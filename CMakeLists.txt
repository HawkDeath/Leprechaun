cmake_minimum_required(VERSION 3.20)
project(Leprechaun)

set(CMAKE_CXX_STANDARD_REQUIRED 20)

option(LEPRECHAUN_BUILD_DEMO "Leprechaun Demo" OFF)

file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/output")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/output/bin")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/output/lib")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/output/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/output/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/output/lib")

add_subdirectory(3party)
add_subdirectory(LeprechaunLib)
#if(LEPRECHAUN_BUILD_DEMO)
    add_subdirectory(demo)
    add_dependencies(demo LeprechaunLib)
#endif(LEPRECHAUN_BUILD_DEMO)


if(MSVC)
 set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT demo)
endif()