#include "../inc/game.hpp"
#include "../inc/system.hpp"

Snake::Snake()
{
    node.setFillColor(sf::Color::White);
}

SnakeClass::SnakeClass()
{
    body = new Snake[200];
    log("Snake Created",debugMode);
}

SnakeClass::SnakeClass(unsigned int maxSnakeSize)
{
    body = new Snake[maxSnakeSize];
    log("Snake Created",debugMode);
}
SnakeClass::SnakeClass(unsigned int maxSnakeSize, unsigned int snakeSize)
{
    body = new Snake[maxSnakeSize];
    if(snakeSize > maxSnakeSize)
    {
        err("Size exceed Max Value",debugMode);
        exit(EXIT_FAILURE);
    }
    else{
        this->snakeSize = snakeSize;
        log("Snake Created",debugMode);
    }
}

SnakeClass::~SnakeClass()
{
    log("Snake Destroyed",debugMode);
    delete[] body;
}

void SnakeClass::updatePosition(float speed = 100.f)
{
    if (updatePositionCLK.getElapsedTime().asMilliseconds() > speed)
    {
        head.prevNodes = head.node.getPosition();
        for (int i = 0; i < snakeSize; i++)
        {
            body[i+1].prevNodes = body[i].node.getPosition();
        }

        sf::Vector2f currentPosition = head.node.getPosition();
        if (lastMove == 1)
        {
            currentPosition.x -= 25.f;
            head.node.setPosition(currentPosition);
        }
        else if (lastMove == 2)
        {
            currentPosition.x += 25.f;
            head.node.setPosition(currentPosition);
        }
        else if (lastMove == 3)
        {
            currentPosition.y -= 25.f;
            head.node.setPosition(currentPosition);
        }
        else if (lastMove == 4)
        {
            currentPosition.y += 25.f ;
            head.node.setPosition(currentPosition);
        }



        updatePositionCLK.restart();
    }
}

void SnakeClass::drawSnake(sf::RenderWindow& window)
{
    body[0].nextNodes = &head.prevNodes;
    body[0].node.setPosition(*body[0].nextNodes);

    for (int i = 0; i < snakeSize; i++)
    {
        body[i+1].nextNodes = &body[i].prevNodes;
        body[i+1].node.setPosition(body[i+1].prevNodes);
    }

    head.node.setTexture(&headSkin);

    for (int i = 0; i < snakeSize; i++)
    {
        body[i].node.setTexture(&bodySkin);
        window.draw(body[i].node);
    }
    window.draw(head.node);
    
}

void SnakeClass::dpad(void)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && lastMove != 2)
    {
        if(!(lastMove == 1))
        {
            log("LEFT", debugMode);
            lastMove = 1;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && lastMove != 1)
    {
        if (!(lastMove == 2))
        {
            log("RIGHT", debugMode);
            lastMove = 2;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && lastMove != 4)
    {
        if (!(lastMove == 3))
        {
            log("UP", debugMode);
            lastMove = 3;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && lastMove != 3)
    {
        if (!(lastMove == 4))
        {
            log("DOWN", debugMode);
            lastMove = 4;
        }
    }
}
