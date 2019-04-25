#include "Mandelbrot.h"

int main() {
    double offsetX = 0; // and move around
    double offsetY = 0;
    double zoom = 0.002; // allow the user to zoom in and out...
    Mandelbrot mb(1600, 800);

    sf::RenderWindow window(sf::VideoMode(mb.IMAGE_WIDTH, mb.IMAGE_HEIGHT), "Mandelbrot");
    window.setFramerateLimit(0);

    sf::Image image;
    image.create(mb.IMAGE_WIDTH, mb.IMAGE_HEIGHT, sf::Color(0, 0, 0));
    sf::Texture texture;
    sf::Sprite sprite;

    for (bool stateChanged = true; window.isOpen();) {
        sf::Event event {};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                stateChanged = true; // image needs to be recreated when the user changes zoom or offset
                switch (event.key.code) {
                    case sf::Keyboard::E:
                        zoom *= 0.96;
                        break;
                    case sf::Keyboard::Q:
                        zoom /= 0.96;
                        break;
                    case sf::Keyboard::W:
                        offsetY -= 8 * zoom;
                        break;
                    case sf::Keyboard::S:
                        offsetY += 8 * zoom;
                        break;
                    case sf::Keyboard::A:
                        offsetX -= 8 * zoom;
                        break;
                    case sf::Keyboard::D:
                        offsetX += 8 * zoom;
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    default:
                        stateChanged = false;
                        break;
                }
            }
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