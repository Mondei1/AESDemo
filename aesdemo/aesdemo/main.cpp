#include <iostream>
#include <libaesdemo/MainWindow.hpp>
#include <gtkmm.h>

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("com.github.mondei1.aesdemo");

    return app->make_window_and_run<aesdemo::MainWindow>(argc, argv, app);
}