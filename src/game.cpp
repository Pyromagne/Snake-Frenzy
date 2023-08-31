#include "../inc/game.hpp"
#include "../inc/system.hpp"


Snake::Snake()
{
    node.setFillColor(sf::Color::White);
}

Wall::Wall(int width, int length)
{
    this->width = width;
    this->length = length;
    top = sf::RectangleShape(sf::Vector2f(float(width*25), 25.f));
    left = sf::RectangleShape(sf::Vector2f(25.f, float(length*25)));
    bottom = sf::RectangleShape(sf::Vector2f(float(width*25), 25.f));
    right = sf::RectangleShape(sf::Vector2f(25.f, float(length*25)));
}

void Wall::setWallColor(sf::Color color)
{
    top.setFillColor(color);
    left.setFillColor(color);
    bottom.setFillColor(sf::Color::Blue);
    right.setFillColor(sf::Color::Blue);
}

void Wall::setWallPosition(float x, float y)
{
    top.setPosition(x, y);
    left.setPosition(x, y);
    bottom.setPosition(x, (y + (length*25))-25);
    right.setPosition((x + (width*25))-25, y);
}

SnakeClass::SnakeClass()
{
    /* if (body != nullptr)
    {
        log("true",debugMode);
        delete[] body; // Deallocate the memory
    }
    delete[] body; */
    body = new Snake[200];
    log("Snake Created",debugMode);
}

SnakeClass::SnakeClass(unsigned int maxSnakeSize)
{
    /* if (body != nullptr)
    {
        log("true",debugMode);
        delete[] body; // Deallocate the memory
    }
    delete[] body; */
    body = new Snake[maxSnakeSize];
    log("Snake Created",debugMode);
}
SnakeClass::SnakeClass(unsigned int maxSnakeSize, unsigned int snakeSize)
{
    /* if (body != nullptr)
    {
        log("true",debugMode);
        delete[] body; // Deallocate the memory
    } */
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
    delete[] body;
    log("Snake Destroyed",debugMode);
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

bool SnakeClass::checkSnakeCollision()
{
    for (int i = 0; i < snakeSize; i++)
    {
        if(head.node.getGlobalBounds() == body[i].node.getGlobalBounds())
        {
            return true;
        }
    }

    return false;
}

bool SnakeClass::checkWallHit()
{
    if (head.node.getGlobalBounds().intersects(wall.top.getGlobalBounds()))
    {
        return true;
    }
    if(head.node.getGlobalBounds().intersects(wall.left.getGlobalBounds()))
    {
        return true;
    }
    if(head.node.getGlobalBounds().intersects(wall.bottom.getGlobalBounds()))
    {
        return true;
    }
    if(head.node.getGlobalBounds().intersects(wall.right.getGlobalBounds()))
    {
        return true;
    }

    return false;
}

void SnakeClass::dpad(void)
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && lastMove != 2)
    {
        if(!(lastMove == 1))
        {
            log("LEFT", debugMode);
            lastMove = 1;
        }
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && lastMove != 1)
    {
        if (!(lastMove == 2))
        {
            log("RIGHT", debugMode);
            lastMove = 2;
        }
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))&& lastMove != 4)
    {
        if (!(lastMove == 3))
        {
            log("UP", debugMode);
            lastMove = 3;
        }
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && lastMove != 3)
    {
        if (!(lastMove == 4))
        {
            log("DOWN", debugMode);
            lastMove = 4;
        }
    }
}

bool SnakeClass::checkFoodCollision(Food& food)
{
    if (head.node.getGlobalBounds().intersects(food.food.getGlobalBounds()))
    {
        return true;
    }
    else return false;
}

bool SnakeClass::checkFoodHitBody(Food& food)
{
    bool collide = false;
    for (int i = 0; i < snakeSize; i++)
    {
        if (body[i].node.getGlobalBounds().intersects(food.food.getGlobalBounds()))
        {
            collide = true;
        }
    }
    return collide;
}

void Food::generateFood(unsigned short width, unsigned short length)
{
    unsigned short min = genRandom(1, (width - 2));
    unsigned short max = genRandom(1, (length - 2));

    this->x = 25 * min;
    this->y = 25 * max;
    
    food.setPosition(x , y);
    
    food.setTexture(&normFoodTEX);
}