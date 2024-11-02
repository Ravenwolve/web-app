#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "service/userservice.h"
#include "utility/alias.h"
#include <wfrest/HttpServer.h>
#include <QScopedPointer>
#include <QSharedPointer>

namespace App
{
class UserController
{
public:
    void signUp(const HTTPRequest *request, HTTPResponse *response);

public:
    UserController(QSharedPointer<HTTPServer> server);

private:
    QSharedPointer<HTTPServer> m_httpServer;
    QScopedPointer<UserService> m_userService;
};
} // namespace App

#endif
