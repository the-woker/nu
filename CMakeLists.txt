cmake_minimum_required(VERSION 3.10)
project(nu)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(nu src/main.cpp)

target_compile_features(nu PRIVATE cxx_std_20)

target_include_directories(nu
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

install(TARGETS nu DESTINATION bin)
