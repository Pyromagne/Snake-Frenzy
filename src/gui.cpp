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
    backgroundTEX.loadFromFile("backgroundTile.png");
    backgroundTEX.setRepeated(true);

    sf::Sprite backgroundSPR(backgroundTEX);
    backgroundSPR.setTextureRect(sf::IntRect(0, 0, 1280, 720));

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
                gameClassicUI(window, true);
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

void gameClassicUI(sf::RenderWindow& window, bool isPressed)
{
    window.setMouseCursorVisible(false);
    unsigned int score = 0;

    if(isPressed)
    {
        sf::Texture backgroundTEX;
        backgroundTEX.loadFromFile("backgroundTile.png");
        backgroundTEX.setRepeated(true);

        sf::Sprite backgroundSPR(backgroundTEX);
        backgroundSPR.setTextureRect(sf::IntRect(0, 0, 1280, 720));

        sf::Font simpleSquareFNT;
        simpleSquareFNT.loadFromFile("ST-SimpleSquare.otf");

        sf::Text modeTitleTXT;
        modeTitleTXT.setFont(simpleSquareFNT);
        modeTitleTXT.setFillColor(sf::Color::White);
        modeTitleTXT.setString("Classic");
        modeTitleTXT.setCharacterSize(33.f);
        modeTitleTXT.setPosition(sf::Vector2f(605.f, 10.f));

        sf::Text scoreLabelTXT;
        scoreLabelTXT.setFont(simpleSquareFNT);
        scoreLabelTXT.setFillColor(sf::Color::White);
        scoreLabelTXT.setString("Score:");
        scoreLabelTXT.setCharacterSize(30.f);
        scoreLabelTXT.setPosition(sf::Vector2f(605.f, 60.f));

        sf::Text scoreTXT;
        scoreTXT.setFont(simpleSquareFNT);
        scoreTXT.setFillColor(sf::Color::White);
        scoreTXT.setCharacterSize(30.f);
        scoreTXT.setPosition(sf::Vector2f(740.f, 60.f));

        Snake *snake = new Snake(100,3);
        snake->headTEX.loadFromFile("snakeHead.png");
        snake->bodyTEX.loadFromFile("snakeSkin.png");

        snake->head.nodeRect.setPosition(50.f, 50.f);

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

            window.draw(modeTitleTXT);
            window.draw(scoreLabelTXT);
            
            scoreTXT.setString(std::to_string(score));
            window.draw(scoreTXT);

            /* TEMPORARY PLACE */
                if(food.x == 0 && food.y == 0)
                {
                    food.generateFood(snake->wall.width, snake->wall.length);
                }
                if(snake->checkFoodCollision(food))
                {
                    food.generateFood(snake->wall.width, snake->wall.length);
                    snake->snakeSize++;
                    log("Food eaten",debugMode);
                    score = score + 100;
                    log("Score: " + std::to_string(score),debugMode);
                }
                if(snake->checkFoodHitBody(food))
                {
                    food.generateFood(snake->wall.width, snake->wall.length);
                    log("Food hit body detected, changing food position",debugMode);
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
