#ifndef USER_H
#define USER_H

#include <QString>

namespace App {
struct User {
  quint64 m_id;
  QString m_login;
  QString m_password;
  QString m_salt;
};
} // namespace App

#endif
