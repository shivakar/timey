include_directories(
    ${PROJECT_SOURCE_DIR}/include
    )

add_executable(timer_basics timer_basics.cpp)
target_link_libraries(timer_basics timey)
