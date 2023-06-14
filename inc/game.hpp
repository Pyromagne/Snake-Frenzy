#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "system.hpp"

struct Snake
{
    sf::RectangleShape node = sf::RectangleShape(sf::Vector2f(25.f,25.f));
    sf::Vector2f* nextNodes;
    sf::Vector2f prevNodes;

    Snake();
};

class SnakeClass
{
    public:
        int snakeSize = 10;
        Snake head;
        Snake* body;
        int lastMove = 0;
        sf::Clock updatePositionCLK;
        sf::Texture headSkin;
        sf::Texture bodySkin;
        SnakeClass();
        SnakeClass(unsigned int maxSnakeSize);
        SnakeClass(unsigned int maxSnakeSize, unsigned int snakeSize);
        ~SnakeClass();

        void drawSnake(sf::RenderWindow& window);
        void updatePosition(float speed);
        void dpad(void);
    //end of public
};

#endif // GAME_HPP_INCLUDED
