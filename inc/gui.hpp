#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "sfmlbutton.hpp"
#include "system.hpp"
#include "game.hpp"

void mainMenuUI(sf::RenderWindow& window);
//bool isPressed parameter is not necessary it will be remove soon
void gameClassicUI(sf::RenderWindow& window, bool isPressed);
void gameArcadeUI(sf::RenderWindow& window);
void drawPause(sf::RenderWindow& window);
void drawGameOver(sf::RenderWindow& window, unsigned int score);


#endif // GUI_HPP_INCLUDED
