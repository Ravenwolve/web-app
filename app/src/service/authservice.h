#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include "dto/authrequestdto.h"
#include "dto/authresponsedto.h"
#include "dto/userrequestdto.h"
#include "dto/userresponsedto.h"
#include "repository/userrepository.h"
#include <optional>
#include <QSharedPointer>

namespace App
{
class AuthService
{
public:
    auto generateTokens(const AuthRequestDTO &dto) noexcept -> std::optional<AuthResponseDTO>;
    auto refreshTokens(const QString &token) noexcept -> std::optional<AuthResponseDTO>;
    auto login(const UserRequestDTO &dto) noexcept -> std::optional<UserResponseDTO>;

public:
    AuthService() noexcept;

private:
    QSharedPointer<UserRepository> m_userRepository;
};
} // namespace App

#endif
