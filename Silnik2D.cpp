
#include <SFML/Graphics.hpp>
#include <iostream>

class Point2D {
public:
    float x, y;

    Point2D(float x = 0, float y = 0) : x(x), y(y) {}

    // Przesunięcie punktu
    void move(float dx, float dy) {
        x += dx;
        y += dy;
    }
};
class InputHandler {
public:
    bool isKeyPressed(sf::Keyboard::Key key) {
        return sf::Keyboard::isKeyPressed(key);
    }

    Point2D getMousePosition(const sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return Point2D(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    }
};
class Renderer {
public:
    void drawPoint(sf::RenderWindow& window, const Point2D& point) {
        sf::CircleShape shape(5);
        shape.setPosition(point.x, point.y);
        shape.setFillColor(sf::Color::Red);
        window.draw(shape);
    }

    void drawLine(sf::RenderWindow& window, const Point2D& start, const Point2D& end) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(start.x, start.y)),
            sf::Vertex(sf::Vector2f(end.x, end.y))
        };
        window.draw(line, 2, sf::Lines);
    }

    void drawRectangle(sf::RenderWindow& window, const Point2D& topLeft, float width, float height) {
        sf::RectangleShape rectangle(sf::Vector2f(width, height));
        rectangle.setPosition(topLeft.x, topLeft.y);
        rectangle.setFillColor(sf::Color::Green);
        window.draw(rectangle);
    }
};
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "2D Silnik");

    Point2D point(100, 100);
    InputHandler input;
    Renderer renderer;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Obsługa wejścia - przesuwanie punktu klawiszami strzałek
        if (input.isKeyPressed(sf::Keyboard::Left)) {
            point.move(-1, 0);
        }
        if (input.isKeyPressed(sf::Keyboard::Right)) {
            point.move(1, 0);
        }
        if (input.isKeyPressed(sf::Keyboard::Up)) {
            point.move(0, -1);
        }
        if (input.isKeyPressed(sf::Keyboard::Down)) {
            point.move(0, 1);
        }

        // Wyświetlanie współrzędnych myszy w konsoli
        Point2D mousePos = input.getMousePosition(window);
        std::cout << "Mouse Position: (" << mousePos.x << ", " << mousePos.y << ")\n";

        // Rysowanie
        window.clear();
        renderer.drawPoint(window, point);
        renderer.drawRectangle(window, Point2D(300, 350), 100, 50);
        renderer.drawLine(window, Point2D(300, 300), mousePos);
        window.display();
    }

    return 0;
}

