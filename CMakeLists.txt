cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
project(cars)

find_package(SFML 3.0 CONFIG REQUIRED
    COMPONENTS
        System
        Window
        Graphics
        Audio
)

set(SOURCES
    main.cpp
    src/car.cpp
    src/Track.cpp
    src/PhysicsObject.cpp
)

add_executable(main ${SOURCES})

target_link_libraries(main PRIVATE
    SFML::System
    SFML::Window
    SFML::Graphics
    SFML::Audio
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/music)
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/music/music.mp3
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/music/music.mp3
)

file(COPY resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
