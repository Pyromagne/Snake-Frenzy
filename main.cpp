#include <SFML/Graphics.hpp>
#include "inc/system.hpp"
#include "inc/game.hpp"
#include "inc/gui.hpp"

bool debugMode = true;

int main()
{
    enable_vtp();
    log("Game Started",debugMode);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Frenzy", sf::Style::Titlebar | sf::Style::Close);

    mainMenuUI(window);

    log("Game Exited",debugMode);
    return EXIT_SUCCESS;
}

//there is a memory error when exiting a game, low priority for now.
//it is probably because of poor control flow of a game in gui.cpp, the snake object is not deallocated properly