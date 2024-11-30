#include "userrepository.h"
#include "config.h"
#include <iostream>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include <QSqlError>
#include <QSqlQuery>
#include <QThread>

namespace App
{

UserRepository::UserRepository() noexcept
    : m_database(QSqlDatabase::addDatabase("QPSQL"))
{
    m_database.setHostName(Config::POSTGRES_HOST);
    m_database.setDatabaseName(Config::POSTGRES_DB);
    m_database.setUserName(Config::POSTGRES_USER);
    m_database.setPassword(Config::POSTGRES_PASSWORD);
    m_database.setPort(Config::POSTGRES_PORT);
    m_database.open();
    qDebug() << m_database;
}

bool UserRepository::add(const User &user) noexcept
{
    if (!m_database.isOpen())
    {
        m_database.open();
    }
    qDebug() << "UserRepository::add";
    std::cerr << "Add" << std::endl;
    // auto m_database = ConnectToDB();
    QSqlQuery query(m_database);
    std::cerr << "Initialized" << std::endl;
    query.prepare("INSERT INTO users (login, salt, password) VALUES (:login, :salt, :password)");
    std::cerr << "Prepared" << std::endl;
    query.bindValue(":login", user.m_login);
    std::cerr << "Login bound" << std::endl;
    query.bindValue(":salt", user.m_salt);
    std::cerr << "Login bound" << std::endl;
    query.bindValue(":password", user.m_password);
    std::cerr << "Login bound" << std::endl;

    return query.exec();
}

std::optional<User> UserRepository::findById(quint64 id) noexcept
{
    if (!m_database.isOpen())
    {
        m_database.open();
    }
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM users WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next())
    {
        return std::nullopt;
    }

    User user{query.value("id").toUInt(),
              query.value("login").toString(),
              query.value("password").toString(),
              query.value("salt").toString()};

    return user;
}

std::optional<User> UserRepository::findByLogin(const QString &login) noexcept
{
    qDebug() << "UserRepository::findByLogin";
    if (!m_database.isOpen())
    {
        m_database.open();
    }
    qDebug() << "Connected!";
    QSqlQuery query(m_database);
    qDebug() << "Query initialized!";
    query.prepare("SELECT * FROM users WHERE login = :login");
    qDebug() << "Query prepared!";
    query.bindValue(":login", login);
    qDebug() << "Query bound!";

    if (!query.exec() || !query.next())
    {
        return std::nullopt;
    }

    User user{query.value("id").toUInt(),
              query.value("login").toString(),
              query.value("password").toString(),
              query.value("salt").toString()};

    return user;
}
} // namespace App
