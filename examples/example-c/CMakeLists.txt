# 
#                     Copyright (C) 2020 Clovis Durand
# 
# -----------------------------------------------------------------------------

# Source files --------------------------------------------
file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

message("C Example SOURCES : ${SOURCES}")

# Link directories ----------------------------------------

# Target definition ---------------------------------------
add_executable(${CMAKE_PROJECT_NAME}-c-util
    ${SOURCES}
)
add_dependencies(${CMAKE_PROJECT_NAME}-c-util
    ${CMAKE_PROJECT_NAME}
)
target_link_libraries(${CMAKE_PROJECT_NAME}-c-util
    ${CMAKE_PROJECT_NAME}
)
set_target_properties(${CMAKE_PROJECT_NAME}-c-util PROPERTIES 
    PUBLIC_HEADER "${PUBLIC_HEADERS}"
)

#----------------------------------------------------------------------------
install(TARGETS ${CMAKE_PROJECT_NAME}-c-util
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)
