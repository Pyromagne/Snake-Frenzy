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

void Wall::setWallTexture(sf::Texture& texture)
{
    top.setTexture(&texture);
    bottom.setTexture(&texture);
    left.setTexture(&texture);
    right.setTexture(&texture);
}

void Wall::drawWall(sf::RenderWindow& window)
{
    window.draw(top);
    window.draw(left);
    window.draw(bottom);
    window.draw(right);
}

void Food::generateFood(unsigned short width, unsigned short length)
{
    unsigned short min = genRandom(1, (width - 2));
    unsigned short max = genRandom(1, (length - 2));

    this->x = 25 * min;
    this->y = 25 * max;

    food.setPosition(x , y);
}

void Food::setFoodTexture(sf::Texture& texture)
{
    food.setTexture(&texture);
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
    delete[] body;
    log("Snake Destroyed",debugMode);
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

void SnakeClass::drawSnake(sf::RenderWindow& window)
{
    body[0].nextNodes = &head.prevNodes;
    body[0].node.setPosition(*body[0].nextNodes);

    for (unsigned short i = 0; i < snakeSize; i++)
    {
        body[i+1].nextNodes = &body[i].prevNodes;
        body[i+1].node.setPosition(body[i+1].prevNodes);
    }

    /*SETTING SNAKE TEXTURES HERE IS NOT FINAL*/
    head.node.setTexture(&headTEX);

    for (unsigned short i = 0; i < snakeSize; i++)
    {
        body[i].node.setTexture(&bodyTEX);
        window.draw(body[i].node);
    }
    
    window.draw(head.node);
}

void SnakeClass::updatePosition(float speed = 100.f)
{
    if (updatePositionCLK.getElapsedTime().asMilliseconds() > speed)
    {
        head.prevNodes = head.node.getPosition();
        for (unsigned short i = 0; i < snakeSize; i++)
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

bool SnakeClass::checkSnakeCollision()
{
    for (unsigned short i = 0; i < snakeSize; i++)
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
    for (unsigned short i = 0; i < snakeSize; i++)
    {
        if (body[i].node.getGlobalBounds().intersects(food.food.getGlobalBounds()))
        {
            collide = true;
        }
    }
    return collide;
}