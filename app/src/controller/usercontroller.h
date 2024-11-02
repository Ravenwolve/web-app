#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "../service/userservice.h"
#include "../utility/alias.h"
#include <QScopedPointer>
#include <QSharedPointer>
#include <wfrest/HttpServer.h>

namespace App {
class UserController {
public:
  void signUp(const HTTPRequest *request, HTTPResponse *response);
  void auth(const HTTPRequest *request, HTTPResponse *response);
  void refresh(const HTTPRequest *request, HTTPResponse *response);

public:
  UserController(QSharedPointer<HTTPServer> server);

private:
  QSharedPointer<HTTPServer> m_httpServer;
  QScopedPointer<UserService> m_userService;
};
} // namespace App

#endif
