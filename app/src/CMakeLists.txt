find_package(wfrest REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Sql)
find_package(jwt-cpp CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRC
  application/main.cpp
  
  application/application.cpp
  
  controller/authcontroller.cpp

  repository/userrepository.cpp
  
  service/authservice.cpp

  mapper/usermapper.cpp
  
  utility/passwordbuilder.cpp
  utility/functional.cpp
)

set(HEADER
  application/application.h
  
  controller/authcontroller.h

  service/authservice.h

  repository/userrepository.h
  repository/config.h

  entity/user.h
  dto/signinrequestdto.h
  dto/signuprequestdto.h
  dto/refreshrequestdto.h
  dto/signinresponsedto.h
  dto/signupresponsedto.h
  dto/refreshresponsedto.h

  utility/alias.h
  utility/passwordbuilder.h
  utility/functional.h

  mapper/usermapper.h
)

add_executable(${PROJECT_NAME} ${SRC} ${HEADER})

target_link_libraries(${PROJECT_NAME} PRIVATE
  wfrest
  workflow
  jwt-cpp::jwt-cpp
  Qt5::Sql
)
