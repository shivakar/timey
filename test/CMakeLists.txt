# GOOGLETEST_ROOT needs to match PREFIX in CMakeLists.txt.in
set(GOOGLETEST_ROOT ${CMAKE_BINARY_DIR}/vendor/googletest)
configure_file(CMakeLists.txt.in ${GOOGLETEST_ROOT}/CMakeLists.txt)

# Setting up googletest-download project
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${GOOGLETEST_ROOT}
    )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

# Cloning and building googletest
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${GOOGLETEST_ROOT}
    )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Setting variables for include and library paths
set(GTEST_SOURCE_DIR ${GOOGLETEST_ROOT}/src/googletest)
set(GTEST_BINARY_DIR ${GOOGLETEST_ROOT}/src/googletest-build)
set(GTEST_INCLUDE_DIR ${GTEST_SOURCE_DIR}/googletest/include)
set(GTEST_LIBRARY_DIR ${GTEST_BINARY_DIR}/googletest)

# Adding gtest and gtest_main libraries to current project
add_library(gtest STATIC IMPORTED)
set_property(TARGET gtest
    PROPERTY IMPORTED_LOCATION ${GTEST_LIBRARY_DIR}/libgtest.a
    )
add_dependencies(gtest googletest)
add_library(gtest_main STATIC IMPORTED)
set_property(TARGET gtest_main
    PROPERTY IMPORTED_LOCATION ${GTEST_LIBRARY_DIR}/libgtest_main.a
    )
add_dependencies(gtest_main googletest)

# Adding pthreads since it is required to link against googletest
find_package(Threads REQUIRED)

# Setting include_directories
include_directories (
    ${GTEST_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    )

# Adding all .cpp files to test executable
file(GLOB TEST_SRCS_
    "*.cpp"
    )
add_executable(${CMAKE_PROJECT_NAME}_test ${TEST_SRCS_})
target_link_libraries(${CMAKE_PROJECT_NAME}_test ${CMAKE_PROJECT_NAME} gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})

add_test(NAME ${CMAKE_PROJECT_NAME}_test COMMAND ${CMAKE_PROJECT_NAME}_test)
