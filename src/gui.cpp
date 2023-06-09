#include "../inc/gui.hpp"
#include "../inc/game.hpp"

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
            if (playBTN.isPressed)
            {
                gameMenuUI(window);
            }

            //snake.dpad();

        }

        //snake.updatePosition(150.f);

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(backgroundSPR);

        playBTN.draw(window);
        exitBTN.draw(window);
        //snake.drawSnake(window);

        // Update the window
        window.display();
    }
}

void gameMenuUI(sf::RenderWindow& window)
{
    SnakeClass snake;
    snake.skin.loadFromFile("snakeSkin.png");
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                snake.~SnakeClass();
                mainMenuUI(window);
            }

            snake.dpad();

        }

        snake.updatePosition(50.f);

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(snake.head.node);

        snake.drawSnake(window);

        // Update the window
        window.display();
    }
}

// BOILERPLATE FOR GAME LOOP

/* while (window.isOpen())
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        sampleBTN.getButtonStatus(window, event);

        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if (sampleBTN.isPressed)
        {
            window.close();
        }


    }


    // Clear screen
    window.clear();

    // Draw the sprite
    sampleBTN.draw(window);

    // Update the window
    window.display();
} */
