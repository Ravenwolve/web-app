#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include "service/authservice.h"
#include "utility/alias.h"
#include <wfrest/HttpServer.h>
#include <QScopedPointer>
#include <QSharedPointer>

namespace App
{
class AuthController
{
public:
    void auth(const HTTPRequest *request, HTTPResponse *response);
    void refresh(const HTTPRequest *request, HTTPResponse *response);

public:
    AuthController(QSharedPointer<HTTPServer> server);

private:
    QSharedPointer<HTTPServer> m_httpServer;
    QScopedPointer<AuthService> m_authService;
};
} // namespace App

#endif
