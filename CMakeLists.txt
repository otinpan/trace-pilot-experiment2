cmake_minimum_required(VERSION 3.16)

project(AHC046 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ahc046
    src/main.cpp
    src/logger.cpp
    src/navigator.cpp
    src/strategy/strategy.cpp
    src/strategy/greedy.cpp
    src/strategy/initial_position.cpp
)

target_include_directories(ahc046 PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

set_target_properties(ahc046 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

