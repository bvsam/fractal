#include <SFML/Graphics.hpp>

#ifndef RENDERER_HPP
#define RENDERER_HPP

template <typename T>
class FractalRenderer
{
    sf::VertexArray vertex_array;
    sf::Vector2u dimensions;

    void set_pixel_colour(uint32_t x, uint32_t y, sf::Color color)
    {
        const size_t index = y * dimensions.x + x;
        vertex_array[index].color = color;
    }

public:
    FractalRenderer(uint32_t width, uint32_t height)
        : vertex_array{sf::PrimitiveType::Points, width * height}, dimensions{width, height}
    {
        // Initialize the position of each of the points
        size_t index = 0;
        for (uint32_t y = 0; y < height; y++)
        {
            for (uint32_t x = 0; x < width; x++)
            {
                vertex_array[index].position = sf::Vector2f{static_cast<float>(x), static_cast<float>(y)};
                set_pixel_colour(x, y, sf::Color::Magenta);
                index++;
            }
        }
    }

    const sf::VertexArray &get_state()
    {
        return vertex_array;
    }
};

#endif