#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include "../dto/userrequestdto.h"
#include "../entity/user.h"
#include <QSqlDatabase>
#include <optional>

namespace App {
class UserRepository {
public:
  bool add(const User &user) noexcept;
  auto findById(quint64 id) noexcept -> std::optional<User>;
  auto findByLogin(const QString &login) noexcept -> std::optional<User>;

public:
  UserRepository() noexcept;

private:
  QSharedPointer<QSqlDatabase> m_database;
};
} // namespace App

#endif
