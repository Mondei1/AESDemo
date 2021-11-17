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

#include "Crypto.hpp"

namespace aesdemo {
    class MainWindow : public Gtk::ApplicationWindow {
    public:
        void ShowError(std::string message);
        explicit MainWindow(const Glib::RefPtr<Gtk::Application>& app);

    private:
        // Signal handlers:
        void OnClick();
        void OnEncrypt();
        void OnClickClear();

        int clickCount;

        // Child widgets:
        Gtk::Grid mGrid;
        Gtk::Label mTitle;
        Gtk::Label mSubTitle;
        Gtk::Box mBtnBox;
        Gtk::Button mBtnEncrypt, mBtnDecrypt, mBtnClear;
        Gtk::PasswordEntry mPassphrase;
        Gtk::Entry mCipher, mIV, mInput;
    };
}