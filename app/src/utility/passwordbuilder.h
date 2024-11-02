#ifndef PASSWORDBUILDER_H
#define PASSWORDBUILDER_H

#include <QString>

namespace App {
class PasswordBuilder {
public:
  auto generateSalt() noexcept -> PasswordBuilder &;
  auto salt() noexcept -> PasswordBuilder &;
  auto encrypt() noexcept -> PasswordBuilder &;

public:
  PasswordBuilder(const QString &password) noexcept;
  PasswordBuilder(QString &&password) noexcept;

public:
  QString m_salt;
  QString m_password;
};
} // namespace App

#endif
