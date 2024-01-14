#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

#define MOD_VALUE 2.0f

// Returns the mod of a complex number
// https://en.wikipedia.org/wiki/Complex_modulus
template <typename PrecisionType>
inline PrecisionType complex_mod(PrecisionType real, PrecisionType imaginary)
{
    return std::sqrt(real * real + imaginary * imaginary);
}

template <typename PrecisionType>
uint32_t julia_set_iterator(const sf::Vector2<PrecisionType> &initial, const sf::Vector2<PrecisionType> &constant, uint32_t max_iterations)
{
    uint32_t iterations = 0;
    PrecisionType real = initial.x;
    PrecisionType imaginary = initial.y;

    while (complex_mod<PrecisionType>(real, imaginary) < PrecisionType{MOD_VALUE} && iterations < max_iterations)
    {
        // z = z^2 + c
        // Square the number
        // Square of a complex number (a + bi) is (a^2 - b^2 + 2abi)
        const PrecisionType prev_real = real;
        real = real * real - imaginary * imaginary;
        imaginary = PrecisionType{2.0} * prev_real * imaginary;
        // Add the constant
        real += constant.x;
        imaginary += constant.y;

        iterations++;
    }
    return iterations;
}

template <typename PrecisionType>
class FractalRenderer
{
    sf::VertexArray vertex_array;
    const sf::Vector2u dimensions;
    // Store window_center as a PrecisionType vector to prevent repeated static casts
    const sf::Vector2<PrecisionType> window_center;
    const uint32_t MAX_ITERATIONS;
    const sf::Vector2<PrecisionType> &ITERATION_CONSTANT;

    void set_pixel_color(uint32_t x, uint32_t y, sf::Color color)
    {
        const size_t index = y * dimensions.x + x;
        vertex_array[index].color = color;
    }

public:
    FractalRenderer(uint32_t width, uint32_t height, const sf::Vector2<PrecisionType> &constant, uint32_t max_iterations = 1000)
        : vertex_array{sf::PrimitiveType::Points, width * height},
          dimensions{width, height},
          window_center{static_cast<PrecisionType>(0.5) * static_cast<PrecisionType>(width), static_cast<PrecisionType>(0.5) * static_cast<PrecisionType>(height)},
          ITERATION_CONSTANT{constant},
          MAX_ITERATIONS{max_iterations}
    {
        // Initialize the position of each of the points
        size_t index = 0;
        for (uint32_t y = 0; y < height; y++)
        {
            for (uint32_t x = 0; x < width; x++)
            {
                vertex_array[index].position = sf::Vector2f{static_cast<float>(x), static_cast<float>(y)};
                index++;
            }
        }
        generate();
    }

    void generate()
    {
        for (uint32_t y = 0; y < dimensions.y; y++)
        {
            for (uint32_t x = 0; x < dimensions.x; x++)
            {
                // Set the colour of each pixel
                // Map the pixel coordinates into a range of about -2 to 2
                const PrecisionType x_val = (static_cast<PrecisionType>(x) - window_center.x) / window_center.x * static_cast<PrecisionType>(MOD_VALUE);
                const PrecisionType y_val = (static_cast<PrecisionType>(y) - window_center.y) / window_center.y * static_cast<PrecisionType>(MOD_VALUE);
                const sf::Vector2<PrecisionType> initial{x_val, y_val};
                // Determine the number of iterations for the given pixel
                const uint32_t iterations = julia_set_iterator<PrecisionType>(initial, ITERATION_CONSTANT, MAX_ITERATIONS);
                // Determine the ratio of iterations taken to the max number of iterations allowed
                const float ratio = static_cast<float>(iterations) / static_cast<float>(MAX_ITERATIONS);
                // Map the resulting ratio onto a colour scale
                // Use grayscale to keep things basic
                const uint8_t value = static_cast<uint8_t>(ratio * 255.0f);
                const sf::Color color{value, value, value};
                set_pixel_color(x, y, color);
            }
        }
    }

    const sf::VertexArray &get_state()
    {
        return vertex_array;
    }
};

#endif