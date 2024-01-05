#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "system.hpp"

extern sf::Font defaultFont;
extern sf::Vector2i resolution;

namespace color{
    const sf::Color ONYX = sf::Color(0x353839ff);
}

enum direction
{
    null = 0,
    left = 1,
    right = 2,
    up = 3,
    down = 4
};

enum speed
{
    spd1 = 75,
    spd2 = 70,
    spd3 = 65,
    spd4 = 60,
    spd5 = 55,
    spd6 = 50,
    spd7 = 45,
    spd8 = 40,
    spd9 = 35,
    spd10 = 30,
};

class Node
{
    public:
    Node(); // implement initialization list in the future for nodeRect like in the class Food
    sf::RectangleShape nodeRect = sf::RectangleShape(sf::Vector2f(25, 25));
    sf::Vector2f* nextNodes;
    sf::Vector2f prevNodes;
    float nodeSize = 25.f;
    sf::Vector2i gridPosition; /* For future features make a position map in grid*/ /* Not yet use */

};

class Wall
{
    public:
    Wall(int width, int length, sf::RectangleShape sRect);

    unsigned short width;
    unsigned short length;
    unsigned short x;
    unsigned short y;
    sf::Vector2f nodeSize;

    sf::RectangleShape topRect;
    sf::RectangleShape bottomRect;
    sf::RectangleShape leftRect;
    sf::RectangleShape rightRect;

    //sf::Sprite plane;
    sf::RectangleShape plane;

    void setWallPosition(float x, float y);
    void setWallColor(sf::Color);
    void setWallTexture(sf::Texture& texture);
    void setPlaneColor(sf::Color);
    void setPlaneTexture(sf::Texture& texture);
    void drawWall(sf::RenderWindow& window);
};

class Food
{  
    public:

        Food(sf::RectangleShape sRect);
        Food();

        sf::Vector2f nodeSize; //
        unsigned short x = 0;
        unsigned short y = 0;
        sf::RectangleShape rect;

        void generateFood(unsigned short width, unsigned short length, unsigned short xWall = 0, unsigned short yWall = 0);
        void setFoodTexture(sf::Texture& texture);
        void setFoodColor(sf::Color);
        void setRectangle(sf::RectangleShape rect);
    //end of public
};

class Snake
{
    public:
        Snake();
        Snake(unsigned int maxSnake, float nodeSize);
        Snake(unsigned int maxSnakeSize, unsigned int snakeSize, float nodeSize);
        ~Snake();

        unsigned int snakeSize = 10;
        float nodeSize;
        direction lastMove = null;
        direction lastMove2 = null;
        sf::Clock updatePositionCLK;
        sf::Texture headTEX;
        sf::Texture bodyTEX;
        Node head;
        Node* body = nullptr;
        //Wall wall = Wall(36,25); /* max value of wall is calculated by dividing resolution by snakeSize */ /* adding wall to the SnakeClass is not final it can be independent object */

        void dpad(void);
        void drawSnake(sf::RenderWindow& window);
        void updatePosition(float speed);
        void setSnakeTexture(sf::Texture& headTEX, sf::Texture& bodyTEX);
        bool checkSnakeCollision(void);
        bool checkWallHit(Wall& wall);
        bool checkFoodCollision(Food& food);
        bool checkFoodHitBody(Food& food);
    //end of public
};

#endif // GAME_HPP_INCLUDED
