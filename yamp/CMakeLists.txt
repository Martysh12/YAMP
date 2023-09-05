set(SOURCES
    main.cpp
    player.cpp
    playbackoptions.cpp
)

set(HEADERS
    player.h
    playbackoptions.h
    backend.h
)

set(LIBS
    openmpt
)

find_library(PORTAUDIO portaudio)
find_library(PULSEAUDIO pulseaudio)

# Check for available audio backends
if (PORTAUDIO)
    message(STATUS "portaudio audio backend found")
    set(SOURCES ${SOURCES} audio_backends/portaudio.cpp)
    set(LIBS ${LIBS} portaudio)
elseif(PULSEAUDIO)
    message(STATUS "pulseaudio audio backend found")
    set(SOURCES ${SOURCES} audio_backends/pulseaudio.cpp)
    set(LIBS ${LIBS} pulseaudio)
endif()

# Add argp on Termux
if(ANDROID)
    set(LIBS ${LIBS} argp)
endif()

add_executable(yamp ${SOURCES} ${HEADERS})

target_compile_options(yamp PRIVATE -Wall -Wextra)

target_link_libraries(yamp ${LIBS})


install(TARGETS yamp RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
