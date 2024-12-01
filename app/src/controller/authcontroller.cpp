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
    m_httpServer->POST("/sign-up", bind(&AuthController::signUp, this));
    m_httpServer->POST("/auth", bind(&AuthController::signIn, this));
    m_httpServer->POST("/refresh", bind(&AuthController::refresh, this));
}

static void AddTokensToCookies(HTTPResponse *response, const std::tuple<QString, QString> &tokens)
{
    const auto &[accessToken, refreshToken] = tokens;
    HTTPCookie refreshTokenCookie("Refresh-Token", refreshToken.toStdString());
    refreshTokenCookie.set_http_only(true);
    refreshTokenCookie.set_path("/refresh");

    HTTPCookie accessTokenCookie("Access-Token", accessToken.toStdString());
    accessTokenCookie.set_http_only(true);

    response->add_cookie(accessTokenCookie);
    response->add_cookie(refreshTokenCookie);
}

void AuthController::signUp(const HTTPRequest *request, HTTPResponse *response)
{
    qDebug() << "AuthController: signUp handler entered";
    const auto &dto = extract<SignUpRequestDTO>(request);
    if (!dto.has_value())
    {
        response->set_status(HttpStatusBadRequest);
        return;
    }
    qDebug() << "AuthController: SignUpRequestDTO successfully extracted";

    if (!m_authService->create(dto.value()).has_value())
    {
        qDebug() << "User " << dto->m_login << " did not create";
        response->set_status(HttpStatusBadRequest);
        return;
    }

    qDebug() << "User " << dto->m_login << " created successfully";
    response->set_status(HttpStatusCreated);
}

void AuthController::signIn(const HTTPRequest *request, HTTPResponse *response)
{
    const auto &requestDto = extract<SignInRequestDTO>(request);
    if (!requestDto.has_value())
    {
        response->set_status(HttpStatusBadRequest);
        return;
    }

    const auto &responseDto = m_authService->login(requestDto.value());
    if (!responseDto.has_value())
    {
        qDebug() << "User " << responseDto->m_login << " does not exists";
        response->set_status(HttpStatusBadRequest);
        return;
    }

    AddTokensToCookies(response, {responseDto.value().m_accessToken, responseDto.value().m_refreshToken});

    response->set_status(HttpStatusOK);
}

void AuthController::refresh(const HTTPRequest *request, HTTPResponse *response)
{
    const auto &requestDto = extract<RefreshRequestDTO>(request);
    if (!requestDto.has_value())
    {
        qDebug() << "Refresh request invalid";
        response->set_status(HttpStatusBadRequest);
        return;
    }

    qDebug() << "Cookie is got: Refresh_Token " << requestDto->m_refreshToken;

    const auto &responseDto = m_authService->refreshTokens(requestDto.value());
    if (!responseDto.has_value())
    {
        qDebug() << "ERROR: Refreshing tokens is fail";
        response->set_status(HttpStatusForbidden);
        return;
    }

    AddTokensToCookies(response, {responseDto.value().m_accessToken, responseDto.value().m_refreshToken});

    qDebug() << "Tokens refreshed";

    response->set_status(HttpStatusOK);
}
} // namespace App
