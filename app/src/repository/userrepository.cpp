#include "userrepository.h"
#include "config.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

namespace App
{
UserRepository::UserRepository() noexcept
    : m_database(QSharedPointer<QSqlDatabase>::create(QSqlDatabase::addDatabase("QPSQL")))
{
    m_database->setHostName(Config::POSTGRES_HOST);
    m_database->setDatabaseName(Config::POSTGRES_DB);
    m_database->setUserName(Config::POSTGRES_USER);
    m_database->setPassword(Config::POSTGRES_PASSWORD);
    m_database->setPort(Config::POSTGRES_PORT);
}

bool UserRepository::add(const User &user) noexcept
{
    qDebug() << "UserRepository::add: " << *m_database;
    qDebug() << m_database->connectionNames();
    if (!m_database->open())
    {
        qDebug() << m_database->lastError();
        return false;
    }

    QSqlQuery query(*m_database);
    query.prepare("INSERT INTO users (login, salt, password) "
                  "VALUES (:login, :salt, :password)");
    query.bindValue(":login", user.m_login);
    query.bindValue(":salt", user.m_salt);
    query.bindValue(":password", user.m_password);

    bool isSuccess = query.exec();

    m_database->close();
    return isSuccess;
}

std::optional<User> UserRepository::findById(quint64 id) noexcept
{
    if (!m_database->open())
    {
        qDebug() << m_database->lastError();
        return std::nullopt;
    }

    QSqlQuery query(*m_database);
    query.prepare("SELECT * FROM users WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        m_database->close();
        return std::nullopt;
    }

    if (query.next())
    {
        User user{query.value("id").toUInt(),
                  query.value("login").toString(),
                  query.value("password").toString(),
                  query.value("salt").toString()};
        m_database->close();
        return user;
    }

    m_database->close();
    return std::nullopt;
}

std::optional<User> UserRepository::findByLogin(const QString &login) noexcept
{
    qDebug() << "UserRepository::findByLogin: " << *m_database;
    if (!m_database->open())
    {
        qDebug() << m_database->lastError();
        return std::nullopt;
    }

    QSqlQuery query(*m_database);
    query.prepare("SELECT * FROM users WHERE login = :login");
    query.bindValue(":login", login);

    if (!query.exec())
    {
        m_database->close();
        return std::nullopt;
    }

    if (query.next())
    {
        User user{query.value("id").toUInt(),
                  query.value("login").toString(),
                  query.value("password").toString(),
                  query.value("salt").toString()};
        m_database->close();
        return user;
    }

    m_database->close();
    return std::nullopt;
}
} // namespace App
