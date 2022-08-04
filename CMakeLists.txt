cmake_minimum_required(VERSION 3.2)
project(my_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_CURRENT_LIST_DIR}/my_class/my_class.cmake)

add_executable(${PROJECT_NAME}
                main.cpp
                ${MY_CLASS})

target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra)