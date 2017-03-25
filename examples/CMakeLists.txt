include_directories(
    ${PROJECT_SOURCE_DIR}/include
    )

if(BUILD_EXAMPLES)
    add_executable(example_timer example_timer.cpp)
    target_link_libraries(example_timer timey)
endif()
