#pragma once

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <giomm/simpleactiongroup.h>
#include <iostream>
#include <gtkmm/passwordentry.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/listitem.h>
#include <gtkmm/dropdown.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/dialog.h>

#include "Crypto.hpp"

namespace aesdemo {
    class MainWindow : public Gtk::ApplicationWindow {
    public:
        void ShowError(std::string title, std::string message);
        explicit MainWindow(const Glib::RefPtr<Gtk::Application>& app);

    private:
        // Signal handlers:
        void OnClick();
        void OnEncrypt();
        void OnDecrypt();
        void OnRandomize();
        void OnClickClear();
        void OnDropdownSelect();

        int clickCount;
        Crypto::ModeOfOperation mode;

        // Child widgets:
        Gtk::Grid mGrid;
        Gtk::Label mTitle;
        Gtk::Label mSubTitle;
        Gtk::Box mBtnBox;
        Gtk::ComboBoxText mDropdownMode;
        Gtk::Button mBtnEncrypt, mBtnDecrypt, mBtnClear, mRandomize;
        Gtk::PasswordEntry mPassphrase;
        Gtk::Entry mCipher, mIV, mInput;
        Gtk::CheckButton mRawPassword;
        Gtk::MessageDialog mErrorDialog;
    };
}