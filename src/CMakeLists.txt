set(SOURCES
    main.cpp
    args.cpp
    ui.cpp
)

add_executable(yamp ${SOURCES})

target_include_directories(yamp PRIVATE "${YAMP_SOURCE_DIR}/include")
target_link_libraries(yamp openmpt curses pulse-simple)
