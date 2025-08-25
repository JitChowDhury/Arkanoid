# Minimum version required
cmake_minimum_required(VERSION 3.28)

# Project name and language
project(Minesweeper LANGUAGES CXX)

# Where to put the final program
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Get SFML from GitHub
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

# ✅ Collect sources
file(GLOB SRC_FILES src/*.cpp)
file(GLOB HEADER_FILES include/*.h)

# ✅ Define the executable (use your project name here)
add_executable(minesweeper ${SRC_FILES} ${HEADER_FILES})

# Include and C++ standard
target_include_directories(minesweeper PRIVATE include)
target_compile_features(minesweeper PRIVATE cxx_std_17)

# Link SFML
target_link_libraries(minesweeper PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# Copy SFML DLLs after build (Windows only)
if(WIN32)
    add_custom_command(TARGET minesweeper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:sfml-graphics> $<TARGET_FILE_DIR:minesweeper>
    )
endif()

# Compiler warnings
if(MSVC)
    target_compile_options(minesweeper PRIVATE /W4)
else()
    target_compile_options(minesweeper PRIVATE -Wall -Wextra -Wpedantic)
endif()
