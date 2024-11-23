#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

namespace App
{
struct Config
{
    inline static const QString POSTGRES_HOST     = qgetenv("POSTGRES_HOST");
    inline static const QString POSTGRES_USER     = qgetenv("POSTGRES_USER");
    inline static const QString POSTGRES_PASSWORD = qgetenv("POSTGRES_PASSWORD");
    inline static const QString POSTGRES_DB       = qgetenv("POSTGRES_DB");
    inline static const quint64 POSTGRES_PORT     = qgetenv("POSTGRES_PORT").toInt();
    inline static const QString JWT_SALT          = qgetenv("JWT_SALT");
};
} // namespace App

#endif
