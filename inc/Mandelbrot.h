#pragma once

#include <array>

#include <SFML/Graphics.hpp>


class Mandelbrot {
public:
    explicit Mandelbrot(size_t width, size_t height);

    void updateImage(double zoom, double offsetX, double offsetY, sf::Image & image) const;


private:
    int mandelbrot(double startReal, double startImag) const;

    sf::Color getColor(int iterations) const;

    void updateImageSlice(double zoom, double offsetX, double offsetY, sf::Image & image, int minY, int maxY) const;

    int const WIDTH;
    int const HEIGHT;
    static constexpr int MAX = 223;
    std::array<sf::Color, MAX + 1> colors;
};