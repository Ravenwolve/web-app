#include "application.h"
#include <QDebug>
#include <wfrest/HttpServer.h>
#include <workflow/HttpUtil.h>

namespace App {
Application::Application(std::unique_ptr<QCoreApplication> application)
    : m_userController(nullptr), m_application(application.release()) {}

int Application::run() {
  quint64 port = 8080;

  auto httpServer = QSharedPointer<HTTPServer>::create();

  m_userController.reset(new UserController(httpServer));

  if (httpServer->start(port) == 0) {
    qDebug() << "Server started on port: " << port;
    int exitCode = m_application->exec();
    httpServer->stop();
    qDebug() << "Server stopped";
    return exitCode;
  } else {
    qDebug() << "Cannot start server\n";
    return 1;
  }
  return 0;
}

} // namespace App
