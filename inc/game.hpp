#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "system.hpp"

enum direction
{
    null = 0,
    left = 1,
    right = 2,
    up = 3,
    down = 4
};

struct Node
{
    Node();
    sf::RectangleShape nodeRect = sf::RectangleShape(sf::Vector2f(25.f,25.f));
    sf::Vector2f* nextNodes;
    sf::Vector2f prevNodes;
    sf::Vector2i gridPosition; /* For future features make a position map in grid*/ /* Not yet use */
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

class Snake
{
    public:
        Snake();
        Snake(unsigned int maxSnakeSize);
        Snake(unsigned int maxSnakeSize, unsigned int snakeSize);
        ~Snake();

        unsigned int snakeSize = 10;
        direction lastMove = null;
        direction lastMove2 = null;
        sf::Clock updatePositionCLK;
        sf::Texture headTEX;
        sf::Texture bodyTEX;
        Node head;
        Node* body = nullptr;
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
