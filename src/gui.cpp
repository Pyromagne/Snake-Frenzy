#include "../inc/gui.hpp"
#include "../inc/game.hpp"

void mainMenuUI(sf::RenderWindow& window)
{
    window.setMouseCursorVisible(true);
    log("Initializing GUI",debugMode);
    sf::Font simpleSquareFNT;
    simpleSquareFNT.loadFromFile("assets/font/RenogareSoft-Regular.ttf");

    sf::Text titleTXT;
    titleTXT.setFont(simpleSquareFNT);
    titleTXT.setFillColor(color::ONYX);
    titleTXT.setString("Snake: Frenzy");
    titleTXT.setCharacterSize(50.f);
    titleTXT.setPosition(sf::Vector2f(100.f, 50));

    RectButton classicModeBTN(simpleSquareFNT, true, sf::Vector2f(100.f, 300.f));
    classicModeBTN.setLabelColor(color::ONYX, sf::Color(255, 108, 17), sf::Color(255, 108, 17));
    classicModeBTN.setButtonColor(sf::Color::Transparent);
    classicModeBTN.setButtonLabel(40.f, "Classic");

    RectButton arcadeModeBTN(simpleSquareFNT, true, sf::Vector2f(100.f, 400.f));
    arcadeModeBTN.setLabelColor(color::ONYX, sf::Color(255, 108, 17), sf::Color(255, 108, 17));
    arcadeModeBTN.setButtonColor(sf::Color::Transparent);
    arcadeModeBTN.setButtonLabel(40.f, "Arcade");

    /* RectButton frenzyBTN(simpleSquareFNT, true, sf::Vector2f(100.f, 500.f));
    frenzyBTN.setLabelColor(color::ONYX, sf::Color::Red, sf::Color::Red);
    frenzyBTN.setButtonColor(sf::Color::Transparent);
    frenzyBTN.setButtonLabel(40.f, "Frenzy"); */

    RectButton exitBTN(simpleSquareFNT, true, sf::Vector2f(100.f, 600.f));
    exitBTN.setLabelColor(color::ONYX, sf::Color::Red, sf::Color::Red);
    exitBTN.setButtonColor(sf::Color::Transparent);
    exitBTN.setButtonLabel(40.f, "Exit");

    RectButton authorBTN(simpleSquareFNT, true, sf::Vector2f(window.getSize().x - 285, window.getSize().y - 75));
    authorBTN.setLabelColor(sf::Color(0x594D58ff));
    authorBTN.setButtonColor(sf::Color::Transparent);
    authorBTN.setButtonLabel(30.f, "Pyromagne");

    sf::Texture SFMLLogoTEX;
    SFMLLogoTEX.loadFromFile("assets/sfml.png");

    sf::Sprite SFMLLogoSPR;
    SFMLLogoSPR.setTexture(SFMLLogoTEX);
    SFMLLogoSPR.setPosition(sf::Vector2f(window.getSize().x - 75, window.getSize().y - 75));
    //SFMLLogoSPR.setScale(32.f / SFMLLogoSPR.getLocalBounds().width, 32.f / SFMLLogoSPR.getLocalBounds().height);

    /* sf::Texture backgroundTEX;
    backgroundTEX.loadFromFile("assets/image/backgroundSW.png");
    backgroundTEX.setRepeated(true); */

    sf::RectangleShape backgroundSPR(sf::Vector2f(resolution.x, resolution.y));
    backgroundSPR.setFillColor(sf::Color(204, 205, 198));

    sf::Event event;
    //temporary fix the visual bug in buttons
        classicModeBTN.getButtonStatus(window, event);
        arcadeModeBTN.getButtonStatus(window, event);
        //frenzyBTN.getButtonStatus(window, event);
        exitBTN.getButtonStatus(window, event);
        authorBTN.getButtonStatus(window, event);
    //temporary fix the visual bug in buttons

    /* sf::Music MainMenuBGM;
    MainMenuBGM.openFromFile("assets/audio/DavidKBD-Pink-Bloom-Pack-07-The-Hidden-One.ogg");
    MainMenuBGM.setLoop(true);
    MainMenuBGM.setVolume(30.f);
    MainMenuBGM.play(); */

    sf::SoundBuffer selectHoverSB;
    selectHoverSB.loadFromFile("assets/audio/Retro-Blip-07.wav");
    sf::SoundBuffer selectClickedSB;
    selectClickedSB.loadFromFile("assets/audio/Retro-Blip-15.wav");

    sf::Sound soundEffect;
    soundEffect.setLoop(false);
    soundEffect.setVolume(30.f);

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
                //MainMenuBGM.stop();
                gameClassicMode(window);
            }
            if (arcadeModeBTN.isPressed)
            {
                soundEffect.setBuffer(selectClickedSB);
                soundEffect.play();
                //MainMenuBGM.stop();
                gameArcadeMode(window);
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
        //frenzyBTN.draw(window);
        exitBTN.draw(window);
        window.draw(SFMLLogoSPR);
        authorBTN.draw(window);
        window.draw(titleTXT);

        // Update the window
        window.display();
    }
}

void gameClassicMode(sf::RenderWindow& window)
{
    int c = 0;

    window.setMouseCursorVisible(false);
    unsigned int score = 0;
    bool pause = false;
    bool gameOver = false;
    sf::Clock gameOverCLK;

    /* sf::Music GameClassicBGM;
    GameClassicBGM.openFromFile("assets/audio/DavidKBD-Pink-Bloom-Pack-09-Lightyear-City.ogg");
    GameClassicBGM.setLoop(true);
    GameClassicBGM.setVolume(30.f);
    GameClassicBGM.play(); */

    sf::SoundBuffer foodEatSB;
    foodEatSB.loadFromFile("assets/audio/Retro-Blop-07.wav");
    sf::SoundBuffer snakeWallCollideSB;
    snakeWallCollideSB.loadFromFile("assets/audio/Retro-Electronic-Burst-StereoUP-04.wav");

    sf::Sound soundEffect;
    soundEffect.setLoop(false);

    /* sf::Texture backgroundTEX;
    backgroundTEX.loadFromFile("assets/image/backgroundGame4.png");
    backgroundTEX.setRepeated(true); */

    sf::RectangleShape backgroundSPR(sf::Vector2f(resolution.x, resolution.y));
    backgroundSPR.setFillColor(sf::Color(204, 205, 198));

    /*
    sf::Sprite backgroundSPR(backgroundTEX);
    backgroundSPR.setTextureRect(sf::IntRect(0, 0, resolution.x, resolution.y));
    */

    sf::Font simpleSquareFNT;
    simpleSquareFNT.loadFromFile("assets/font/RenogareSoft-Regular.ttf");

    sf::Text scoreTXT;
    scoreTXT.setFont(simpleSquareFNT);
    scoreTXT.setFillColor(sf::Color::White);
    scoreTXT.setCharacterSize(30.f);

    short area = (window.getSize().x / snakeSize.x - 1) * window.getSize().y / snakeSize.y;
    Snake *snake = new Snake(area, 1, 25.f);

    sf::Texture headTEX;
    sf::Texture bodyTEX;

    headTEX.loadFromFile("assets/image/rounded.png");
    bodyTEX.loadFromFile("assets/image/rounded.png");
    //snake->head.nodeRect.setFillColor(sf::Color::Blue);
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

    /* sf::Texture planeTEX;
    planeTEX.loadFromFile("assets/image/plane3.png");
    planeTEX.setRepeated(true);
    //wall.setPlaneTexture(planeTEX); */
    wall.setPlaneColor(sf::Color(0x555555ff));

    Food food(sf::RectangleShape(sf::Vector2f(25.f, 25.f)));
    sf::Texture foodTEX;
    foodTEX.loadFromFile("assets/image/rounded.png");
    food.setFoodTexture(foodTEX);
    food.rect.setFillColor(sf::Color(0xEF9969ff));



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

                //for rainbow snake skin
                //c = c + 10;
                score = score + 10;

                for (unsigned int i = 0; i < snake->snakeSize; i++)
                {
                    //int cc = c + i * 10; // Increment hue based on the index i
                    //snake->body[i].nodeRect.setFillColor(hsv(cc % 360 ,45 , 39));
                    snake->body[i].nodeRect.setFillColor(sf::Color::White);
                }

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
            //GameClassicBGM.stop();
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

void gameArcadeMode(sf::RenderWindow& window)
{
    window.setMouseCursorVisible(false);
    unsigned int score = 0;
    bool pause = false;
    bool gameOver = false;
    sf::Clock gameOverCLK;

    /* sf::Music arcadeMSC;
    arcadeMSC.openFromFile("assets/audio/DavidKBD-Pink-Bloom-Pack-03-To-the-Unknown.ogg");
    arcadeMSC.setLoop(true);
    arcadeMSC.setVolume(30.f);
    arcadeMSC.play(); */

    sf::SoundBuffer timesUpSB;
    timesUpSB.loadFromFile("assets/audio/Retro-Charge-Off-11.wav");
    sf::SoundBuffer countdownSB;
    countdownSB.loadFromFile("assets/audio/Retro-Beeep-20.wav");
    sf::SoundBuffer foodBonusSB;
    foodBonusSB.loadFromFile("assets/audio/Retro-Magic-11.wav");
    sf::SoundBuffer foodEatSB;
    foodEatSB.loadFromFile("assets/audio/Retro-Blop-07.wav");
    sf::SoundBuffer snakeWallCollideSB;
    snakeWallCollideSB.loadFromFile("assets/audio/Retro-Electronic-Burst-StereoUP-04.wav");

    sf::Sound soundEffect;
    soundEffect.setLoop(false);

    /* sf::Texture backgroundTEX;
    backgroundTEX.loadFromFile("assets/image/backgroundGame4.png");
    backgroundTEX.setRepeated(true); */

    sf::RectangleShape backgroundSPR(sf::Vector2f(resolution.x, resolution.y));
    backgroundSPR.setFillColor(sf::Color(204, 205, 198));

    sf::Font simpleSquareFNT;
    simpleSquareFNT.loadFromFile("assets/font/RenogareSoft-Regular.ttf");

    sf::Text scoreTXT;
    scoreTXT.setFont(simpleSquareFNT);
    scoreTXT.setFillColor(sf::Color::White);
    scoreTXT.setCharacterSize(30.f);

    sf::Text timerTXT;
    timerTXT.setFont(simpleSquareFNT);
    timerTXT.setFillColor(sf::Color::White);
    timerTXT.setCharacterSize(30.f);

    short countdown = 15;
    sf::Clock timerCLK;

    short area = (window.getSize().x / snakeSize.x - 1) * window.getSize().y / snakeSize.y;
    Snake *snake = new Snake(area, 1, 25.f);

    sf::Texture headTEX;
    sf::Texture bodyTEX;

    headTEX.loadFromFile("assets/image/rounded.png");
    //bodyTEX.loadFromFile("assets/image/snakeSkin2.png");
    snake->head.nodeRect.setFillColor(sf::Color::Blue);
    snake->setSnakeTexture(headTEX, headTEX);

    /* 16:9 */ Wall wall(window.getSize().x / snakeSize.x - 1, window.getSize().y / snakeSize.y, sf::RectangleShape(sf::Vector2f(25.f, 25.f)));
    /* 16:10 */ //Wall wall(window.getSize().x / snakeSize.x, window.getSize().y / snakeSize.y, sf::RectangleShape(sf::Vector2f(25.f, 25.f)));

    wall.setWallColor(sf::Color::Transparent);
    float centerX, centerY;
    centerX = float((window.getSize().x / 2) - (wall.width / 2) * snakeSize.x);
    centerY = float((window.getSize().y / 2) - (wall.length / 2) * snakeSize.y);
    wall.setWallPosition(centerX, centerY);

    snake->head.nodeRect.setPosition(wall.x + 50, wall.y + 50);
    snake->body[0].nodeRect.setPosition(175.f, 200.f);

    /* sf::Texture planeTEX;
    planeTEX.loadFromFile("assets/image/plane3.png");
    planeTEX.setRepeated(true); */
    //wall.setPlaneTexture(planeTEX);
    wall.setPlaneColor(sf::Color(0x555555ff));


    const unsigned short foodMaxValue = 20;
    Food foodArray[foodMaxValue];
    sf::Texture foodTEX;
    foodTEX.loadFromFile("assets/image/rounded.png");
    for (unsigned short i = 0; i < foodMaxValue; i++)
    {
        foodArray[i].setRectangle(sf::RectangleShape(sf::Vector2f(25.f, 25.f)));
        foodArray[i].setFoodTexture(foodTEX);
        foodArray[i].setFoodColor(sf::Color(0xE49969ff));
    }

    Food foodBonus(sf::RectangleShape(sf::Vector2f(25.f, 25.f)));
    sf::Texture foodBonusTEX;
    foodBonusTEX.loadFromFile("assets/image/rounded.png");
    foodBonus.setFoodTexture(foodBonusTEX);
    foodBonus.setFoodColor(sf::Color(0x74A18Eff));
    unsigned short foodBonusCountdown = 5;
    bool isFoodBonusPresent = false;
    unsigned short foodBonusChance = 100;
    speed snakeSpeed = spd1;

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

        switch (snake->snakeSize)
        {
        case 20:
            snakeSpeed = spd2;
        break;
        case 30:
            snakeSpeed = spd3;
        break;
        case 40:
            snakeSpeed = spd4;
        break;
        case 50:
            snakeSpeed = spd5;
        break;
        case 60:
            snakeSpeed = spd6;
        break;
        case 70:
            snakeSpeed = spd7;
        break;
        case 80:
            snakeSpeed = spd8;
        break;
        case 90:
            snakeSpeed = spd9;
        break;
        case 100:
            snakeSpeed = spd10;
        break;
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
                snake->updatePosition(snakeSpeed);
                if (timerCLK.getElapsedTime().asSeconds() >= 1)
                {
                    countdown--;
                    if (isFoodBonusPresent)
                    {
                        foodBonusCountdown--;
                    }

                    timerCLK.restart();
                }
            }
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(backgroundSPR);

        wall.drawWall(window);
        snake->drawSnake(window);

        scoreTXT.setString(std::to_string(score));
        scoreTXT.setPosition(sf::Vector2f((window.getSize().x / 2) - (scoreTXT.getLocalBounds().width / 2), 682.f));
        window.draw(scoreTXT);

        timerTXT.setString(std::to_string(countdown));

        if(snake->head.nodeRect.getGlobalBounds().intersects(timerTXT.getGlobalBounds()))
        {
            timerTXT.setFillColor(sf::Color(255,255,255,75));
            if (countdown <= 10)
            {
                timerTXT.setFillColor(sf::Color(0xC8869175));
            }

        }
        else
        {
            timerTXT.setFillColor(sf::Color::White);
            if (countdown <= 10)
            {
                timerTXT.setFillColor(sf::Color(0xC88691FF));
            }
        }

        for (unsigned int i = 0; i < snake->snakeSize; i++)
        {
            if(snake->body[i].nodeRect.getGlobalBounds().intersects(timerTXT.getGlobalBounds()))
            {
                timerTXT.setFillColor(sf::Color(255,255,255,75));
                if (countdown <= 10)
                {
                    timerTXT.setFillColor(sf::Color(0xC8869175));
                }
            }
        }

        for (unsigned short i = 0; i < foodMaxValue; i++)
        {
            if(foodArray[i].rect.getGlobalBounds().intersects(timerTXT.getGlobalBounds()))
            {
                timerTXT.setFillColor(sf::Color(0xC88691FF));
            }
        }

        timerTXT.setPosition(sf::Vector2f((window.getSize().x / 2) - (timerTXT.getLocalBounds().width / 2), 50.f));
        window.draw(timerTXT);


        /* TEMPORARY PLACE */
            for (unsigned short i = 0; i < foodMaxValue; i++)
            {
                if(foodArray[i].x == 0 && foodArray[i].y == 0)
                {
                    foodArray[i].generateFood(wall.width, wall.length, wall.x, wall.y);
                }
                if(snake->checkFoodCollision(foodArray[i]))
                {
                    soundEffect.setBuffer(foodEatSB);
                    soundEffect.play();
                    foodArray[i].generateFood(wall.width, wall.length, wall.x, wall.y);
                    snake->snakeSize++;
                    score = score + 10;
                    countdown = countdown + 1;

                    if (isFoodBonusPresent == false)
                    {
                        foodBonusChance = genRandom(1,100);
                        log(std::to_string(foodBonusChance), debugMode);
                    }

                }
                if(snake->checkFoodHitBody(foodArray[i]))
                {
                    foodArray[i].generateFood(wall.width, wall.length, wall.x, wall.y);
                }
                for (unsigned short j = i + 1; j < foodMaxValue; j++)
                {
                    if (foodArray[i].x == foodArray[j].x && foodArray[i].y == foodArray[j].y)
                    {
                        foodArray[i].generateFood(wall.width, wall.length, wall.x, wall.y);
                    }
                }

                window.draw(foodArray[i].rect);
            }

            if (foodBonusChance <= 10 && isFoodBonusPresent == false)
            {
                foodBonusCountdown = 5;

                foodBonus.generateFood(wall.width, wall.length, wall.x, wall.y);
                if(snake->checkFoodHitBody(foodBonus))
                {
                    foodBonus.generateFood(wall.width, wall.length, wall.x, wall.y);
                }
                for (unsigned short i = 0; i < foodMaxValue; i++)
                {
                    if (foodBonus.x == foodArray[i].x && foodBonus.y == foodArray[i].y)
                    {
                        foodBonus.generateFood(wall.width, wall.length, wall.x, wall.y);
                    }
                }

                soundEffect.setBuffer(foodBonusSB);
                soundEffect.play();
                isFoodBonusPresent = true;
            }

            if (isFoodBonusPresent)
            {
                window.draw(foodBonus.rect);
                if(snake->checkFoodCollision(foodBonus))
                {
                    isFoodBonusPresent = false;
                    foodBonus.rect.setPosition(0.f,0.f);
                    soundEffect.setBuffer(foodEatSB);
                    soundEffect.play();
                    score = score + 100;
                    countdown = countdown + 3;
                    foodBonusChance = genRandom(1,100);
                    log(std::to_string(foodBonusChance), debugMode);
                }
                if (foodBonusCountdown == 0)
                {
                    isFoodBonusPresent = false;
                    foodBonus.rect.setPosition(0.f,0.f);
                    foodBonusChance = genRandom(1,100);
                }

            }


        /* TEMPORARY PLACE */

        if(pause == true)
        {
            drawPause(window);
        }
        if (gameOver == true)
        {
            //arcadeMSC.stop();
            drawGameOver(window, score);
            window.display();
            sf::sleep(sf::seconds(2.f));
            delete snake;
            mainMenuUI(window);
        }
        if (countdown == 0)
        {
            soundEffect.setBuffer(timesUpSB);
            soundEffect.play();
            //arcadeMSC.stop();
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

void drawPause(sf::RenderWindow& window)
{
    defaultFont.loadFromFile("assets/font/RenogareSoft-Regular.ttf");
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
    defaultFont.loadFromFile("assets/font/RenogareSoft-Regular.ttf");
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
