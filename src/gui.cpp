#include "../inc/gui.hpp"
#include "../inc/game.hpp"

void mainMenuUI(sf::RenderWindow& window)
{
    window.setMouseCursorVisible(true);
    log("Initializing GUI",debugMode);
    sf::Font simpleSquareFNT;
    simpleSquareFNT.loadFromFile("ST-SimpleSquare.otf");

    sf::Text titleTXT;
    titleTXT.setFont(simpleSquareFNT);
    titleTXT.setFillColor(sf::Color::Yellow);
    titleTXT.setString("Snake: Frenzy");
    titleTXT.setCharacterSize(50.f);
    titleTXT.setPosition(sf::Vector2f(100.f, 50));

    RectButton playBTN(simpleSquareFNT, true, sf::Vector2f(100.f, 300.f));
    playBTN.setLabelColor(sf::Color::White, sf::Color::Green, sf::Color::Green);
    playBTN.setButtonColor(sf::Color::Transparent);
    playBTN.setButtonLabel(40.f, "Classic");

    RectButton exitBTN(simpleSquareFNT, true, sf::Vector2f(100.f, 400.f));
    exitBTN.setLabelColor(sf::Color::White, sf::Color::Red, sf::Color::Red);
    exitBTN.setButtonColor(sf::Color::Transparent);
    exitBTN.setButtonLabel(40.f, "Exit");

    RectButton authorBTN(simpleSquareFNT, true, sf::Vector2f(1000.f, 640.f));
    authorBTN.setLabelColor(sf::Color(240, 67, 14), sf::Color(168, 50, 13), sf::Color(168, 50, 13));
    authorBTN.setButtonColor(sf::Color::Transparent);
    authorBTN.setButtonLabel(30.f, "Pyromagne");

    sf::Texture backgroundTEX;
    backgroundTEX.loadFromFile("backgroundTile.png");
    backgroundTEX.setRepeated(true);

    sf::Sprite backgroundSPR(backgroundTEX);
    backgroundSPR.setTextureRect(sf::IntRect(0, 0, 1280, 800));

    sf::Event event;
    //temporary fix the visual bug in buttons
        playBTN.getButtonStatus(window, event);
        exitBTN.getButtonStatus(window, event);
        authorBTN.getButtonStatus(window, event);
    //temporary fix the visual bug in buttons

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (window.pollEvent(event))
        {
            playBTN.getButtonStatus(window, event);
            exitBTN.getButtonStatus(window, event);
            authorBTN.getButtonStatus(window, event);

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
            if (authorBTN.isPressed)
            {
                system("start https://pyromagne.itch.io/");
            }
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(backgroundSPR);

        playBTN.draw(window);
        exitBTN.draw(window);
        authorBTN.draw(window);
        window.draw(titleTXT);

        // Update the window
        window.display();
    }
}

void gameClassicUI(sf::RenderWindow& window, bool isPressed)
{
    window.setMouseCursorVisible(false);
    unsigned int score = 0;
    bool pause = false;
    bool gameOver = false;
    sf::Clock gameOverCLK;

    if(isPressed)
    {
        sf::Texture backgroundTEX;
        backgroundTEX.loadFromFile("backgroundTile.png");
        backgroundTEX.setRepeated(true);

        sf::Sprite backgroundSPR(backgroundTEX);
        backgroundSPR.setTextureRect(sf::IntRect(0, 0, 1280, 800));

        sf::Font simpleSquareFNT;
        simpleSquareFNT.loadFromFile("ST-SimpleSquare.otf");

        sf::Text modeTitleTXT;
        modeTitleTXT.setFont(simpleSquareFNT);
        modeTitleTXT.setFillColor(sf::Color::White);
        modeTitleTXT.setString("Classic");
        modeTitleTXT.setCharacterSize(33.f);
        modeTitleTXT.setPosition(sf::Vector2f(1020.f, 50.f));

        sf::Text scoreLabelTXT;
        scoreLabelTXT.setFont(simpleSquareFNT);
        scoreLabelTXT.setFillColor(sf::Color::White);
        scoreLabelTXT.setString("Score:");
        scoreLabelTXT.setCharacterSize(30.f);
        scoreLabelTXT.setPosition(sf::Vector2f(980.f, 120.f));

        sf::Text scoreTXT;
        scoreTXT.setFont(simpleSquareFNT);
        scoreTXT.setFillColor(sf::Color::White);
        scoreTXT.setCharacterSize(30.f);
        scoreTXT.setPosition(sf::Vector2f(1120.f, 120.f));

        Snake *snake = new Snake(500,1);
        snake->headTEX.loadFromFile("snakeHead.png");
        snake->bodyTEX.loadFromFile("snakeSkin.png");

        snake->head.nodeRect.setPosition(200.f, 200.f);
        snake->body[0].nodeRect.setPosition(175.f, 200.f);


        sf::Texture wallTEX;
        wallTEX.loadFromFile("wall.png");
        snake->wall.setWallTexture(wallTEX);

        snake->wall.setWallPosition(50.f, 50.f);

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
                if (pause == false)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        pause = true;
                    }

                    snake->dpad();
                }
                if (pause == true)
                {
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        pause = false;
                    }
                }
                
            }


            if(snake->lastMove != 0)
            {
                if(snake->checkSnakeCollision() == true)
                {
                    gameOver = true;
                }

                if(snake->checkWallHit() == true)
                {
                    gameOver = true;
                }

                if (pause == false)
                {
                    snake->updatePosition(50.f);
                }

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
                    food.generateFood(snake->wall.width, snake->wall.length, snake->wall.x, snake->wall.y);
                }
                if(snake->checkFoodCollision(food))
                {
                    food.generateFood(snake->wall.width, snake->wall.length, snake->wall.x, snake->wall.y);
                    snake->snakeSize++;
                    log("Food eaten",debugMode);
                    score = score + 100;
                    log("Score: " + std::to_string(score),debugMode);
                }
                if(snake->checkFoodHitBody(food))
                {
                    food.generateFood(snake->wall.width, snake->wall.length, snake->wall.x, snake->wall.y);
                    log("Food spawned in body position, generate new food",debugMode);
                }
            /* TEMPORARY PLACE */

            window.draw(food.food);

            if(pause == true)
            {
                drawPause(window);
            }
            if (gameOver == true)
            {   
                drawGameOver(window, score);
                window.display();
                sf::sleep(sf::seconds(2.f));
                delete snake;
                mainMenuUI(window);   
            }


            // Update the window
            window.display();
        }
    }
}

void drawPause(sf::RenderWindow& window)
{
    defaultFont.loadFromFile("ST-SimpleSquare.otf");
    sf::RectangleShape overlayRect;
    overlayRect.setFillColor(sf::Color(0, 0, 0, 200));
    overlayRect.setSize(sf::Vector2f(1280.f, 720.f));

    sf::Text pauseTXT;
    pauseTXT.setFont(defaultFont);
    pauseTXT.setFillColor(sf::Color::White);
    pauseTXT.setString("Press [Space] to Continue");
    pauseTXT.setCharacterSize(50.f);

    pauseTXT.setPosition(sf::Vector2f(180.f, float(720 /2)));

    window.draw(overlayRect);
    window.draw(pauseTXT);
}

void drawGameOver(sf::RenderWindow& window, unsigned int score = 0)
{
    defaultFont.loadFromFile("ST-SimpleSquare.otf");
    sf::RectangleShape overlayRect;
    overlayRect.setFillColor(sf::Color(0, 0, 0, 200));
    overlayRect.setSize(sf::Vector2f(1280.f, 720.f));

    sf::Text gameOverTXT;
    gameOverTXT.setFont(defaultFont);
    gameOverTXT.setFillColor(sf::Color::Red);
    gameOverTXT.setString("Game Over");
    gameOverTXT.setCharacterSize(100.f);
    gameOverTXT.setPosition(sf::Vector2f(300.f, 290.f));

    sf::Text scoreTXT;
    scoreTXT.setFont(defaultFont);
    scoreTXT.setFillColor(sf::Color::White);
    scoreTXT.setString("Score: " + std::to_string(score));
    scoreTXT.setCharacterSize(50.f);
    scoreTXT.setPosition(sf::Vector2f(300.f, 400.f));


    window.draw(overlayRect);
    window.draw(gameOverTXT);
    window.draw(scoreTXT);
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
