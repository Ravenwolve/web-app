#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include "dto/refreshrequestdto.h"
#include "dto/refreshresponsedto.h"
#include "dto/signinrequestdto.h"
#include "dto/signinresponsedto.h"
#include "dto/signuprequestdto.h"
#include "dto/signupresponsedto.h"
#include "repository/userrepository.h"
#include <chrono>
#include <optional>
#include <QSharedPointer>

namespace App
{
class AuthService
{
public:
    auto create(const SignUpRequestDTO &dto) noexcept -> std::optional<SignUpResponseDTO>;
    auto login(const SignInRequestDTO &dto) noexcept -> std::optional<SignInResponseDTO>;
    auto refreshTokens(const RefreshRequestDTO &token) noexcept -> std::optional<RefreshResponseDTO>;

private:
    auto generateToken(const QString id,
                       const std::chrono::system_clock::time_point &startsWith,
                       size_t days,
                       const QString &login) noexcept -> QString;

public:
    AuthService() noexcept;

private:
    QSharedPointer<UserRepository> m_userRepository;
};
} // namespace App

#endif
