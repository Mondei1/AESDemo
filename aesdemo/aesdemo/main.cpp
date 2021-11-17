#include <iostream>
#include <libaesdemo/MainWindow.hpp>
#include <gtkmm.h>

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("com.github.mondei1.aesdemo");

    /*if (sodium_init() == -1) {
        std::cout << "Critical dependency \"Sodium\" failed to initialize. Exiting ..." << std::endl;
        return 1;
    }

    if (crypto_aead_aes256gcm_is_available() == 0) {
        std::cout << "Apparently your CPU does not support hardware-accelerated AES encryption. Exiting ..." << std::endl;
        return 1;
    }*/

    /*auto refBuilder = Gtk::Builder::create();
    refBuilder->add_from_file("MainWindow.glade");
    }*/

    return app->make_window_and_run<aesdemo::MainWindow>(argc, argv, app);
}