#ifndef SYSTEM_HPP_INCLUDED
#define SYSTEM_HPP_INCLUDED

#include <ctime>
#include <chrono>
#include <iomanip>
#include <string>
#include <ctime>
#include <stdio.h>
#include "wtypes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ColorEscape.hpp"

extern bool debugMode;
extern sf::Vector2f snakeSize;

void log(std::string log, bool debugMode);
void err(std::string err, bool debugMode);
unsigned short genRandom(unsigned short min,unsigned short max);
sf::Vector2i GetDesktopResolution(void);
sf::Color hsv(int hue, float sat, float val);


#endif // SYSTEM_HPP_INCLUDED
