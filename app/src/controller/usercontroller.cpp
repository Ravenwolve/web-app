#include "usercontroller.h"
#include "../dto/userrequestdto.h"
#include <functional>
#include <workflow/HttpUtil.h>

namespace App {
UserController::UserController(QSharedPointer<HTTPServer> server)
    : m_httpServer(server), m_userService(new UserService) {
  using Handler = wfrest::Handler;
  using std::placeholders::_1, std::placeholders::_2;

  m_httpServer->POST("/sign-up", static_cast<Handler>(std::bind(
                                     &UserController::signUp, this, _1, _2)));
  m_httpServer->POST("/auth", static_cast<Handler>(std::bind(
                                  &UserController::auth, this, _1, _2)));
  m_httpServer->POST("/refresh", static_cast<Handler>(std::bind(
                                     &UserController::auth, this, _1, _2)));
}

void UserController::signUp(const HTTPRequest *request,
                            HTTPResponse *response) {
  const auto &query_list = request->json();

  if (query_list.size() != 2 || !query_list.has("usr") ||
      !query_list.has("pwd")) {
    std::cerr << "Bad Request;\n";
    response->set_status(HttpStatusBadRequest);
    return;
  }

  UserRequestDTO dto{QString::fromStdString(query_list["usr"]),
                     QString::fromStdString(query_list["pwd"])};
  if (m_userService->create(dto).has_value()) {
    std::cerr << "User " << dto.m_login.toStdString()
              << " created successfully;\n";
    response->set_status(HttpStatusCreated);
  } else {
    std::cerr << "User " << dto.m_login.toStdString() << " did not create;\n";
    response->set_status(HttpStatusBadRequest);
  }
}

void UserController::auth(const HTTPRequest *request, HTTPResponse *response) {
  // TODO:
}

void UserController::refresh(const HTTPRequest *request,
                             HTTPResponse *response) {
  // TODO:
}
} // namespace App
