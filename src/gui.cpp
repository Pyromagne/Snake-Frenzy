#include "../inc/gui.hpp"
#include "../inc/game.hpp"

void mainMenuUI(sf::RenderWindow& window)
{
    window.setMouseCursorVisible(true);
    log("Initializing GUI",debugMode);
    sf::Font simpleSquareFNT;
    simpleSquareFNT.loadFromFile("assets/font/ST-SimpleSquare.otf");

    sf::Text titleTXT;
    titleTXT.setFont(simpleSquareFNT);
    titleTXT.setFillColor(sf::Color(45, 226, 230));
    titleTXT.setString("Snake: Frenzy");
    titleTXT.setCharacterSize(50.f);
    titleTXT.setPosition(sf::Vector2f(100.f, 50));

    RectButton classicModeBTN(simpleSquareFNT, true, sf::Vector2f(100.f, 300.f));
    classicModeBTN.setLabelColor(sf::Color::White, sf::Color(255, 108, 17), sf::Color(255, 108, 17));
    classicModeBTN.setButtonColor(sf::Color::Transparent);
    classicModeBTN.setButtonLabel(40.f, "Classic");

    RectButton arcadeModeBTN(simpleSquareFNT, true, sf::Vector2f(100.f, 400.f));
    arcadeModeBTN.setLabelColor(sf::Color::White, sf::Color(255, 108, 17), sf::Color(255, 108, 17));
    arcadeModeBTN.setButtonColor(sf::Color::Transparent);
    arcadeModeBTN.setButtonLabel(40.f, "Arcade");

    RectButton exitBTN(simpleSquareFNT, true, sf::Vector2f(100.f, 500.f));
    exitBTN.setLabelColor(sf::Color::White, sf::Color::Red, sf::Color::Red);
    exitBTN.setButtonColor(sf::Color::Transparent);
    exitBTN.setButtonLabel(40.f, "Exit");

    RectButton authorBTN(simpleSquareFNT, true, sf::Vector2f(window.getSize().x - 275, window.getSize().y - 75));
    authorBTN.setLabelColor(sf::Color(246, 1, 157), sf::Color(212, 0, 120), sf::Color(212, 0, 120));
    authorBTN.setButtonColor(sf::Color::Transparent);
    authorBTN.setButtonLabel(30.f, "Pyromagne");

    sf::Texture backgroundTEX;
    backgroundTEX.loadFromFile("assets/image/backgroundSW.png");
    backgroundTEX.setRepeated(true);

    sf::Sprite backgroundSPR(backgroundTEX);
    backgroundSPR.setTextureRect(sf::IntRect(0, 0, resolution.x, resolution.y));

    sf::Event event;
    //temporary fix the visual bug in buttons
        classicModeBTN.getButtonStatus(window, event);
        arcadeModeBTN.getButtonStatus(window, event);
        exitBTN.getButtonStatus(window, event);
        authorBTN.getButtonStatus(window, event);
    //temporary fix the visual bug in buttons

    sf::Music MainMenuBGM;
    MainMenuBGM.openFromFile("assets/audio/DavidKBD-Pink-Bloom-Pack-07-The-Hidden-One.ogg");
    MainMenuBGM.setLoop(true);
    MainMenuBGM.play();

    sf::SoundBuffer selectHoverSB;
    selectHoverSB.loadFromFile("assets/audio/Retro-Blip-07.wav");
    sf::SoundBuffer selectClickedSB;
    selectClickedSB.loadFromFile("assets/audio/Retro-Blip-15.wav");

    sf::Sound soundEffect;
    soundEffect.setLoop(false);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (window.pollEvent(event))
        {
            classicModeBTN.getButtonStatus(window, event);
            arcadeModeBTN.getButtonStatus(window, event);
            exitBTN.getButtonStatus(window, event);
            authorBTN.getButtonStatus(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            //HOVER FUNCTION OF SFML BUTTON LIBRARY MUST BE CHANGE
            /* if (exitBTN.isHover || playBTN.isHover || authorBTN.isHover)
            {
                soundEffect.setBuffer(selectHoverSB);
                soundEffect.play();
            } */
            if (exitBTN.isPressed)
            {
                soundEffect.setBuffer(selectClickedSB);
                soundEffect.play();
                sf::sleep(sf::seconds(0.5f));
                window.close();
            }
            if (classicModeBTN.isPressed)
            {
                soundEffect.setBuffer(selectClickedSB);
                soundEffect.play();
                MainMenuBGM.stop();
                gameClassicUI(window, true);
            }
            if (arcadeModeBTN.isPressed)
            {
                soundEffect.setBuffer(selectClickedSB);
                soundEffect.play();
                MainMenuBGM.stop();
                //gameClassicUI(window, true);
            }
            if (authorBTN.isPressed)
            {
                soundEffect.setBuffer(selectClickedSB);
                soundEffect.play();
                system("start https://pyromagne.itch.io/");
            }
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(backgroundSPR);

        classicModeBTN.draw(window);
        arcadeModeBTN.draw(window);
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

    sf::Music GameClassicBGM;
    GameClassicBGM.openFromFile("assets/audio/DavidKBD-Pink-Bloom-Pack-09-Lightyear-City.ogg");
    GameClassicBGM.setLoop(true);
    GameClassicBGM.play();

    sf::SoundBuffer foodEatSB;
    foodEatSB.loadFromFile("assets/audio/Retro-Blop-07.wav");
    sf::SoundBuffer snakeWallCollideSB;
    snakeWallCollideSB.loadFromFile("assets/audio/Retro-Electronic-Burst-StereoUP-04.wav");

    sf::Sound soundEffect;
    soundEffect.setLoop(false);

    if(isPressed)
    {
        sf::Texture backgroundTEX;
        backgroundTEX.loadFromFile("assets/image/backgroundGame4.png");
        backgroundTEX.setRepeated(true);

        sf::Sprite backgroundSPR(backgroundTEX);
        backgroundSPR.setTextureRect(sf::IntRect(0, 0, resolution.x, resolution.y));

        sf::Font simpleSquareFNT;
        simpleSquareFNT.loadFromFile("assets/font/ST-SimpleSquare.otf");

        /* sf::Text modeTitleTXT;
        modeTitleTXT.setFont(simpleSquareFNT);
        modeTitleTXT.setFillColor(sf::Color::White);
        modeTitleTXT.setString("Classic");
        modeTitleTXT.setCharacterSize(33.f);
        modeTitleTXT.setPosition(sf::Vector2f(1020.f, 50.f)); */

        /* sf::Text scoreLabelTXT;
        scoreLabelTXT.setFont(simpleSquareFNT);
        scoreLabelTXT.setFillColor(sf::Color::White);
        scoreLabelTXT.setString("Score:");
        scoreLabelTXT.setCharacterSize(30.f);
        scoreLabelTXT.setPosition(sf::Vector2f(980.f, 120.f)); */

        sf::Text scoreTXT;
        scoreTXT.setFont(simpleSquareFNT);
        scoreTXT.setFillColor(sf::Color::White);
        scoreTXT.setCharacterSize(30.f);


        Snake *snake = new Snake(500, 1, 25.f);

        sf::Texture headTEX;
        sf::Texture bodyTEX;

        headTEX.loadFromFile("assets/image/snakeHead2.png");
        bodyTEX.loadFromFile("assets/image/snakeSkin2.png");

        snake->setSnakeTexture(headTEX, bodyTEX);

        /* 16:9 */ Wall wall(window.getSize().x / snakeSize.x - 1, window.getSize().y / snakeSize.y, sf::RectangleShape(sf::Vector2f(25.f, 25.f)));
        /* 16:10 */ //Wall wall(window.getSize().x / snakeSize.x, window.getSize().y / snakeSize.y, sf::RectangleShape(sf::Vector2f(25.f, 25.f)));

        //Wall wall(window.getSize().x / snakeSize.x - 5, window.getSize().y / snakeSize.y - 5, sf::RectangleShape(sf::Vector2f(25.f, 25.f)));
        /* sf::Texture wallTEX;
        wallTEX.loadFromFile("assets/image/wall.png");
        wall.setWallTexture(wallTEX); */

        wall.setWallColor(sf::Color::Transparent);

        float centerX, centerY;
        centerX = float((window.getSize().x / 2) - (wall.width / 2) * snakeSize.x);
        centerY = float((window.getSize().y / 2) - (wall.length / 2) * snakeSize.y);
        wall.setWallPosition(centerX, centerY);

        //wall.setWallPosition(0,0);

        snake->head.nodeRect.setPosition(wall.x + 50, wall.y + 50);
        snake->body[0].nodeRect.setPosition(175.f, 200.f);

        sf::Texture planeTEX;
        planeTEX.loadFromFile("assets/image/plane3.png");
        planeTEX.setRepeated(true);
        wall.setPlaneTexture(planeTEX);

        Food food(sf::RectangleShape(sf::Vector2f(25.f, 25.f)));
        sf::Texture foodTEX;
        foodTEX.loadFromFile("assets/image/food2.png");
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
                    soundEffect.setBuffer(snakeWallCollideSB);
                    soundEffect.play();
                    gameOver = true;
                }

                if(snake->checkWallHit(wall) == true)
                {
                    soundEffect.setBuffer(snakeWallCollideSB);
                    soundEffect.play();
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

            wall.drawWall(window);
            snake->drawSnake(window);

            //window.draw(modeTitleTXT);
            //window.draw(scoreLabelTXT);
            scoreTXT.setString(std::to_string(score));
            if( snake->head.nodeRect.getGlobalBounds().intersects(scoreTXT.getGlobalBounds()) ||
                food.rect.getGlobalBounds().intersects(scoreTXT.getGlobalBounds()))
            {
                scoreTXT.setFillColor(sf::Color(255,255,255,75));
            }
            else
            {
                scoreTXT.setFillColor(sf::Color::White);
            }

            for (unsigned int i = 0; i < snake->snakeSize; i++)
            {
                if(snake->body[i].nodeRect.getGlobalBounds().intersects(scoreTXT.getGlobalBounds()))
                {
                    scoreTXT.setFillColor(sf::Color(255,255,255,75));
                }
            }

            scoreTXT.setPosition(sf::Vector2f((window.getSize().x / 2) - (scoreTXT.getLocalBounds().width / 2), 50.f));
            window.draw(scoreTXT);

            /* TEMPORARY PLACE */
                if(food.x == 0 && food.y == 0)
                {
                    food.generateFood(wall.width, wall.length, wall.x, wall.y);
                }
                if(snake->checkFoodCollision(food))
                {
                    soundEffect.setBuffer(foodEatSB);
                    soundEffect.play();
                    food.generateFood(wall.width, wall.length, wall.x, wall.y);
                    snake->snakeSize++;
                    log("Food eaten",debugMode);
                    score = score + 10;
                    log("Score: " + std::to_string(score),debugMode);
                }
                if(snake->checkFoodHitBody(food))
                {
                    food.generateFood(wall.width, wall.length, wall.x, wall.y);
                    log("Food spawned in body position, generate new food",debugMode);
                }
            /* TEMPORARY PLACE */

            window.draw(food.rect);

            if(pause == true)
            {
                drawPause(window);
            }
            if (gameOver == true)
            {
                GameClassicBGM.stop();
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

void gameArcadeUI(sf::RenderWindow& window, bool isPressed)
{
    while (window.isOpen())
    {   
        sf::Event event;
        while (window.pollEvent(event))
        {
            //sampleBTN.getButtonStatus(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            

        }

        // Clear screen
        window.clear();

        // Draw the sprite
        //sampleBTN.draw(window);

        // Update the window
        window.display();
    }
}

void drawPause(sf::RenderWindow& window)
{
    defaultFont.loadFromFile("assets/font/ST-SimpleSquare.otf");
    sf::RectangleShape overlayRect;
    overlayRect.setFillColor(sf::Color(0, 0, 0, 200));
    overlayRect.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

    sf::Text pauseTXT;
    pauseTXT.setFont(defaultFont);
    pauseTXT.setFillColor(sf::Color::White);
    pauseTXT.setString("Press [Space] to Continue");
    pauseTXT.setCharacterSize(50.f);

    pauseTXT.setPosition(sf::Vector2f(
        (window.getSize().x / 2) - (pauseTXT.getLocalBounds().width / 2),
        (window.getSize().y / 2) - (pauseTXT.getLocalBounds().height / 2)
    ));

    window.draw(overlayRect);
    window.draw(pauseTXT);
}

void drawGameOver(sf::RenderWindow& window, unsigned int score = 0)
{
    defaultFont.loadFromFile("assets/font/ST-SimpleSquare.otf");
    sf::RectangleShape overlayRect;
    overlayRect.setFillColor(sf::Color(0, 0, 0, 200));
    overlayRect.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

    sf::Text gameOverTXT;
    gameOverTXT.setFont(defaultFont);
    gameOverTXT.setFillColor(sf::Color::Red);
    gameOverTXT.setString("Game Over");
    gameOverTXT.setCharacterSize(100.f);
    gameOverTXT.setPosition(sf::Vector2f(
        (window.getSize().x / 2) - (gameOverTXT.getLocalBounds().width / 2),
        (window.getSize().y / 2) - (gameOverTXT.getLocalBounds().height / 2)
    ));

    sf::Text scoreTXT;
    scoreTXT.setFont(defaultFont);
    scoreTXT.setFillColor(sf::Color::White);
    scoreTXT.setString("Score: " + std::to_string(score));
    scoreTXT.setCharacterSize(50.f);
    scoreTXT.setPosition(sf::Vector2f(
        (window.getSize().x / 2) - (scoreTXT.getLocalBounds().width / 2),
        (window.getSize().y / 2) - (scoreTXT.getLocalBounds().height / 2) + 100
    ));


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
