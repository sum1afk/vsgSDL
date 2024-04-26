set(HEADERS
    ${CMAKE_SOURCE_DIR}/include/vsgSDL/export.hpp
    ${CMAKE_SOURCE_DIR}/include/vsgSDL/keyboard.hpp
    ${CMAKE_SOURCE_DIR}/include/vsgSDL/mouse.hpp
    ${CMAKE_SOURCE_DIR}/include/vsgSDL/version.hpp
    ${CMAKE_SOURCE_DIR}/include/vsgSDL/window.hpp
)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/vsgSDL/export.cpp
    ${CMAKE_SOURCE_DIR}/src/vsgSDL/keyboard.cpp
    ${CMAKE_SOURCE_DIR}/src/vsgSDL/mouse.cpp
    ${CMAKE_SOURCE_DIR}/src/vsgSDL/version.cpp
    ${CMAKE_SOURCE_DIR}/src/vsgSDL/window.cpp
)

add_library(vsgSDL ${HEADERS} ${SOURCES})

set_property(TARGET vsgSDL PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET vsgSDL PROPERTY CXX_STANDARD 17)

target_include_directories(vsgSDL PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(ANDROID)
    target_compile_definitions(vsgSDL PRIVATE VSGSDL_PLATFORM_ANDROID)
elseif(IOS)
    target_compile_definitions(vsgSDL PRIVATE VSGSDL_PLATFORM_IOS)
elseif(WIN32)
    target_compile_definitions(vsgSDL PRIVATE VSGSDL_PLATFORM_WIN32 SDL_MAIN_HANDLED)
elseif(APPLE)
    target_compile_definitions(vsgSDL PRIVATE VSGSDL_PLATFORM_APPLE)
else()
    target_compile_definitions(vsgSDL PRIVATE VSGSDL_PLATFORM_XCB)
endif()

target_link_libraries(vsgSDL
    vsg::vsg
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

install(TARGETS vsgSDL
    DESTINATION lib
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/vsgSDL
    DESTINATION include
)