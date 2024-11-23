#ifndef SIGNUPRESPONSEDTO_H
#define SIGNUPRESPONSEDTO_H

#include <QString>

namespace App
{
struct SignUpResponseDTO
{
    quint64 m_id;
    QString m_login;
    QString m_password;
    QString m_salt;
};
} // namespace App

#endif
