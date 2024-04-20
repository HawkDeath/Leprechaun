cmake_minimum_required(VERSION 3.20)
project(LeprechaunLib)

set(CMAKE_CXX_STANDARD_REQUIRED 20)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(COMMON_SOURCE
    src/Log/Logger.cpp
)

set(INPUT_SOURCES
    src/Input/Input.cpp)

set(WINDOW_SOURCES
    src/Window/Window.cpp)

set(RENDERER_SOURCES

    )

set(BASE_APPLICATION_SOURCES
    src/BaseApplication.cpp)

set(ENGINE_LIB_SOURCES ${BASE_APPLICATION_SOURCES} ${RENDERER_SOURCES} ${WINDOW_SOURCES} ${INPUT_SOURCES} ${COMMON_SOURCE})

add_library(${PROJECT_NAME} STATIC ${ENGINE_LIB_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../3party>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../3party/Vulkan-Headers/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
target_link_libraries(${PROJECT_NAME} PRIVATE volk vulkan glfw glm spdlog imgui stb_image freetype)