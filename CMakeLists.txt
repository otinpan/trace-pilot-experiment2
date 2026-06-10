cmake_minimum_required(VERSION 3.16)

project(AHC062 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ahc062
    src/main.cpp
    src/logger.cpp
    src/simulator.cpp
    src/state.cpp
    src/strategy/strategy.cpp
)

target_include_directories(ahc062 PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

set_target_properties(ahc062 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)


