#ifndef APPLICATION_H
#define APPLICATION_H

#include "controller/authcontroller.h"
#include "controller/usercontroller.h"
#include <QCoreApplication>

namespace App
{
class Application
{
public:
    int run();

public:
    Application(std::unique_ptr<QCoreApplication> application);

private:
    Application(const Application &)            = delete;
    Application(Application &&)                 = delete;
    Application &operator=(const Application &) = delete;
    Application &&operator=(Application &&)     = delete;

private:
    QScopedPointer<QCoreApplication> m_application;
    QScopedPointer<UserController> m_userController;
    QScopedPointer<AuthController> m_authController;
};
} // namespace App

#endif // SERVER_H
