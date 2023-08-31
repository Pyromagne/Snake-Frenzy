#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "sfmlbutton.hpp"
#include "system.hpp"
#include "game.hpp"

void mainMenuUI(sf::RenderWindow& window);
//bool isPressed is not necessary it will be remove soon
void gameMenuUI(sf::RenderWindow& window, bool isPressed);


#endif // GUI_HPP_INCLUDED
