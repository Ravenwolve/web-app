#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "dto/userrequestdto.h"
#include "dto/userresponsedto.h"
#include "repository/userrepository.h"
#include <optional>
#include <QSharedPointer>

namespace App
{
class UserService
{
public:
    auto create(const UserRequestDTO &dto) noexcept -> std::optional<UserResponseDTO>;

public:
    UserService() noexcept;

private:
    QSharedPointer<UserRepository> m_userRepository;
};
} // namespace App

#endif
