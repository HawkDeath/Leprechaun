cmake_minimum_required(VERSION 3.10)
project(LeprechaunLib)

include_directories(${CMAKE_SOURCE_DIR}/3party)
include_directories(${CMAKE_SOURCE_DIR}/3party/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(INPUT_SOURCES
    src/Input/Input.cpp)

set(WINDOW_SOURCES
    src/Window/Window.cpp)

set(BASE_APPLICATION_SOURCES
    src/BaseApplication.cpp)

set(ENGINE_LIB_SOURCES ${BASE_APPLICATION_SOURCES} ${WINDOW_SOURCES} ${INPUT_SOURCES})

add_library(${PROJECT_NAME} STATIC ${ENGINE_LIB_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad glm spdlog imgui stb_image freetype)