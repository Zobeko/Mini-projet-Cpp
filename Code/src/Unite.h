#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

class Unite
{
public:
	virtual ~Unite() = default;
	Unite(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary);
	int getX();
	int getY();
	int getH();
	int getL();
	sf::Sprite& getSprite();
	virtual void setXY(int _x, int _y);
	void setSprite(int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary);
	void draw(sf::RenderWindow & window);

private:
	int x;
	int y;
	int h;
	int l;
	sf::Sprite sprite;
};