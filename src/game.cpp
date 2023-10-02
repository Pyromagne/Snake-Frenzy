#include "../inc/game.hpp"
#include "../inc/system.hpp"


Node::Node()
{
    nodeRect.setFillColor(sf::Color::White);
}

Wall::Wall(int width, int length, sf::RectangleShape sRect) : topRect(sRect), bottomRect(sRect), leftRect(sRect), rightRect(sRect)
{
    this->width = width;
    this->length = length;
    this->nodeSize.x  = sRect.getSize().x;
    this->nodeSize.y  = sRect.getSize().y;

    //plane.setTextureRect(sf::IntRect(0, 0, width * nodeSize.x, length * nodeSize.y));
    plane.setTextureRect(sf::IntRect(0, 0, width * nodeSize.x - (nodeSize.x*2), length * nodeSize.y - (nodeSize.y*2)));

    topRect = sf::RectangleShape(sf::Vector2f(float(width * nodeSize.x), nodeSize.y));
    leftRect = sf::RectangleShape(sf::Vector2f(nodeSize.x, float(length * nodeSize.y)));
    bottomRect = sf::RectangleShape(sf::Vector2f(float(width * nodeSize.x), nodeSize.y));
    rightRect = sf::RectangleShape(sf::Vector2f(nodeSize.x, float(length * nodeSize.y)));

}

void Wall::setWallPosition(float x, float y)
{
    this->x = x;
    this->y = y;

    plane.setPosition(x + this->nodeSize.x, y + this->nodeSize.y);
    //plane.setPosition(x , y);

    topRect.setPosition(x, y);
    leftRect.setPosition(x, y);
    bottomRect.setPosition(x, (y + (length * this->nodeSize.y)) - this->nodeSize.y);
    rightRect.setPosition((x + (width * this->nodeSize.x)) - this->nodeSize.x, y);
}

void Wall::setWallColor(sf::Color color)
{
    topRect.setFillColor(color);
    leftRect.setFillColor(color);
    bottomRect.setFillColor(color);
    rightRect.setFillColor(color);
}

void Wall::setWallTexture(sf::Texture& texture)
{
    topRect.setTexture(&texture);
    bottomRect.setTexture(&texture);
    leftRect.setTexture(&texture);
    rightRect.setTexture(&texture);
}

void Wall::setPlaneColor(sf::Color color)
{
    plane.setColor(color);
}

void Wall::setPlaneTexture(sf::Texture& texture)
{
    texture.setRepeated(true);
    plane.setTexture(texture);
}

void Wall::drawWall(sf::RenderWindow& window)
{
    window.draw(plane);
    window.draw(topRect);
    window.draw(leftRect);
    window.draw(bottomRect);
    window.draw(rightRect);
}

Food::Food(sf::RectangleShape sRect) : rect(sRect)
{
    nodeSize.x = rect.getSize().x;
    nodeSize.y = rect.getSize().y;
}

void Food::generateFood(unsigned short width, unsigned short length, unsigned short xWall, unsigned short yWall)
{
    unsigned short min = genRandom(1, (width - 2));
    unsigned short max = genRandom(1, (length - 2));

    this->x = (nodeSize.x * min) + xWall;
    this->y = (nodeSize.y * max) + yWall;

    rect.setPosition(x , y);
}

void Food::setFoodTexture(sf::Texture& texture)
{
    texture.setRepeated(true);
    rect.setTexture(&texture);
    //food.setTextureRect(sf::IntRect(0,0,50,50));
}

Snake::Snake()
{
    body = new Node[500];
    log("Snake Created",debugMode);
}

Snake::Snake(unsigned int maxSnakeSize, float nodeSize)
{
    this->nodeSize = nodeSize;
    body = new Node[maxSnakeSize];
    log("Snake Created",debugMode);
}

Snake::Snake(unsigned int maxSnakeSize, unsigned int snakeSize, float nodeSize)
{
    this->nodeSize = nodeSize;
    body = new Node[maxSnakeSize];
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

Snake::~Snake()
{
    delete[] body;
    log("Snake Destroyed",debugMode);
}

void Snake::dpad(void)
{
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && lastMove2 != right)
    {
        if(!(lastMove2 == left))
        {
            log("LEFT", debugMode);
            lastMove = left;
        }
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && lastMove2 != left)
    {
        if (!(lastMove2 == right))
        {
            log("RIGHT", debugMode);
            lastMove = right;
        }
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))&& lastMove2 != down)
    {
        if (!(lastMove2 == up))
        {
            log("UP", debugMode);
            lastMove = up;
        }
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && lastMove2 != up)
    {
        if (!(lastMove2 == down))
        {
            log("DOWN", debugMode);
            lastMove = down;
        }
    }
}

void Snake::drawSnake(sf::RenderWindow& window)
{
    /* if (lastMove == null)
    {
        head.prevNodes = sf::Vector2f(175.f, 200.f);
    } */

    body[0].nextNodes = &head.prevNodes;
    body[0].nodeRect.setPosition(*body[0].nextNodes);

    for (unsigned short i = 0; i < snakeSize; i++)
    {
        body[i+1].nextNodes = &body[i].prevNodes;
        body[i+1].nodeRect.setPosition(body[i+1].prevNodes);
    }

    /*SETTING SNAKE TEXTURES HERE IS NOT FINAL*/
    head.nodeRect.setTexture(&headTEX);

    for (unsigned short i = 0; i < snakeSize; i++)
    {
        body[i].nodeRect.setTexture(&bodyTEX);
        window.draw(body[i].nodeRect);
    }

    window.draw(head.nodeRect);
}

void Snake::updatePosition(float speed = 100.f)
{
    if (updatePositionCLK.getElapsedTime().asMilliseconds() > speed)
    {
        head.prevNodes = head.nodeRect.getPosition();
        for (unsigned short i = 0; i < snakeSize; i++)
        {
            body[i+1].prevNodes = body[i].nodeRect.getPosition();
        }

        sf::Vector2f currentPosition = head.nodeRect.getPosition();
        if (lastMove == left)
        {
            currentPosition.x -= nodeSize;
            head.nodeRect.setPosition(currentPosition);
        }
        else if (lastMove == right)
        {
            currentPosition.x += nodeSize;
            head.nodeRect.setPosition(currentPosition);
        }
        else if (lastMove == up)
        {
            currentPosition.y -= nodeSize;
            head.nodeRect.setPosition(currentPosition);
        }
        else if (lastMove == down)
        {
            currentPosition.y += nodeSize;
            head.nodeRect.setPosition(currentPosition);
        }
        lastMove2 = lastMove;

        updatePositionCLK.restart();
    }
}

void Snake::setSnakeTexture(sf::Texture& headTEX, sf::Texture& bodyTEX)
{
    this->headTEX.setRepeated(true);
    this->bodyTEX.setRepeated(true);
    this->headTEX = headTEX;
    this->bodyTEX = bodyTEX;
}

bool Snake::checkSnakeCollision()
{
    for (unsigned short i = 0; i < snakeSize; i++)
    {
        if(head.nodeRect.getGlobalBounds() == body[i].nodeRect.getGlobalBounds())
        {
            return true;
        }
    }

    return false;
}

bool Snake::checkWallHit(Wall& wall)
{
    if (head.nodeRect.getGlobalBounds().intersects(wall.topRect.getGlobalBounds()))
    {
        return true;
    }
    if(head.nodeRect.getGlobalBounds().intersects(wall.leftRect.getGlobalBounds()))
    {
        return true;
    }
    if(head.nodeRect.getGlobalBounds().intersects(wall.bottomRect.getGlobalBounds()))
    {
        return true;
    }
    if(head.nodeRect.getGlobalBounds().intersects(wall.rightRect.getGlobalBounds()))
    {
        return true;
    }

    return false;
}

bool Snake::checkFoodCollision(Food& food)
{
    if (head.nodeRect.getGlobalBounds().intersects(food.rect.getGlobalBounds()))
    {
        return true;
    }
    else return false;
}

bool Snake::checkFoodHitBody(Food& food)
{
    bool collide = false;
    for (unsigned short i = 0; i < snakeSize; i++)
    {
        if (body[i].nodeRect.getGlobalBounds().intersects(food.rect.getGlobalBounds()))
        {
            collide = true;
        }
    }
    return collide;
}
