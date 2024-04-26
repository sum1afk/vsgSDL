set(SOURCES
    main.cpp
)

set(HEADERS
)

add_executable(vsgSDLexample ${SOURCES} ${HEADERS})

target_link_libraries(vsgSDLexample vsgSDL)

if (vsgXchange_FOUND)
    target_compile_definitions(vsgSDLexample PRIVATE vsgXchange_FOUND)
    target_link_libraries(vsgSDLexample vsgXchange::vsgXchange)
endif()

target_compile_definitions(vsgSDLexample PRIVATE SDL_MAIN_HANDLED)

install(TARGETS vsgSDLexample DESTINATION bin)

add_custom_command (
    TARGET vsgSDLexample POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy
            "${CMAKE_CURRENT_LIST_DIR}/models/teapot.vsgt" 
            "$<TARGET_FILE_DIR:vsgSDLexample>/models/teapot.vsgt"
            USES_TERMINAL COMMAND_EXPAND_LISTS
)