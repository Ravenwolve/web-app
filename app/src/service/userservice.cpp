#include "userservice.h"

#include "mapper/usermapper.h"
#include "utility/passwordbuilder.h"
#include <QDebug>

namespace App
{
UserService::UserService() noexcept
    : m_userRepository(QSharedPointer<UserRepository>::create())
{}

std::optional<UserResponseDTO> UserService::create(const UserRequestDTO &dto) noexcept
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
} // namespace App
