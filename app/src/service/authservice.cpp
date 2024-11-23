#include "authservice.h"
#include "dto/refreshrequestdto.h"
#include "mapper/usermapper.h"
#include "repository/config.h"
#include "utility/passwordbuilder.h"
#include <chrono>
#include <jwt-cpp/jwt.h>
#include <QDebug>

namespace App
{
AuthService::AuthService() noexcept
    : m_userRepository(QSharedPointer<UserRepository>::create())
{}

std::optional<SignUpResponseDTO> AuthService::create(const SignUpRequestDTO &dto) noexcept
{
    {
        const auto &response = m_userRepository->findByLogin(dto.m_login);
        if (response.has_value())
        {
            qDebug() << "ERROR: User " << dto.m_login << " exists yet;";
            return std::nullopt;
        }
    }

    const auto &[salt, password] = PasswordBuilder(dto.m_password).generateSalt().salt().encrypt();

    User newUser{NULL, dto.m_login, std::move(password), std::move(salt)};

    if (!m_userRepository->add(newUser))
    {
        qDebug() << "ERROR: User " << dto.m_login << " did not add to database;";
        return std::nullopt;
    }

    const auto &response = m_userRepository->findByLogin(dto.m_login);
    if (!response.has_value())
    {
        qDebug() << "ERROR: User " << dto.m_login << " does not exists;";
        return std::nullopt;
    }

    return UserMapper::toResponseDTO(response.value());
}

auto AuthService::generateToken(const QString id,
                                const std::chrono::system_clock::time_point &startsWith,
                                size_t days,
                                const QString &login) noexcept -> QString
{
    auto time = jwt::date::clock::now();

    auto token = jwt::create()
                     .set_type("JWT")
                     .set_issuer("app")
                     .set_id(id.toStdString())
                     .set_payload_claim("usr", jwt::claim(login.toStdString()))
                     .set_expires_at(time + std::chrono::days(days))
                     .sign(jwt::algorithm::hs256(Config::JWT_SALT.toStdString()));

    return QString::fromStdString(token);
}

auto AuthService::login(const SignInRequestDTO &dto) noexcept -> std::optional<SignInResponseDTO>
{
    const auto &user = m_userRepository->findByLogin(dto.m_login);
    if (!user.has_value())
    {
        return std::nullopt;
    }
    if (PasswordBuilder(dto.m_password).salt(user->m_salt).encrypt().getPassword() != user->m_password)
    {
        qDebug() << "User " << dto.m_login << ": Invalid password";
        return std::nullopt;
    }

    auto now                 = jwt::date::clock::now();
    const auto &accessToken  = generateToken("Access-Token", now, 1, user->m_login);
    const auto &refreshToken = generateToken("Refresh-Token", now, 3, user->m_login);

    return SignInResponseDTO{user->m_id, user->m_login, user->m_password, user->m_salt, accessToken, refreshToken};
}

auto AuthService::refreshTokens(const RefreshRequestDTO &dto) noexcept -> std::optional<RefreshResponseDTO>
{
    auto decodedToken = jwt::decode(dto.m_refreshToken.toStdString());

    if (decodedToken.has_expires_at())
    {
        qDebug() << "Token " << dto.m_refreshToken << " expired";
        return std::nullopt;
    }

    const QString &login = QString::fromStdString(decodedToken.get_payload_claim("usr").as_string());
    auto user            = m_userRepository->findByLogin(login);
    if (!user.has_value())
    {
        qDebug() << "Token " << dto.m_refreshToken << " has invalid login data";
        return std::nullopt;
    }

    auto verifier = jwt::verify().allow_algorithm(jwt::algorithm::hs256(user.value().m_salt.toStdString()));

    try
    {
        verifier.verify(decodedToken);
    }
    catch (...)
    {
        qDebug() << "Token " << dto.m_refreshToken << " has invalid encryptor key";
        return std::nullopt;
    }

    auto now                 = jwt::date::clock::now();
    const auto &accessToken  = generateToken("Access-Token", now, 1, user->m_login);
    const auto &refreshToken = generateToken("Refresh-Token", now, 3, user->m_login);

    return RefreshResponseDTO{user->m_id, user->m_login, user->m_password, user->m_salt, accessToken, refreshToken};
}
} // namespace App
