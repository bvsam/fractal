#include <SFML/Graphics.hpp>
#include "renderer.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main()
{
    using PrecisionType = double;
    const sf::Vector2<PrecisionType> iteration_constant{-0.8, 0.156};
    const uint32_t max_iterations = 1000;
    const uint32_t n_samples = 16;

    FractalRenderer<PrecisionType> fractal_renderer{WINDOW_WIDTH, WINDOW_HEIGHT, iteration_constant, max_iterations, n_samples};
    PrecisionType zoom = 1.0;
    PrecisionType zoom_multiplier = 1.5;
    bool zoom_in = false;
    bool zoom_out = false;

    sf::RenderWindow window{sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Fractal"};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        fractal_renderer.generate(zoom);
        window.draw(fractal_renderer.get_state());
        window.display();

        // Check for key presses and determine whether to zoom in or out
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            zoom_in = true;
        }
        else
        {
            zoom_in = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            zoom_out = true;
        }
        else
        {
            zoom_out = false;
        }

        // Adjust zoom
        if (zoom_in)
        {
            zoom *= zoom_multiplier;
        }
        if (zoom_out)
        {
            zoom /= zoom_multiplier;
        }
    }

    return 0;
}