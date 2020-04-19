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
# add_test(${CMAKE_PROJECT_NAME}_test_default ${CMAKE_PROJECT_NAME}-tests -1)

# FileFiller string parsing tests
add_test(${CMAKE_PROJECT_NAME}_singleTagParsingTest ${CMAKE_PROJECT_NAME}-tests 1)
add_test(${CMAKE_PROJECT_NAME}_duplicateTagParsingTest ${CMAKE_PROJECT_NAME}-tests 2)
add_test(${CMAKE_PROJECT_NAME}_multipleTagParsingTest ${CMAKE_PROJECT_NAME}-tests 3)
add_test(${CMAKE_PROJECT_NAME}_multipleTagParsingTest2 ${CMAKE_PROJECT_NAME}-tests 4)

# FileFiller file parsing tests
add_test(${CMAKE_PROJECT_NAME}_fileMultipleTagParsingTest ${CMAKE_PROJECT_NAME}-tests
    5
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleTags/multipleTags.txt.in
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleTags/multipleTags-expected.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleTags/multipleTags-output.txt
)
add_test(${CMAKE_PROJECT_NAME}_fileMultipleLinesParsingTest ${CMAKE_PROJECT_NAME}-tests
    6
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines.txt.in
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-expected.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-output.txt
)

# FileFillerTagFactory tests
add_test(${CMAKE_PROJECT_NAME}_buildTagMapParsingTest ${CMAKE_PROJECT_NAME}-tests 7)
add_test(${CMAKE_PROJECT_NAME}_buildTagMapFileParsingTest ${CMAKE_PROJECT_NAME}-tests
    8
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/FileFillerTagFactory/tags.csv
)

# FileFillerTagFactory & FileFiller combined tests
add_test(${CMAKE_PROJECT_NAME}_tagMapFileParsingAndOutputGenerationTest ${CMAKE_PROJECT_NAME}-tests
    9
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines.txt.in
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-expected.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-output.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-tags.csv
)

add_test(${CMAKE_PROJECT_NAME}_tagMapFileParsingAndOutputGenerationTestMissingEoLSemiColonTest ${CMAKE_PROJECT_NAME}-tests
    10
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines.txt.in
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-expected.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-output.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-tags-missing-eol-semi-colon.csv
)

add_test(${CMAKE_PROJECT_NAME}_tagMapFileParsingAndOutputGenerationTestMissingTagTest ${CMAKE_PROJECT_NAME}-tests
    11
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-tags-missing-tag.csv
)

add_test(${CMAKE_PROJECT_NAME}_tagMapFileParsingAndOutputGenerationTestMissingValueTest ${CMAKE_PROJECT_NAME}-tests
    12
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines.txt.in
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-expected-missing-value.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-output.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-tags-missing-value.csv
)

add_test(${CMAKE_PROJECT_NAME}_tagMapFileParsingAndOutputGenerationTestMissingValueAndSemiColonTest ${CMAKE_PROJECT_NAME}-tests
    13
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines.txt.in
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-expected-missing-value.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-output.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/multipleLines/multipleLines-tags-missing-value-and-semi-colon.csv
)

# REMOVE_LINE
add_test(${CMAKE_PROJECT_NAME}_removeLineTest ${CMAKE_PROJECT_NAME}-tests
    14
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/removeLines/removeLines.txt.in
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/removeLines/removeLines-expected.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/removeLines/removeLines-output.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/removeLines/removeLines-tags.csv
)

add_test(${CMAKE_PROJECT_NAME}_removeLineTest_EoF_NL ${CMAKE_PROJECT_NAME}-tests
    15
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/removeLines-EoF-NL/removeLines.txt.in
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/removeLines-EoF-NL/removeLines-expected.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/removeLines-EoF-NL/removeLines-output.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/removeLines-EoF-NL/removeLines-tags.csv
)

add_test(${CMAKE_PROJECT_NAME}_readFileTest ${CMAKE_PROJECT_NAME}-tests
    16
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/readFile/OSCOGenOD_Values.in.c
)

add_test(${CMAKE_PROJECT_NAME}_readFileTest2 ${CMAKE_PROJECT_NAME}-tests
    17
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/readFile/OSCOGenOD_MaxValues.in.c
)

add_test(${CMAKE_PROJECT_NAME}_readFileTest3 ${CMAKE_PROJECT_NAME}-tests
    18
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/readFile/OSCOGenOD_Values.in.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/tests/readFile/OSCOGenOD_MaxValues.in.c
)
