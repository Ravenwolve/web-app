#ifndef AUTHRESPONSEDTO_H
#define AUTHRESPONSEDTO_H

#include <QString>

namespace App
{
struct AuthResponseDTO
{
    QString m_accessToken;
    QString m_refreshToken;
};
} // namespace App

#endif
