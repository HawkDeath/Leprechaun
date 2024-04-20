cmake_minimum_required(VERSION 3.20)
project(demo)

# link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(DEMO_SRC main.cpp)

add_executable(${PROJECT_NAME} ${DEMO_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} PRIVATE 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/3party>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/LeprechaunLib/include>)
MESSAGE(STATUS "libdirs: " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/LeprechaunLib.lib volk vulkan)