#include "../inc/game.hpp"
#include "../inc/system.hpp"


Node::Node()
{
    nodeRect.setFillColor(sf::Color::White);
}

Wall::Wall(int width, int length)
{
    this->width = width;
    this->length = length;

    plane.setTextureRect(sf::IntRect(0, 0, width * 25.f - 50.f, length * 25.f - 50.f));
    
    top = sf::RectangleShape(sf::Vector2f(float(width*25), 25.f));
    left = sf::RectangleShape(sf::Vector2f(25.f, float(length*25)));
    bottom = sf::RectangleShape(sf::Vector2f(float(width*25), 25.f));
    right = sf::RectangleShape(sf::Vector2f(25.f, float(length*25)));

}

void Wall::setWallPosition(float x, float y)
{
    this->x = x;
    this->y = y;

    plane.setPosition(x + 25.f, y + 25.f);

    top.setPosition(x, y);
    left.setPosition(x, y);
    bottom.setPosition(x, (y + (length*25))-25);
    right.setPosition((x + (width*25))-25, y);
}

void Wall::setWallColor(sf::Color color)
{
    top.setFillColor(color);
    left.setFillColor(color);
    bottom.setFillColor(color);
    right.setFillColor(color);
}

void Wall::setWallTexture(sf::Texture& texture)
{
    top.setTexture(&texture);
    bottom.setTexture(&texture);
    left.setTexture(&texture);
    right.setTexture(&texture);
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
    window.draw(top);
    window.draw(left);
    window.draw(bottom);
    window.draw(right);
}
void Food::generateFood(unsigned short width, unsigned short length, unsigned short xWall, unsigned short yWall)
{
    unsigned short min = genRandom(1, (width - 2));
    unsigned short max = genRandom(1, (length - 2));

    this->x = (25 * min) + xWall;
    this->y = (25 * max) + yWall;

    food.setPosition(x , y);
}

void Food::setFoodTexture(sf::Texture& texture)
{
    food.setTexture(&texture);
}

Snake::Snake()
{
    body = new Node[500];
    log("Snake Created",debugMode);
}

Snake::Snake(unsigned int maxSnakeSize)
{
    body = new Node[maxSnakeSize];
    log("Snake Created",debugMode);
}

Snake::Snake(unsigned int maxSnakeSize, unsigned int snakeSize)
{
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
            currentPosition.x -= 25.f;
            head.nodeRect.setPosition(currentPosition);
        }
        else if (lastMove == right)
        {
            currentPosition.x += 25.f;
            head.nodeRect.setPosition(currentPosition);
        }
        else if (lastMove == up)
        {
            currentPosition.y -= 25.f;
            head.nodeRect.setPosition(currentPosition);
        }
        else if (lastMove == down)
        {
            currentPosition.y += 25.f ;
            head.nodeRect.setPosition(currentPosition);
        }
        lastMove2 = lastMove;

        updatePositionCLK.restart();
    }
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

bool Snake::checkWallHit()
{
    if (head.nodeRect.getGlobalBounds().intersects(wall.top.getGlobalBounds()))
    {
        return true;
    }
    if(head.nodeRect.getGlobalBounds().intersects(wall.left.getGlobalBounds()))
    {
        return true;
    }
    if(head.nodeRect.getGlobalBounds().intersects(wall.bottom.getGlobalBounds()))
    {
        return true;
    }
    if(head.nodeRect.getGlobalBounds().intersects(wall.right.getGlobalBounds()))
    {
        return true;
    }

    return false;
}

bool Snake::checkFoodCollision(Food& food)
{
    if (head.nodeRect.getGlobalBounds().intersects(food.food.getGlobalBounds()))
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
        if (body[i].nodeRect.getGlobalBounds().intersects(food.food.getGlobalBounds()))
        {
            collide = true;
        }
    }
    return collide;
}
