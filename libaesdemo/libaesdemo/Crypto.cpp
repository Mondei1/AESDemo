#include "Crypto.hpp"
#include <cryptopp/hex.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/modes.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/pwdbased.h>

#define KDF_ITERATIONS 150000
#define DECRYPT_ERROR "Entschlüsselung fehlgeschlagen. Ist der Ciphertext beschädigt, wurde KDF ein-/ausgeschaltet oder ist der Key / IV verändert wurden?"

aesdemo::Crypto::Crypto(bool useKDF) {
    this->useKDF = useKDF;
}


std::string
aesdemo::Crypto::Encrypt(ModeOfOperation mode, std::string key, const std::string &input, std::string iv) {
    CheckInput(key, iv, mode);
    std::cout << "Input for encryption: " << input << " | key: " << key << " | iv: " << iv << std::endl;

    std::string cipherOutput;
    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(cipherOutput));

    CryptoPP::SecByteBlock cryptoKey(CryptoPP::AES::DEFAULT_KEYLENGTH);

    this->DoKDF(key, cryptoKey);

    std::string cipher;

    if (mode == ModeOfOperation::cbc) {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption e;
        e.SetKeyWithIV(cryptoKey, cryptoKey.size(), (CryptoPP::byte *) iv.data(), iv.length());

        CryptoPP::StringSource s(input, true,
                                 new CryptoPP::StreamTransformationFilter(e,
                                                                          new CryptoPP::StringSink(cipher)
                                 )
        );
    } else {
        CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption e;
        e.SetKey(cryptoKey, cryptoKey.size());

        CryptoPP::StringSource s(input, true,
                                 new CryptoPP::StreamTransformationFilter(e,
                                                                          new CryptoPP::StringSink(cipher)
                                 )
        );
    }

    encoder.Put((const CryptoPP::byte *) &cipher[0], cipher.size());
    encoder.MessageEnd();

    std::transform(cipherOutput.begin(), cipherOutput.end(), cipherOutput.begin(), ::tolower);
    std::cout << std::endl << "Successfully encrypted content: " << cipherOutput << std::endl;

    return cipherOutput;
}

std::string
aesdemo::Crypto::Decrypt(ModeOfOperation mode, std::string key, const std::string &input, std::string iv) {
    CheckInput(key, iv, mode);

    std::string decodedCiphertext, recovered;
    CryptoPP::StringSource ss(input, true,
                              new CryptoPP::HexDecoder(
                                      new CryptoPP::StringSink(decodedCiphertext)
                              )
    );

    std::cout << "Input for decryption: " << input << " | key: " << key << " | iv: " << iv << std::endl;

    CryptoPP::SecByteBlock cryptoKey(CryptoPP::AES::DEFAULT_KEYLENGTH);

    this->DoKDF(key, cryptoKey);

    if (mode == ModeOfOperation::cbc) {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption d;
        d.SetKeyWithIV(cryptoKey, cryptoKey.size(), (CryptoPP::byte *) iv.data(), iv.length());

        try {
            CryptoPP::StringSource s(decodedCiphertext, true,
                                     new CryptoPP::StreamTransformationFilter(d,
                                                                              new CryptoPP::StringSink(recovered)
                                     )
            );
        } catch (const CryptoPP::Exception &e) {
            std::cout << e.what() << std::endl;
            throw CryptoPP::Exception(e.GetErrorType(),
                                      DECRYPT_ERROR);
        }
    } else {
        CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption d;
        d.SetKey(cryptoKey, cryptoKey.size());

        try {
            CryptoPP::StringSource s(decodedCiphertext, true,
                                     new CryptoPP::StreamTransformationFilter(d,
                                                                              new CryptoPP::StringSink(recovered)
                                     )
            );
        } catch (const CryptoPP::Exception &e) {
            std::cout << e.what() << std::endl;
            throw CryptoPP::Exception(e.GetErrorType(),
                                      DECRYPT_ERROR);
        }
    }

    std::cout << std::endl << "Decrypted: " << recovered << std::endl;

    return recovered;
}

void aesdemo::Crypto::CheckInput(const std::string &key, const std::string &iv, ModeOfOperation mode) {
    if (!this->useKDF) {
        std::cout << key.length() << std::endl;
        if (key.length() != 16 && key.length() != 24 && key.length() != 32) {
            throw CryptoPP::Exception(CryptoPP::Exception::INVALID_ARGUMENT,
                                      "Die Schlüssellänge darf, wenn KDF deaktiviert ist, nur exakt 16, 24 oder 32 Zeichen lang sein.");
        }
    }

    if (iv.length() != 16 && mode == ModeOfOperation::cbc) {
        throw CryptoPP::Exception(CryptoPP::Exception::INVALID_ARGUMENT,
                                  "Der Initialisierungsvektor darf nur exakt 16 Zeichen lang sein.");
    }
}

void aesdemo::Crypto::DoKDF(const std::string& input, CryptoPP::SecByteBlock &forBlock) {
    if (this->useKDF) {
        // Use PKCS5 and PBKDF2 to pad the input key. This makes it even harder to brute force the password.
        CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA256> kdf;

        auto begin = std::chrono::system_clock::now().time_since_epoch();
        auto beginMillis = std::chrono::duration_cast<std::chrono::milliseconds>(begin).count();

        std::cout << "KDF operation:" << std::endl;
        std::cout << "\t-> Apply PKCS5 padding with PBKDF2 password sketching with " << KDF_ITERATIONS
        << " iterations ..." << std::endl;
        kdf.DeriveKey(forBlock.data(), forBlock.size(), 0, (CryptoPP::byte *) input.data(), input.size(), nullptr, 0,
                      KDF_ITERATIONS);

        auto end = std::chrono::system_clock::now().time_since_epoch();
        auto endMillis = std::chrono::duration_cast<std::chrono::milliseconds>(end).count();

        std::cout << "\t-> Operation took " << (endMillis - beginMillis) << "ms to complete. Key is now " << forBlock.size() << " bytes long." << std::endl;
    } else {
        std::cout << "Skip KDF" << std::endl;

        /*if (key.length() != 16) {
            std::cerr << "If KDF is disabled the provided key MUST BE 16 chars in length." << std::endl;
            throw CryptoPP::Exception(CryptoPP::Exception::OTHER_ERROR, "Schlüssellänge muss bei deaktivierten KDF genau 16 Zeichen lang sein.");
        }*/

        forBlock.Assign((CryptoPP::byte *) input.data(), input.length());
    }
}