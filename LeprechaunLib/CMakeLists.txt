cmake_minimum_required(VERSION 3.10)
project(LeprechaunLib)

include_directories(${CMAKE_SOURCE_DIR}/3party)
include_directories(${CMAKE_SOURCE_DIR}/3party/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(ENGINE_LIB_SOURCES main.cpp)

# add_library(${PROJECT_NAME} STATIC ${ENGINE_LIB_SOURCES})
add_executable(${PROJECT_NAME} ${ENGINE_LIB_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad glm spdlog)