#include "authcontroller.h"
#include "utility/functional.h"
#include <workflow/HttpUtil.h>
#include <QDebug>

namespace App
{
AuthController::AuthController(QSharedPointer<HTTPServer> server)
    : m_httpServer(server)
    , m_authService(new AuthService)
{
    m_httpServer->POST("/auth", bind(&AuthController::auth, this));
    m_httpServer->POST("/refresh", bind(&AuthController::refresh, this));
}

static void AddTokensToCookies(HTTPResponse *response, const AuthResponseDTO &dto)
{
    HTTPCookie accessTokenCookie("Access-Token", dto.m_accessToken.toStdString());
    accessTokenCookie.set_http_only(true);

    HTTPCookie refreshTokenCookie("Refresh-Token", dto.m_refreshToken.toStdString());
    refreshTokenCookie.set_http_only(true);
    refreshTokenCookie.set_path("/refresh");

    response->add_cookie(accessTokenCookie);
    response->add_cookie(refreshTokenCookie);
}

void AuthController::auth(const HTTPRequest *request, HTTPResponse *response)
{
    auto dto = extract<UserRequestDTO>(request);
    if (!dto.has_value())
    {
        response->set_status(HttpStatusBadRequest);
        return;
    }

    auto authDto = m_authService->login(dto.value());
    if (!authDto.has_value())
    {
        qDebug() << "User " << authDto->m_login << " does not exists;";
        response->set_status(HttpStatusBadRequest);
        return;
    }

    auto tokens = m_authService->generateTokens(authDto.value());
    AddTokensToCookies(response, tokens.value());

    response->set_status(HttpStatusOK);
}

void AuthController::refresh(const HTTPRequest *request, HTTPResponse *response)
{
    const auto &cookies = request->cookies();

    if (!cookies.contains("Refresh-Token"))
    {
        response->set_status(HttpStatusForbidden);
        return;
    }

    auto refreshedTokens = m_authService->refreshTokens(QString::fromStdString(cookies.at("Refresh-Token")));
    if (!refreshedTokens.has_value())
    {
        response->set_status(HttpStatusForbidden);
        return;
    }
    AddTokensToCookies(response, refreshedTokens.value());

    response->set_status(HttpStatusOK);
}
} // namespace App
