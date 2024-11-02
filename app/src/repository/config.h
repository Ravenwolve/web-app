#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

namespace App {
struct Config {
  inline static const QString HOST = "172.18.0.2";
  inline static const QString POSTGRES_USER = qgetenv("POSTGRES_USER");
  inline static const QString POSTGRES_PASSWORD = qgetenv("POSTGRES_PASSWORD");
  inline static const QString POSTGRES_DB = qgetenv("POSTGRES_DB");
  inline static const quint64 POSTGRES_PORT = 5432;
};
} // namespace App

#endif
