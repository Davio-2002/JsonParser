cmake_minimum_required(VERSION 3.20)
project(JsonParser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ../include/core
        ../include/model
        ../include/utils
)

file(GLOB_RECURSE CORE_SRC src/core/*.cpp)
file(GLOB_RECURSE MODEL_SRC src/model/*.cpp)
file(GLOB_RECURSE UTILS_SRC src/utils/*.cpp)

set(MAIN_SRC src/main.cpp)

add_executable(JsonParser ${MAIN_SRC} ${CORE_SRC} ${MODEL_SRC} ${UTILS_SRC})
