#include <SFML/Graphics.hpp>
#include "inc/system.hpp"
#include "inc/game.hpp"
#include "inc/gui.hpp"

bool debugMode = true;
sf::Font defaultFont;
sf::Vector2i resolution;

int main()
{
    enable_vtp();
    srand(time(0));

    log("Game Started",debugMode);

    resolution = GetDesktopResolution();
    sf::RenderWindow window;
    unsigned short int videoMode = 2;

    //defaultFont.loadFromFile("ST-SimpleSquare.otf");

    if(videoMode == 1)
    {
        window.create(sf::VideoMode(1280, 720), "Snake: Frenzy", sf::Style::Titlebar | sf::Style::Close); /* 16:9 */
    }
    else if(videoMode == 2)
    {
        window.create(sf::VideoMode(1280, 800), "Snake: Frenzy", sf::Style::Titlebar | sf::Style::Close); /* 16:10 */
    }
    else if(videoMode == 3)
    {
        window.create(sf::VideoMode(1280, 720), "Snake: Frenzy", sf::Style::Fullscreen | sf::Style::Close); /* 16:9 */
    }
    else if(videoMode == 4)
    {
        window.create(sf::VideoMode(1280, 800), "Snake: Frenzy", sf::Style::Fullscreen | sf::Style::Close); /* 16:10 */
    }
    else
    {
        window.create(sf::VideoMode(resolution.x, resolution.y), "Snake: Frenzy", sf::Style::Titlebar | sf::Style::Close);
    }

    mainMenuUI(window);
    //gameMenuUI(window, true);

    log("Game Exited",debugMode);
    return EXIT_SUCCESS;
}

//memory issue fixed but flow of the game must be improved
