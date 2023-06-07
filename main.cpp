#include <SFML/Graphics.hpp>
#include "sfmlbutton.hpp"

#include "inc/system.hpp"

void mainMenuUI(sf::RenderWindow& window);
bool debugMode = false;

int main()
{
    enable_vtp();
    debugMode = true;
    if(debugMode)log("Game Started");

    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake Frenzy", sf::Style::Titlebar | sf::Style::Close);

    mainMenuUI(window);

    return EXIT_SUCCESS;
}

void mainMenuUI(sf::RenderWindow& window)
{
    sf::Font lemonMilkFNT;
    lemonMilkFNT.loadFromFile("LEMONMILK-Regular.otf");

    RectButton playBTN(lemonMilkFNT, true, sf::Vector2f(50.f, 50.f));
    playBTN.setLabelColor(sf::Color::White, sf::Color::Green, sf::Color::Green);
    playBTN.setButtonColor(sf::Color::Transparent);
    playBTN.setButtonLabel(50.f, "Play");

    RectButton exitBTN(lemonMilkFNT, true, sf::Vector2f(50.f, 150.f));
    exitBTN.setLabelColor(sf::Color::White, sf::Color::Red, sf::Color::Red);
    exitBTN.setButtonColor(sf::Color::Transparent);
    exitBTN.setButtonLabel(50.f, "Exit");

    sf::Texture backgroundTEX;
    backgroundTEX.loadFromFile("background.png");

    sf::Sprite backgroundSPR;
    backgroundSPR.setTexture(backgroundTEX);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            playBTN.getButtonStatus(window, event);
            exitBTN.getButtonStatus(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (exitBTN.isPressed)
            {
                window.close();
            }
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(backgroundSPR);

        playBTN.draw(window);
        exitBTN.draw(window);

        // Update the window
        window.display();
    }
}
