#ifndef USERRESPONSEDTO_H
#define USERRESPONSEDTO_H

#include <QString>

namespace App {
struct UserResponseDTO {
  quint64 m_id;
  QString m_login;
  QString m_password;
  QString m_salt;
};
} // namespace App

#endif
