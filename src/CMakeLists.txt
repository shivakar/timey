include_directories(
    ${PROJECT_SOURCE_DIR}/include
    )

set(LSRCS timer.cpp)

# Install headers
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include
    DESTINATION .
    COMPONENT headers
    )

# Build and install static library
add_library(${PROJECT_NAME} STATIC ${LSRCS})
install(
    TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT lib
    )

# Build and install shared library if requested
if(ENABLE_SHARED)
    add_library(${PROJECT_NAME}Shared SHARED ${LSRCS})
    set_target_properties(
        ${PROJECT_NAME}Shared
        PROPERTIES OUTPUT_NAME ${PROJECT_NAME}
        CLEAN_DIRECT_OUTPUT 1
        )
    install(
        TARGETS ${PROJECT_NAME}Shared
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        COMPONENT lib
        )
endif()
