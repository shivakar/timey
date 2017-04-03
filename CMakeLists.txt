cmake_minimum_required(VERSION 3.0)

project(timey)
set(PROJECT_NAME "timey")
set(PROJECT_VERSION "0.0.2")

option(BUILD_EXAMPLES "Build examples." ON)
option(BUILD_TESTS "Build tests." ON)
option(BUILD_DOCUMENTATION "Build and install HTML documentation." ON)
option(ENABLE_CXX_STRICT "Enable strict compiler rules." OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -pedantic -Wextra")
if(BUILD_STRICT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

# Set the default installation prefix to /opt/apps/timey/<version>
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /opt/apps/{PROJECT_NAME}/{PROJECT_VERSION})
endif()

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include
    DESTINATION .
    COMPONENT headers
    )

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

if (BUILD_DOCUMENTATION)
    add_subdirectory(doc)
endif()
