cmake_minimum_required(VERSION 3.7)

project(vsgSDL
    VERSION 0.0.0
    DESCRIPTION "VulkanSceneGraph-SDL Integration"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

find_package(vsg 0.4.1 REQUIRED)
find_package(SDL2 REQUIRED)
find_package(vsgXchange QUIET)

add_subdirectory(src/vsgSDL)

add_subdirectory(example)