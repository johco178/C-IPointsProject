cmake_minimum_required(VERSION 3.8)
project("C++lPointsProject" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Code coverage flags (only for GCC/Clang)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# Main application source files
set(MAIN_SOURCES
    C++lPointsProject.cpp
    hangman.cpp
    newwordle.cpp
    secretNumber.cpp
    TicTacToe.cpp
    home.cpp
)

# Test source files
set(TEST_SOURCES
    runAllTest.cpp
    test_hangman.cpp
    test_newwordle.cpp
    test_tictactoe.cpp
    secretNumTests.cpp
)

# Add main executable
add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

# Add test executable
add_executable(${PROJECT_NAME}_test 
    ${TEST_SOURCES} 
    hangman.cpp 
    newwordle.cpp 
    TicTacToe.cpp 
    secretNumber.cpp
)

# Common settings for both executables
foreach(TARGET ${PROJECT_NAME} ${PROJECT_NAME}_test)
    target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_definitions(${TARGET} PRIVATE
        $<$<CONFIG:Debug>:_DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
        UNIT_TESTING
    )
    set_target_properties(${TARGET} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endforeach()

# Copy dictionary file to build directory
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dictionary.txt")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dictionary.txt
                   ${CMAKE_CURRENT_BINARY_DIR}/dictionary.txt
                   COPYONLY)
endif()

# Copy dictionary file to build directory
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/wordlength5.txt")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wordlength5.txt
                   ${CMAKE_CURRENT_BINARY_DIR}/wordlength5.txt
                   COPYONLY)
endif()


# Enable testing
enable_testing()

# Add test
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)