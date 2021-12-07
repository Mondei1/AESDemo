#include "MainWindow.hpp"
#include <iostream>
#include <gtkmm/cssprovider.h>
#include <gtkmm/signallistitemfactory.h>
#include <cryptopp/cryptlib.h>

namespace aesdemo {

    void MainWindow::ShowError(std::string title, std::string message) {
        auto titleWidget = Gtk::make_managed<Gtk::Label>("Fehler");
        mAboutHeaderBar.set_title_widget(*titleWidget);

        mErrorDialog.set_message(title);
        mErrorDialog.set_secondary_text(message);
        mErrorDialog.set_hide_on_close(true);
        mErrorDialog.set_modal();
        mErrorDialog.set_transient_for(*this);
        mErrorDialog.set_titlebar(mAboutHeaderBar);
        mErrorDialog.signal_response().connect(
                sigc::hide(sigc::mem_fun(mErrorDialog, &Gtk::Widget::hide)));
        mErrorDialog.show();
    }

    Crypto::ModeOfOperation mode = Crypto::ModeOfOperation::cbc;

    MainWindow::MainWindow(const Glib::RefPtr<Gtk::Application> &app)
            : Gtk::ApplicationWindow(app)
            , mHeaderBar()
            , mDialogAbout()
            , mAboutHeaderBar()
            , mBtnAbout()
            , mErrorDialog(*this, "")
            , mBtnBox(Gtk::Orientation::HORIZONTAL, 10)
            , mBtnEncrypt("Verschlüsseln")
            , mBtnDecrypt("Entschlüsseln")
            , mBtnClear("Löschen")
            , mRandomize("Per Zufall ausfüllen")
            , mDropdownMode()
            , mPassphrase()
            , mCipher()
            , mIV()
            , mInput()
            , mRawPassword()
            , mTitle("AES Demo")
            , mSubTitle("Dieses Demo Programm demonstriert Ihnen wie AES funktioniert.")
            , mGrid() {
        set_default_size(600, 480);
        set_title("AES Demo");

        // Header bar & About
        auto texture = Gdk::Texture::create_from_resource("/img/icon.png");
        mDialogAbout.set_logo(texture);
        mDialogAbout.set_program_name("AESDemo");
        mDialogAbout.set_authors(std::vector<Glib::ustring> { "Nicolas Klier <klier.nicolas@protonmail.com>" });
        mDialogAbout.set_comments("Dieses Demo Programm demonstriert Ihnen wie AES funktioniert. Es dient als Eigenanteil meiner Belegarbeit über AES.");
        mDialogAbout.set_version("1.0");
        mDialogAbout.set_transient_for(*this);
        mDialogAbout.set_license_type(Gtk::License::MIT_X11);
        mDialogAbout.set_website("https://github.com/mondei1/AESDemo");
        mDialogAbout.set_hide_on_close();
        mDialogAbout.set_modal();

        mBtnAbout.set_icon_name("help-about");
        mHeaderBar.pack_start(mBtnAbout);
        set_titlebar(reinterpret_cast<Widget &>(mHeaderBar));

        //
        // Events
        //
        mBtnEncrypt.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnEncrypt));
        mBtnDecrypt.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnDecrypt));
        mBtnClear.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnClickClear));
        mRandomize.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnRandomize));
        mBtnAbout.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnAboutClick));

        // mBtnClear
        Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();

        // TODO: This is a possible way but hovering and clicking the button will not change its color.
        cssProvider->load_from_data("button { background-image: image(red); }");
        mBtnClear.get_style_context()->add_provider(cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);

        mBtnBox.append(mBtnEncrypt);
        mBtnBox.append(mBtnClear);
        mBtnBox.append(mBtnDecrypt);
        mBtnBox.set_halign(Gtk::Align::CENTER);

        mIV.set_icon_from_icon_name("gtk-add");
        mIV.set_placeholder_text("Initialisierungsvektor");

        auto *titleOptions = new Cairo::FontOptions();
        mTitle.set_font_options(*titleOptions);
        mTitle.set_markup("<span size='30000'>AES Demo</span>");

        mInput.set_placeholder_text("Eingabe");
        mPassphrase.set_show_peek_icon(true);
        mPassphrase.property_placeholder_text().set_value("Passphrase");
        mCipher.set_placeholder_text("Cipher Text");

        // Grid settings
        mGrid.set_margin_top(32);
        mGrid.set_margin_bottom(32);
        mGrid.set_column_spacing(16);
        mGrid.set_row_spacing(24);
        mGrid.set_halign(Gtk::Align::CENTER);

        mDropdownMode.append("CBC");
        mDropdownMode.append("ECB");
        mDropdownMode.set_active_text("CBC");
        mDropdownMode.signal_changed().connect(sigc::mem_fun(*this, &MainWindow::OnDropdownSelect));

        mRawPassword.set_label("ohne KDF");
        mRawPassword.set_tooltip_text(
                "Dies deaktiviert die Key Derivation Function (KDF). Sie wird verwendet um das Passwort sicherer zu machen und in die von AES gewünschte Form zu bringen. Daher sind Variable Schlüssellängen möglich. Durch das deaktivieren wird das Passwort direkt verwendet und der Prozess wird schneller.");
        mRawPassword.set_halign(Gtk::Align::CENTER);

        mGrid.attach(mTitle, 0, 0, 2);
        mGrid.attach(mSubTitle, 0, 1, 2);
        mGrid.attach(mDropdownMode, 0, 2, 2);
        mGrid.attach(mInput, 0, 3, 2);
        mGrid.attach(mPassphrase, 0, 4);
        mGrid.attach(mIV, 1, 4);
        mGrid.attach(mCipher, 0, 5, 2);

        mGrid.attach(mRawPassword, 0, 6, 2);
        mGrid.attach(mBtnBox, 0, 7, 2);
        mGrid.attach(mRandomize, 0, 8, 2);

        set_child(mGrid);
    }

    void MainWindow::OnClick() {
    }

    void MainWindow::OnClickClear() {
        mPassphrase.set_text("");
        mCipher.set_text("");
        mInput.set_text("");
        mIV.set_text("");
        mRawPassword.set_active(false);
    }

    void MainWindow::OnRandomize() {
        const char *plaintext[15] = {"Das ist eine zufällige Nachricht.",
                                     "Was für eine Zufall nicht wahr?",
                                     "Manchmal frage ich mich ob das Zufall ist.",
                                     "Letztens war das echt zufällig.",
                                     "Hätte er nicht so zufällig diese Zahl gewürfelt, hätte ich gewonnen.",
                                     "Also ich glaube nicht an Zufall, du?",
                                     "Doch, also ich glaube an Zufall.",
                                     "Wusstest du das ein Computer keinen echten Zufall erstellen kann?",
                                     "Zufallsrechnung in Mathe ist langweilig.",
                                     "Zufällig habe ich eine Nachricht geschrieben und zufällig an dich gesendet.",
                                     "Vielleicht gewinne ich morgen per Zufall im Lotto.",
                                     "AES ist die am weitesten verbreitete Verschlüsselungsmethode.",
                                     "Sogar die NSA verwendet AES um Top-Secret Akten zu verschlüsseln.",
                                     "Früher waren in den USA alle Cipher, die eine Schlüssellänge von mehr als 56-Bit unterstützten, verboten.",
                                     "Tools wie GPG nutzen ebenfalls AES um Daten symmetrisch zu verschlüsseln."};
        std::basic_string<char> iv = Utils::RandomString(16);
        std::string passphrase = Utils::RandomString(16);

        mPassphrase.set_text(passphrase);
        mIV.set_text(iv);
        mInput.set_text(plaintext[rand() & 14]);
    }

    /**
     * Function will be executed when the user clicks on the "Encrypt" button.
     */
    void MainWindow::OnEncrypt() {
        std::cout << std::endl << "[ ------------------------ Start Encryption ------------------------ ]" << std::endl;
        try {
            auto helper = new aesdemo::Crypto( !mRawPassword.get_active());
            std::string enc = helper->Encrypt(aesdemo::mode, mPassphrase.get_text(), mInput.get_text().c_str(),
                                             mIV.get_text());
            mCipher.set_text(enc);
        } catch (const CryptoPP::Exception &e) {
            ShowError("Verschlüsselungsfehler", e.what());

            std::cerr << "Encryption failed because of the following error: " << e.what() << std::endl;
        }

        std::cout << "[ ------------------------- End Encryption ------------------------- ]" << std::endl << std::endl;
    }

    /**
     * Function will be executed when the user clicks on the "Decrypt" button.
     */
    void MainWindow::OnDecrypt() {
        std::cout << "[ ------------------------ Start Decryption ------------------------ ]" << std::endl;
        try {
            auto helper = new aesdemo::Crypto(!mRawPassword.get_active());
            std::string dec = helper->Decrypt(aesdemo::mode, mPassphrase.get_text(), mCipher.get_text(), mIV.get_text());
            mInput.set_text(dec);
        } catch (const CryptoPP::Exception &e) {
            ShowError("Entschlüsselungsfehler", e.what());

            std::cerr << "Decryption failed because of the following error: " << e.GetErrorType() << ": " << e.what() << std::endl;
        }

        std::cout << "[ ------------------------- End Decryption ------------------------- ]" << std::endl << std::endl;
    }

    void MainWindow::OnDropdownSelect() {
        auto selected = mDropdownMode.get_active_text();

        if (selected == "CBC") {
            aesdemo::mode = Crypto::ModeOfOperation::cbc;

            mIV.set_visible(true);
            mGrid.remove(mPassphrase);
            mGrid.attach(mPassphrase, 0, 4);
        } else if (selected == "ECB") {
            aesdemo::mode = Crypto::ModeOfOperation::ecb;

            mIV.set_visible(false);
            mIV.set_text("");

            mGrid.remove(mPassphrase);
            mGrid.attach(mPassphrase, 0, 4, 2);
        }
    }

    void MainWindow::OnAboutClick() {
        mDialogAbout.show();
        mDialogAbout.present();
    }
}