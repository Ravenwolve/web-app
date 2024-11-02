#ifndef USERMAPPER_H
#define USERMAPPER_H

#include "dto/userresponsedto.h"
#include "entity/user.h"

namespace App
{
class UserMapper
{
public:
    static auto toResponseDTO(const User &user) -> UserResponseDTO;
};
} // namespace App

#endif
