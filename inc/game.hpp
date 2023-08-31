#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "system.hpp"

struct Snake
{
    Snake();
    sf::RectangleShape node = sf::RectangleShape(sf::Vector2f(25.f,25.f));
    sf::Vector2f* nextNodes;
    sf::Vector2f prevNodes;
    sf::Vector2i gridPosition;
};

struct Wall
{
    Wall(int width, int length);

    unsigned short width;
    unsigned short length;
    sf::RectangleShape top;
    sf::RectangleShape bottom;
    sf::RectangleShape left;
    sf::RectangleShape right;

    void setWallColor(sf::Color);
    void setWallPosition(float x, float y);
    void setWallTexture(sf::Texture& texture);
    void drawWall(sf::RenderWindow& window);
};

class Food
{
    public:
        unsigned short x = 0;
        unsigned short y = 0;
        sf::RectangleShape food = sf::RectangleShape(sf::Vector2f(25.f,25.f));

        void generateFood(unsigned short width, unsigned short length);
        void setFoodTexture(sf::Texture& texture);
    //end of public
};

class SnakeClass
{
    public:
        SnakeClass();
        SnakeClass(unsigned int maxSnakeSize);
        SnakeClass(unsigned int maxSnakeSize, unsigned int snakeSize);
        ~SnakeClass();

        unsigned int snakeSize = 10;
        unsigned short lastMove = 0;
        sf::Clock updatePositionCLK;
        sf::Texture headTEX;
        sf::Texture bodyTEX;
        Snake head;
        Snake* body = nullptr;
        Wall wall = Wall(24,24); /* Wall wall = Wall(32,24); max wall value */ /* adding wall to the SnakeClass is not final it can be independent object */

        void dpad(void);
        void drawSnake(sf::RenderWindow& window);
        void updatePosition(float speed);
        bool checkSnakeCollision(void);
        bool checkWallHit(void);
        bool checkFoodCollision(Food& food);
        bool checkFoodHitBody(Food& food);
    //end of public
};

#endif // GAME_HPP_INCLUDED
