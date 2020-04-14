# 
#                     Copyright (C) 2020 Clovis Durand
# 
# -----------------------------------------------------------------------------

# Definitions ---------------------------------------------
add_definitions(-DTEST)

# Requirements --------------------------------------------

# Header files --------------------------------------------
file(GLOB_RECURSE PUBLIC_HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc/*.hpp
)
set(HEADERS
    ${PUBLIC_HEADERS}
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc
)

# Source files --------------------------------------------
file(GLOB_RECURSE TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# Target definition ---------------------------------------
add_executable(${CMAKE_PROJECT_NAME}-tests
    ${TEST_SOURCES}
)
add_dependencies(${CMAKE_PROJECT_NAME}-tests
    ${CMAKE_PROJECT_NAME}
)
target_link_libraries(${CMAKE_PROJECT_NAME}-tests
    ${CMAKE_PROJECT_NAME}
)

# Test definition -----------------------------------------
#add_test( testname Exename arg1 arg2 ... )
add_test( ${CMAKE_PROJECT_NAME}_test_default ${CMAKE_PROJECT_NAME}-tests -1 )
add_test( ${CMAKE_PROJECT_NAME}_singleTagParsingTest ${CMAKE_PROJECT_NAME}-tests 0 )
add_test( ${CMAKE_PROJECT_NAME}_duplicateTagParsingTest ${CMAKE_PROJECT_NAME}-tests 1 )
add_test( ${CMAKE_PROJECT_NAME}_multipleTagParsingTest ${CMAKE_PROJECT_NAME}-tests 2 )
add_test( ${CMAKE_PROJECT_NAME}_multipleTagParsingTest2 ${CMAKE_PROJECT_NAME}-tests 3 )
