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
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    unsigned short int videoMode = 1;

    //defaultFont.loadFromFile("ST-SimpleSquare.otf");

    switch(videoMode)
    {
        case 1:
            window.create(sf::VideoMode(1280, 720), "Snake: Frenzy", sf::Style::Titlebar | sf::Style::Close); /* 16:9 */
        break;
        case 2:
            window.create(sf::VideoMode(1280, 800), "Snake: Frenzy", sf::Style::Titlebar | sf::Style::Close); /* 16:10 */
        break;
        case 3:
            window.create(sf::VideoMode(1280, 720), "Snake: Frenzy", sf::Style::Fullscreen | sf::Style::Close); /* 16:9 */
        break;
        case 4:
            window.create(sf::VideoMode(1280, 800), "Snake: Frenzy", sf::Style::Fullscreen | sf::Style::Close); /* 16:10 */
        break;
        default:
            window.create(sf::VideoMode(resolution.x, resolution.y), "Snake: Frenzy", sf::Style::Fullscreen | sf::Style::Close);
        break;
    }

    mainMenuUI(window);

    log("Game Exited",debugMode);
    return EXIT_SUCCESS;
}

//memory issue fixed but flow of the game must be improved
