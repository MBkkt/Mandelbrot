#include <vector>
#include <thread>

#include "Mandelbrot.h"


Mandelbrot::Mandelbrot(size_t width, size_t height)
    : IMAGE_WIDTH(width), IMAGE_HEIGHT(height) {
    for (int i = 0; i <= MAX; ++i) {
        colors[i] = getColor(i);
    }
}

int Mandelbrot::mandelbrot(double startReal, double startImag) const {
    double zReal = startReal;
    double zImag = startImag;

    for (int counter = 0; counter < MAX; ++counter) {
        double r2 = zReal * zReal;
        double i2 = zImag * zImag;
        if (r2 + i2 > 4.0) {
            return counter;
        }
        zImag = 2.0 * zReal * zImag + startImag;
        zReal = r2 - i2 + startReal;
    }
    return MAX;
}

sf::Color Mandelbrot::getColor(int iterations) const {
    int r = 0, g = 0, b = 0;

    // colour gradient:      Black -> Red -> Magenta -> Blue -> Cyan -> Green -> Yellow -> Black
    // corresponding values: 0     -> 32  -> 64      -> 96   -> 128  -> 160   -> 192    -> 224
    if (iterations < 32) {
        // (0, 0, 0) -> (255, 0, 0)
        r = iterations * 8;
        g = 0;
        b = 0;
    } else if (iterations < 64) {
        // (255, 0, 0) -> (255, 0, 255)
        r = 255;
        g = 0;
        b = iterations * 8;
    } else if (iterations < 96) {
        // (255, 0, 255) -> (0, 0, 255)
        r = 255 - (iterations * 8);
        g = 0;
        b = 255;
    } else if (iterations < 128) {
        // (0, 0, 255) -> (0, 255, 255)
        r = 0;
        g = iterations * 8;
        b = 255;
    } else if (iterations < 160) {
        // (0, 255, 255) -> (0, 255, 0)
        r = 0;
        g = 255;
        b = 255 - (iterations * 8);
    } else if (iterations < 192) {
        // (0, 255, 0) -> (255, 255, 0)
        r = iterations * 8;
        g = 255;
        b = 0;
    } else {
        // (255, 255, 0) -> (0, 0, 0)
        r = 255 - (iterations * 8);
        g = 255 - (iterations * 8);
        b = 0;
    }
    return sf::Color(r, g, b);
}

void
Mandelbrot::updateImageSlice(double zoom, double offsetX, double offsetY, sf::Image & image, int minY, int maxY) const {
    double real = -(IMAGE_WIDTH / 2.0 * zoom) + offsetX;
    double imagstart = minY * zoom - IMAGE_HEIGHT / 2.0 * zoom + offsetY;
    for (int x = 0; x < IMAGE_WIDTH; ++x, real += zoom) {
        double imag = imagstart;
        for (int y = minY; y < maxY; ++y, imag += zoom) {
            int value = mandelbrot(real, imag);
            image.setPixel(x, y, colors[value]);
        }
    }
}


void Mandelbrot::updateImage(double zoom, double offsetX, double offsetY, sf::Image & image) const {
    const int STEP = IMAGE_HEIGHT / std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    for (int i = 0; i < IMAGE_HEIGHT; i += STEP) {
        threads.emplace_back(
            &Mandelbrot::updateImageSlice, *this,
            zoom, offsetX, offsetY, std::ref(image), i, std::min(i + STEP, IMAGE_HEIGHT)
        );
    }
    for (auto & t : threads) {
        t.join();
    }
}
