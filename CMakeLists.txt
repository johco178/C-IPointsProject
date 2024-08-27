cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("C++lPointsProject" LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add source files
set(SOURCE_FILES
    "C++lPointsProject.cpp"
    "hangman.cpp"
    "newwordle.cpp"
    "home.cpp"
    "secretNumber.cpp"
)

# Add header files
set(HEADER_FILES
    "C++lPointsProject.h"
    "hangman.h"
    "newwordle.h"
    "home.h"
    "secretNumber.h"
)

# Add executable
add_executable(C++lPointsProject ${SOURCE_FILES} ${HEADER_FILES})

# Include directories
target_include_directories(C++lPointsProject PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Copy dictionary file to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dictionary.txt
               ${CMAKE_CURRENT_BINARY_DIR}/dictionary.txt
               COPYONLY)

# Add compile definitions for different build types
target_compile_definitions(C++lPointsProject PRIVATE
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

# Set output directory
set_target_properties(C++lPointsProject PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Install target
install(TARGETS C++lPointsProject
    RUNTIME DESTINATION bin
)

# Install dictionary file
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/dictionary.txt
    DESTINATION bin
)

# Enable testing
enable_testing()

# Add a simple test
add_test(NAME C++lPointsProject_test COMMAND C++lPointsProject)