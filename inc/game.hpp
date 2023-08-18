#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "system.hpp"

struct Snake
{
    sf::RectangleShape node = sf::RectangleShape(sf::Vector2f(25.f,25.f));
    sf::Vector2f* nextNodes;
    sf::Vector2f prevNodes;
    sf::Vector2i gridPosition;

    Snake();
};

struct Wall
{
    sf::RectangleShape top;
    sf::RectangleShape bottom;
    sf::RectangleShape left;
    sf::RectangleShape right;

    int width;
    int length;
    void setWallColor(sf::Color);
    void setWallPosition(float x, float y);
    Wall(int width, int length);
};

class SnakeClass
{
    public:
        int snakeSize = 10;
        Snake head;
        Snake* body = nullptr;
        int lastMove = 0;
        sf::Clock updatePositionCLK;
        sf::Texture headSkin;
        sf::Texture bodySkin;
        Wall safeArea = Wall(20,20);

        SnakeClass();
        SnakeClass(unsigned int maxSnakeSize);
        SnakeClass(unsigned int maxSnakeSize, unsigned int snakeSize);
        ~SnakeClass();

        void drawSnake(sf::RenderWindow& window);
        bool checkSnakeCollision();
        bool checkWallHit();
        void updatePosition(float speed);
        void dpad(void);
    //end of public
};

#endif // GAME_HPP_INCLUDED
