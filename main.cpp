#include <SFML/Graphics.hpp>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <string>
#include "ColorEscape.hpp"
#include "sfmlbutton.hpp"

void log(std::string log)
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);
    ce::setForegroundColor(50);
    std::clog << std::put_time(&tm, "[%y:%m:%d]%H:%M:%S");
    ce::setForegroundColor(190);
    std::clog << " : " << log << std::endl;
    ce::reset();
}

void err(void)
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);
    ce::setForegroundColor(50);
    std::clog << std::put_time(&tm, "[%y:%m:%d]%H:%M:%S");
    ce::setForegroundColor(160);
    std::clog << ": " << std::endl;
}

int main()
{
    enable_vtp();
    log("Game Started");
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(sprite);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
