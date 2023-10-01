#include <SFML/Graphics.hpp>
#include "inc/system.hpp"
#include "inc/game.hpp"
#include "inc/gui.hpp"

bool debugMode = true;
sf::Font defaultFont;
sf::Vector2i resolution;
sf::Vector2f snakeSize(25.f, 25.f);

//TEST GPG SIGN IN GIT a1

int main(int argc, char* argv[])
{
    enable_vtp();
    srand(time(0));

    log("Game Started",debugMode);

    resolution = GetDesktopResolution();
    sf::RenderWindow window;
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    //defaultFont.loadFromFile("ST-SimpleSquare.otf");

     if (argc >= 2)
     {
        unsigned short videoMode = std::atoi(argv[1]);
        videoMode = 1;
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
            case 5:
                window.create(sf::VideoMode(resolution.x, resolution.y), "Snake: Frenzy", sf::Style::Fullscreen | sf::Style::Close);
            break;
            default:
                window.create(sf::VideoMode(1280, 720), "Snake: Frenzy", sf::Style::Titlebar | sf::Style::Close); /* 16:9 */
            break;
        }
    }
    else
    {
        window.create(sf::VideoMode(1280, 720), "Snake: Frenzy", sf::Style::Titlebar | sf::Style::Close); /* 16:9 */
    }

    mainMenuUI(window);

    log("Game Exited",debugMode);
    return EXIT_SUCCESS;
}

//memory issue fixed but flow of the game must be improved
