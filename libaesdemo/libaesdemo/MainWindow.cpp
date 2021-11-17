#include "MainWindow.hpp"
#include <iostream>
#include <gtkmm/cssprovider.h>

namespace aesdemo {
    int clickCount = 0;

    MainWindow::MainWindow(const Glib::RefPtr<Gtk::Application> &app)
        : Gtk::ApplicationWindow(app)
        , mBtnBox(Gtk::Orientation::HORIZONTAL, 10)
        , mBtnEncrypt("Verschlüsseln")
        , mBtnDecrypt("Entschlüsseln")
        , mBtnClear("Löschen")
        , mPassphrase()
        , mCipher()
        , mIV()
        , mInput()
        , mTitle("AES Demo")
        , mSubTitle("Dieses Demo Programm demonstiert Ihnen wie AES funktioniert.")
        , mGrid() {
        set_default_size(640, 480);
        set_title("AESDemo");

        mBtnEncrypt.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnEncrypt));
        mBtnDecrypt.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnClick));
        mBtnClear.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OnClickClear));

        // mBtnClear
        Glib::RefPtr<Gtk::CssProvider> cssProvider = Gtk::CssProvider::create();

        // TODO: This is a possible way but hovering and clicking the button will not change its color.
        cssProvider->load_from_data("button { background-image: image(red); }");
        mBtnClear.get_style_context()->add_provider(cssProvider, GTK_STYLE_PROVIDER_PRIORITY_USER);

        mBtnBox.append(mBtnEncrypt);
        mBtnBox.append(mBtnClear);
        mBtnBox.append(mBtnDecrypt);

        mIV.set_icon_from_icon_name("gtk-add");
        mIV.set_placeholder_text("Initialisierungsvektor");

        auto *titleOptions = new Cairo::FontOptions();
        mTitle.set_font_options(*titleOptions);
        mTitle.set_markup("<b>AES Demo</b>");

        mInput.set_placeholder_text("Eingabe");
        mPassphrase.set_show_peek_icon(true);
        mPassphrase.property_placeholder_text().set_value("Passphrase");
        mCipher.set_placeholder_text("Cipher Text");

        mGrid.set_margin_top(32);
        mGrid.set_column_spacing(16);
        mGrid.set_row_spacing(32);
        mGrid.set_halign(Gtk::Align::CENTER);

        mGrid.attach(mTitle, 0, 0);
        mGrid.attach(mSubTitle, 0, 1);
        mGrid.attach(mInput, 0, 2);
        mGrid.attach(mPassphrase, 0, 3);
        mGrid.attach(mIV, 1, 3);
        mGrid.attach(mCipher, 0, 4);
        mGrid.attach(mBtnBox, 0, 5);

        set_child(mGrid);
    }

    void MainWindow::OnClick() {
        Crypto crypto = aesdemo::Crypto();
        // mBtnEncrypt.set_label("Clicked " + std::to_string(aesdemo::clickCount) + " times");
    }

    void MainWindow::OnClickClear() {
        mPassphrase.set_text("");
        mCipher.set_text("");
        mInput.set_text("");
        mIV.set_text("");
    }

    /**
     * Function will be executed when the user clicks on the "Encrypt" button.
     */
     void MainWindow::OnEncrypt() {
        Crypto::encrypt((unsigned char *) "ABCABCABCABCABCAABCABCABCAB", (unsigned char *) "ABCABCABCABCABCA", "Informatiksystem");
    }
}