#include "usermapper.h"

namespace App {
UserResponseDTO UserMapper::toResponseDTO(const User &user) {
  UserResponseDTO dto;

  dto.m_id = user.m_id;
  dto.m_login = user.m_login;
  dto.m_password = user.m_password;
  dto.m_salt = user.m_salt;

  return dto;
}
} // namespace App
