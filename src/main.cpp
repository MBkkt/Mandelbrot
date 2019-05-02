#include "Mandelbrot.h"

int main() {
    double offsetX = 0; // and move around
    double offsetY = 0;
    double zoom = 0.002; // allow the user to zoom in and out...
    Mandelbrot mb(1600, 800);

    sf::RenderWindow window(sf::VideoMode(IMAGE_WIDTH, IMAGE_HEIGHT), "Mandelbrot");
    window.setFramerateLimit(0);

    sf::Image image;
    image.create(mb.IMAGE_WIDTH, mb.IMAGE_HEIGHT, sf::Color(0, 0, 0));
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Event event {};
    double offsetX = 0;
    double offsetY = 0;
    double zoom = 0.002;
    for (bool stateChanged = true; window.isOpen();) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            zoom *= 0.98;
            stateChanged = true;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            zoom /= 0.98;
            stateChanged = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            offsetY -= 8 * zoom;
            stateChanged = true;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            offsetY += 8 * zoom;
            stateChanged = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            offsetX -= 8 * zoom;
            stateChanged = true;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            offsetX += 8 * zoom;
            stateChanged = true;
        }
        if (stateChanged) {
            mb.updateImage(zoom, offsetX, offsetY, image);
            texture.loadFromImage(image);
            sprite.setTexture(texture);
            stateChanged = false;
        }
        window.draw(sprite);
        window.display();
    }
}