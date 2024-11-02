#include "usercontroller.h"
#include "../dto/userrequestdto.h"
#include "../utility/functional.h"
#include <workflow/HttpUtil.h>
#include <QDebug>

namespace App
{
UserController::UserController(QSharedPointer<HTTPServer> server)
    : m_httpServer(server)
    , m_userService(new UserService)
{
    m_httpServer->POST("/sign-up", bind(&UserController::signUp, this));
}

void UserController::signUp(const HTTPRequest *request, HTTPResponse *response)
{
    auto dto = extract<UserRequestDTO>(request);
    if (!dto.has_value())
    {
        response->set_status(HttpStatusBadRequest);
        return;
    }

    if (!m_userService->create(dto.value()).has_value())
    {
        qDebug() << "User " << dto->m_login << " did not create;";
        response->set_status(HttpStatusBadRequest);
    }

    qDebug() << "User " << dto->m_login << " created successfully;";
    response->set_status(HttpStatusCreated);
}
} // namespace App
