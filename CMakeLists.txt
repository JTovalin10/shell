cmake_minimum_required(VERSION 3.13)

project(shell-starter-cpp)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(shell ${SOURCE_FILES})

target_include_directories(shell PRIVATE src /opt/homebrew/opt/readline/include)

target_link_directories(shell PRIVATE /opt/homebrew/opt/readline/lib)

target_link_libraries(shell PRIVATE readline)
