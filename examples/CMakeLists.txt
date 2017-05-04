include_directories(
    ${PROJECT_SOURCE_DIR}/include
    )

file(GLOB EXAMPLE_SRCS_ "*.cpp")
foreach(file ${EXAMPLE_SRCS_})
    get_filename_component(example_name ${file} NAME_WE)
    add_executable(${example_name} ${file})
    target_link_libraries(${example_name} timey)
endforeach()
