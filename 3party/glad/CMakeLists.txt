cmake_minimum_required(VERSION 3.10)
project(glad)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(GLAD_SOURCE src/glad.c)

add_library(${PROJECT_NAME} STATIC ${GLAD_SOURCE})