#include "application.h"

#include <QCoreApplication>

int main(int argc, char *argv[]) {
  auto app = std::make_unique<QCoreApplication>(argc, argv);

  App::Application srv(std::move(app));
  return !srv.run();
}
