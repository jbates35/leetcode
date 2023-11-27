cmake_minimum_required(VERSION 3.6)
project(romanToInt)

# Set the C standard to C99
set(CMAKE_C_STANDARD 99)

set(CMAKE_BUILD_TYPE Debug)
# Allow vscode to find compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add executable target
add_executable(romanToInt main.c)
