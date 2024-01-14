#include <SFML/Graphics.hpp>
#include "renderer.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main()
{
    FractalRenderer<double> fractalRenderer{WINDOW_WIDTH, WINDOW_HEIGHT};
    // create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fractal");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(fractalRenderer.get_state());

        // end the current frame
        window.display();
    }

    return 0;
}