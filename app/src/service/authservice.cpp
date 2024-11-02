#include "authservice.h"
#include "mapper/usermapper.h"
#include <chrono>
#include <jwt-cpp/jwt.h>
#include <QDebug>

namespace App
{
AuthService::AuthService() noexcept
    : m_userRepository(QSharedPointer<UserRepository>::create())
{}

auto AuthService::generateTokens(const AuthRequestDTO &dto) noexcept -> std::optional<AuthResponseDTO>
{
    auto time = jwt::date::clock::now();

    auto accessToken = jwt::create()
                           .set_type("JWT")
                           .set_issuer("app")
                           .set_id("Access-Token")
                           .set_payload_claim("usr", jwt::claim(dto.m_login.toStdString()))
                           .set_expires_at(time + std::chrono::days(1))
                           .sign(jwt::algorithm::hs256(dto.m_salt.toStdString()));

    auto refreshToken = jwt::create()
                            .set_type("JWT")
                            .set_issuer("app")
                            .set_id("Refresh-Token")
                            .set_payload_claim("usr", jwt::claim(dto.m_login.toStdString()))
                            .set_expires_at(time + std::chrono::days(3))
                            .sign(jwt::algorithm::hs256(dto.m_salt.toStdString()));

    return AuthResponseDTO{std::move(QString::fromStdString(accessToken)),
                           std::move(QString::fromStdString(refreshToken))};
}

auto AuthService::login(const UserRequestDTO &dto) noexcept -> std::optional<UserResponseDTO>
{
    const auto &response = m_userRepository->findByLogin(dto.m_login);
    if (!response.has_value())
    {
        return std::nullopt;
    }

    return UserMapper::toResponseDTO(response.value());
}

auto AuthService::refreshTokens(const QString &token) noexcept -> std::optional<AuthResponseDTO>
{
    auto decodedToken = jwt::decode(token.toStdString());

    if (decodedToken.has_expires_at())
    {
        qDebug() << "Token " << token << " expired";
        return std::nullopt;
    }

    const QString &login = QString::fromStdString(decodedToken.get_payload_claim("usr").as_string());
    auto user            = m_userRepository->findByLogin(login);
    if (!user.has_value())
    {
        qDebug() << "Token " << token << " has invalid login data";
        return std::nullopt;
    }

    auto verifier = jwt::verify().allow_algorithm(jwt::algorithm::hs256(user.value().m_salt.toStdString()));

    try
    {
        verifier.verify(decodedToken);
    }
    catch (...)
    {
        qDebug() << "Token " << token << " has invalid encryptor key";
        return std::nullopt;
    }

    return generateTokens(UserMapper::toResponseDTO(user.value()));
}
} // namespace App
