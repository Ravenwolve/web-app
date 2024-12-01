#ifndef USERMAPPER_H
#define USERMAPPER_H

#include "dto/signupresponsedto.h"
#include "entity/user.h"

namespace App
{
class UserMapper
{
public:
    static auto toResponseDTO(const User &user) -> SignUpResponseDTO;
};
} // namespace App

#endif
