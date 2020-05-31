#include <SFML/Graphics.hpp>

sf::RectangleShape PB_Rect(int _posX, int _posY, int _width, int _height) {
	sf::RectangleShape rect(sf::Vector2f(_width,_height));
	rect.setPosition(_posX,_posY);
	rect.setFillColor(sf::Color::Red);
	return rect;
}