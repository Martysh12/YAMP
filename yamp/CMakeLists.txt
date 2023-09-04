set(SOURCES
    main.cpp
    yampplayer.cpp
    yampoptions.cpp
    yampportaudio.cpp
)

set(HEADERS
    yampplayer.h
    yampoptions.h
    yampportaudio.h
)

add_executable(yamp ${SOURCES} ${HEADERS})

target_compile_options(yamp PRIVATE -Wall -Wextra)

target_link_libraries(yamp openmpt portaudio)

if(ANDROID)
    target_link_libraries(yamp argp)
endif()

install(TARGETS yamp RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
