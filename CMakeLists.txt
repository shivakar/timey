cmake_minimum_required(VERSION 3.0)

project(timey)
set(PROJECT_NAME "timey")
set(PROJECT_VERSION "0.1.0")

option(BUILD_EXAMPLES "Build examples." ON)
option(BUILD_TESTS "Build tests." ON)
option(BUILD_DOCUMENTATION "Build and install HTML documentation." ON)
option(ENABLE_CXX_STRICT "Enable strict compiler rules." OFF)
option(ENABLE_COVERAGE "Enable code coverage analysis. **Note** Sets current build to DEBUG." OFF)

# Prerequisites
if(BUILD_TESTS)
    # pthread is required by googletest
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    find_package(Threads REQUIRED)
endif()
if(ENABLE_COVERAGE)
    find_program(LCOV_PATH lcov)
    if(NOT LCOV_PATH)
        message(FATAL_ERROR "lcov is needed to generate coverage.")
    endif()
    find_program(GENHTML_PATH genhtml)
    if(NOT GENHTML_PATH)
        message(FATAL_ERROR "genhtml is needed to generate coverage report.")
    endif()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -pedantic -Wextra")
if(BUILD_STRICT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
if(ENABLE_COVERAGE)
    message("INFO: Code coverage enabled. Switching to DEBUG build.")
    set(CMAKE_BUILD_TYPE "Debug")
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
