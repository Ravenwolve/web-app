find_package(wfrest REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(jwt-cpp CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRC
  application/main.cpp
  
  application/application.cpp
  
  controller/usercontroller.cpp

  repository/userrepository.cpp
  
  service/userservice.cpp

  mapper/usermapper.cpp
  
  utility/passwordbuilder.cpp
)

set(HEADER
  application/application.h
  
  controller/usercontroller.h
  
  service/userservice.h

  repository/userrepository.h
  repository/config.h

  entity/user.h
  dto/userrequestdto.h
  dto/userresponsedto.h

  utility/alias.h
  utility/passwordbuilder.h

  mapper/usermapper.h
)

add_executable(${PROJECT_NAME} ${SRC} ${HEADER})

target_link_libraries(${PROJECT_NAME} PRIVATE
  wfrest
  workflow
  jwt-cpp::jwt-cpp
  Qt6::Sql
)
