#include "dhp.h"
#include <gtkmm/application.h>

int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  DevhelpPlugin devhelp;

  //Shows the window and returns when it is closed.
  return app->run(devhelp);
}
