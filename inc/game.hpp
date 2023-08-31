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

class Food
{
    public:
    sf::RectangleShape food = sf::RectangleShape(sf::Vector2f(25.f,25.f));
    unsigned short x = 0;
    unsigned short y = 0;

    sf::Texture normFoodTEX;
    sf::Clock foodCLK;
    void generateFood(unsigned short width, unsigned short length);

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
        sf::Texture wallSkin;
        Wall wall = Wall(24,24);
        //Wall wall = Wall(32,24); max wall value

        SnakeClass();
        SnakeClass(unsigned int maxSnakeSize);
        SnakeClass(unsigned int maxSnakeSize, unsigned int snakeSize);
        ~SnakeClass();

        void drawSnake(sf::RenderWindow& window);
        bool checkSnakeCollision();
        bool checkWallHit();
        void updatePosition(float speed);
        void dpad(void);
        bool checkFoodCollision(Food& food);
        bool checkFoodHitBody(Food& food);
    //end of public
};



#endif // GAME_HPP_INCLUDED
