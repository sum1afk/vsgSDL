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


install(TARGETS vsgSDLexample DESTINATION bin)