cmake_minimum_required(VERSION 3.26)

project(SnakeFrenzy)

set(CMAKE_CXX_STANDARD 17)

set(SFML_INCLUDE_DIR "" CACHE PATH "Path to SFML include directory")
set(SFML_LIB_DIR "" CACHE PATH "Path to SFML lib directory")

include_directories(
        ${SFML_INCLUDE_DIR}
        lib/ColorEscape
)

add_executable(SnakeFrenzy
        main.cpp
        include/game.hpp
        include/system.hpp
        include/gui.hpp
        src/game.cpp
        src/gui.cpp
        src/system.cpp
        #temporary include button libs src in compilation
        sfmlButton/include/button.hpp
        sfmlButton/include/ellipseButton.hpp
        sfmlButton/include/rectButton.hpp
        sfmlButton/include/sfmlButton.hpp
        sfmlButton/src/button.cpp
        sfmlButton/src/ellipseButton.cpp
        sfmlButton/src/rectButton.cpp
)

target_link_directories(SnakeFrenzy
        PUBLIC
        ${SFML_LIB_DIR}
        lib/ColorEscape
)

target_link_libraries(SnakeFrenzy
        PUBLIC
        sfml-audio-d
        sfml-graphics-d
        sfml-main-d
        sfml-network-d
        sfml-system-d
        sfml-window-d
        ColorEscape
)
