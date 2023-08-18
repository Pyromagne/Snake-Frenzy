#include "../inc/gui.hpp"
#include "../inc/game.hpp"

void mainMenuUI(sf::RenderWindow& window)
{
    log("Initializing GUI",debugMode);
    sf::Font simpleSquareFNT;
    simpleSquareFNT.loadFromFile("ST-SimpleSquare.otf");

    RectButton playBTN(simpleSquareFNT, true, sf::Vector2f(50.f, 50.f));
    playBTN.setLabelColor(sf::Color::White, sf::Color::Green, sf::Color::Green);
    playBTN.setButtonColor(sf::Color::Transparent);
    playBTN.setButtonLabel(50.f, "Play");

    RectButton exitBTN(simpleSquareFNT, true, sf::Vector2f(50.f, 150.f));
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
                gameMenuUI(window, true);
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

void gameMenuUI(sf::RenderWindow& window, bool isPressed)
{
    if(isPressed)
    {
        SnakeClass *snake = new SnakeClass(100,10);
        snake->headSkin.loadFromFile("snakeHead.png");
        snake->bodySkin.loadFromFile("snakeSkin.png");

        sf::Texture backgroundTEX;
        backgroundTEX.loadFromFile("background.png");

        sf::Sprite backgroundSPR;
        backgroundSPR.setTexture(backgroundTEX);

        snake->head.node.setPosition(50.f, 50.f);
        snake->safeArea.setWallColor(sf::Color::Red);
        snake->safeArea.setWallPosition(0.f, 0.f);

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
                    delete snake;
                    mainMenuUI(window);
                }

                snake->dpad();
            }

            if(snake->lastMove != 0)
            {
                if(snake->checkSnakeCollision() == true)
                {
                    delete snake;
                    mainMenuUI(window);
                }

                if(snake->checkWallHit() == true)
                {
                    delete snake;
                    mainMenuUI(window);
                }

                snake->updatePosition(50.f);
                std::cout<<snake->head.node.getPosition().x << " " << snake->head.node.getPosition().y <<std::endl;
            }

            // Clear screen
            window.clear();

            // Draw the sprite
            window.draw(backgroundSPR);
            window.draw(snake->safeArea.top);
            window.draw(snake->safeArea.left);
            window.draw(snake->safeArea.bottom);
            window.draw(snake->safeArea.right);
            snake->drawSnake(window);

            // Update the window
            window.display();
        }
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
