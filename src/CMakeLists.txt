set(SOURCES
    main.cpp
    yampplayer.cpp
    yampoptions.cpp
    yampportaudio.cpp
    arguments.cpp
)

add_executable(yamp ${SOURCES})

target_include_directories(yamp PRIVATE "${YAMP_SOURCE_DIR}/include")
target_link_libraries(yamp openmpt curses portaudio)

if(ANDROID)
    target_link_libraries(yamp argp)
endif()

