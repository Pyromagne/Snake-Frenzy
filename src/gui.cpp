#include "../inc/gui.hpp"
#include "../inc/game.hpp"

void mainMenuUI(sf::RenderWindow& window)
{
    window.setMouseCursorVisible(true);
    log("Initializing GUI",debugMode);
    sf::Font simpleSquareFNT;
    simpleSquareFNT.loadFromFile("ST-SimpleSquare.otf");

    RectButton playBTN(simpleSquareFNT, true, sf::Vector2f(50.f, 50.f));
    playBTN.setLabelColor(sf::Color::White, sf::Color::Green, sf::Color::Green);
    playBTN.setButtonColor(sf::Color::Transparent);
    playBTN.setButtonLabel(40.f, "Classic");

    RectButton exitBTN(simpleSquareFNT, true, sf::Vector2f(50.f, 150.f));
    exitBTN.setLabelColor(sf::Color::White, sf::Color::Red, sf::Color::Red);
    exitBTN.setButtonColor(sf::Color::Transparent);
    exitBTN.setButtonLabel(40.f, "Exit");

    sf::Texture backgroundTEX;
    backgroundTEX.loadFromFile("background.png");

    sf::Sprite backgroundSPR;
    backgroundSPR.setTexture(backgroundTEX);

    sf::Event event;
    //temporary fix the visual bug in buttons
        playBTN.getButtonStatus(window, event);
        exitBTN.getButtonStatus(window, event);
    //temporary fix the visual bug in buttons

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
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
    window.setMouseCursorVisible(false);
    if(isPressed)
    {
        sf::Texture backgroundTEX;
        backgroundTEX.loadFromFile("background.png");

        sf::Sprite backgroundSPR;
        backgroundSPR.setTexture(backgroundTEX);

        SnakeClass *snake = new SnakeClass(100,3);
        snake->headTEX.loadFromFile("snakeHead.png");
        snake->bodyTEX.loadFromFile("snakeSkin.png");

        snake->head.node.setPosition(50.f, 50.f);

        sf::Texture wallTEX;
        wallTEX.loadFromFile("wall.png");
        snake->wall.setWallTexture(wallTEX);

        snake->wall.setWallPosition(0.f, 0.f);

        Food food;
        sf::Texture foodTEX;
        foodTEX.loadFromFile("food.png");
        food.setFoodTexture(foodTEX);

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
            }

            // Clear screen
            window.clear();

            // Draw the sprite
            window.draw(backgroundSPR);
            snake->wall.drawWall(window);
            snake->drawSnake(window);

            /* TEMPORARY PLACE */
                if(food.x == 0 && food.y == 0)
                {
                    food.generateFood(snake->wall.width, snake->wall.length);
                }
                if(snake->checkFoodCollision(food))
                {
                    food.generateFood(snake->wall.width, snake->wall.length);
                    snake->snakeSize++;
                    std::cout<< "Food Hit! "<< snake->snakeSize <<std::endl;
                }
                if(snake->checkFoodHitBody(food))
                {
                    food.generateFood(snake->wall.width, snake->wall.length);
                    std::cout<< "SNAKE!!!!!!!" << std::endl;
                }
            /* TEMPORARY PLACE */

            window.draw(food.food);
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
