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

    return EXIT_SUCCESS;
}
