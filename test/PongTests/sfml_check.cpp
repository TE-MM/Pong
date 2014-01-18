#include <SFML/Graphics.hpp>
#define BOOST_TEST_MODULE SFMLCheck
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(SFMLWorks) {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    window.clear();
    window.draw(shape);
    window.display();
}
