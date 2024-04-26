cmake_minimum_required(VERSION 3.7)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

project(vsgSDL
    VERSION 0.0.0
    DESCRIPTION "VulkanSceneGraph-SDL Integration"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

find_package(vsg CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(vsgXchange QUIET)

add_subdirectory(src/vsgSDL)

add_subdirectory(example)