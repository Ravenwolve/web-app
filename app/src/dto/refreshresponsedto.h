#ifndef REFRESHRESPONSEDTO_H
#define REFRESHRESPONSEDTO_H

#include <QString>

namespace App
{
struct RefreshResponseDTO
{
    quint64 m_id;
    QString m_login;
    QString m_password;
    QString m_salt;
    QString m_accessToken;
    QString m_refreshToken;
};
} // namespace App

#endif
