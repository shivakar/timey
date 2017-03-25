cmake_minimum_required(VERSION 2.8)

project(timey)
set(PROJECT_NAME "timey")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install)
endif()

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include
    DESTINATION .
    COMPONENT headers
    )

#add_subdirectory(src)
#add_subdirectory(test)
add_subdirectory(examples)
