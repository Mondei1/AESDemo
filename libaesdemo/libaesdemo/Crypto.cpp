#include "Crypto.hpp"

std::string aesdemo::Crypto::encrypt(ModeOfOperation mode, unsigned char *key, std::string input, unsigned char *iv) {
    struct AES_ctx ctx{};

    auto buf = reinterpret_cast<uint8_t*>(&input);

    pkcs7_padding_pad_buffer(buf, input.size(), sizeof buf, 16);

    if (mode == ModeOfOperation::cbc) {
        if (iv == nullptr) {
            std::cerr << "You try to encrypt data using CBC mode but provided to IV. This operation is not possible." << std::endl;
            return "";
        }

        // This time, we need to add a IV because CBC requires one.
        AES_init_ctx_iv(&ctx, key, iv);
        AES_ECB_encrypt(&ctx, buf);
    } else if (mode == ModeOfOperation::ecb) {
        // We don't need to init with an IV because ECB doesn't need one.
        AES_init_ctx(&ctx, key);
        AES_ECB_encrypt(&ctx, buf);
    }

    std::cout << "Successfully encrypted content: " << buf << std::endl;

    //int padAction = sodium_pad(&buf_padded_len, key, buf_unpadded_len, block_size, sizeof key);

    std::cout << base64_encode(Utils::convertToString(reinterpret_cast<char *>(buf), sizeof(key))) << std::endl;

    return "worked";
}