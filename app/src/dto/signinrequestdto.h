#ifndef SIGNINREQUESTDTO_H
#define SIGNINREQUESTDTO_H

#include <QString>

namespace App
{
struct SignInRequestDTO
{
    QString m_login;
    QString m_password;
};
} // namespace App

#endif
