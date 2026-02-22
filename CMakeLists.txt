cmake_minimum_required(VERSION 3.10)
project(OrangyEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)

find_package(glfw3 QUIET)
if(NOT glfw3_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW glfw3)
endif()

# Asegúrate de que el archivo esté en src/main.cpp
add_executable(OrangyEngine src/main.cpp)

target_link_libraries(OrangyEngine 
    PRIVATE 
    OpenGL::GL 
    Threads::Threads
)

if(glfw3_FOUND)
    target_link_libraries(OrangyEngine PRIVATE glfw)
elseif(GLFW_FOUND)
    target_link_libraries(OrangyEngine PRIVATE ${GLFW_LIBRARIES})
endif()
