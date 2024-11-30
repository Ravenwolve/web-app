#include "passwordbuilder.h"
#include <climits>
#include <random>

namespace App
{

PasswordBuilder::PasswordBuilder(const QString &password) noexcept
    : m_password(password)
{}

PasswordBuilder::PasswordBuilder(QString &&password) noexcept
    : m_password(password)
{}

auto PasswordBuilder::generateSalt() noexcept -> PasswordBuilder &
{
    std::independent_bits_engine<std::default_random_engine, CHAR_BIT, unsigned char> rbe;
    std::string salt(32, ' ');
    std::generate(salt.begin(), salt.end(), std::ref(rbe));
    m_salt = std::move(QString::fromStdString(salt));

    return *this;
}

auto PasswordBuilder::salt() noexcept -> PasswordBuilder &
{
    return salt(m_salt);
}

auto PasswordBuilder::salt(const QString &salt) noexcept -> PasswordBuilder &
{
    m_password += salt;

    return *this;
}

auto PasswordBuilder::encrypt() noexcept -> PasswordBuilder &
{
    m_password = std::move(QString::fromStdString(std::to_string(std::hash<std::string>()(m_password.toStdString()))));

    return *this;
}

auto PasswordBuilder::getPassword() noexcept -> QString
{
    return m_password;
}

auto PasswordBuilder::getSalt() noexcept -> QString
{
    return m_salt;
}

auto PasswordBuilder::getPair() noexcept -> std::pair<QString, QString>
{
    return {m_salt, m_password};
}

} // namespace App
