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

# Create test executables from each .cpp file
file(GLOB TEST_SRCS_ "*.cpp")
foreach(file ${TEST_SRCS_})
    get_filename_component(test_name ${file} NAME_WE)
    add_executable(${test_name} ${file})
    target_link_libraries(${test_name} ${CMAKE_PROJECT_NAME} gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

if(ENABLE_COVERAGE)
    set(coverage_info_path "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}_coverage.info")
    set(coverage_cleaned_path "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}_coverage.cleaned")
    set(coverage_output_path "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}_coverage")
    ADD_CUSTOM_TARGET(coverage
        # Build test executables
        COMMAND ${CMAKE_COMMAND} --build .

        # Clean any previous lcov outputs
        COMMAND ${LCOV_PATH} --directory . --zerocounters

        # Run all tests
        COMMAND ${CMAKE_COMMAND} --build . --target test

        # Capture lcov counters
        COMMAND ${LCOV_PATH} --directory . --capture --output-file ${coverage_info_path}

        # Remove system and vendor libraries from the coverage report
        COMMAND ${LCOV_PATH} --remove ${coverage_info_path} 'test/*' '/usr/*' '/opt/local/*' '/opt/apps/*' 'vendor/*' 'gtest/*' ${LCOV_REMOVE_EXTRA} --output-file ${coverage_cleaned_path}

        # Generate report
        COMMAND ${GENHTML_PATH} -o ${coverage_output_path} ${coverage_cleaned_path}

        # Cleanup
        COMMAND ${CMAKE_COMMAND} -E remove ${coverage_info_path} ${coverage_cleaned_path}

        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()
