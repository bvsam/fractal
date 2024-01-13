#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main()
{
    sf::VertexArray vertexArray{sf::PrimitiveType::Points, WINDOW_WIDTH * WINDOW_HEIGHT};
    uint32_t idx = 0;
    for (uint32_t x{0}; x < WINDOW_WIDTH; ++x)
    {
        for (uint32_t y{0}; y < WINDOW_HEIGHT; ++y)
        {
            vertexArray[idx].position = sf::Vector2f{static_cast<float>(x), static_cast<float>(y)};
            vertexArray[idx].color = sf::Color::Green;
            idx++;
        }
    }

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
        window.draw(vertexArray);

        // end the current frame
        window.display();
    }

    return 0;
}