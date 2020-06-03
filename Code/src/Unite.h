#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

class Unite
{
public:
	virtual ~Unite() = default;
	Unite(int _x, int _y, int _h, int _l, string textureName);
	Unite();
	int getX();
	int getY();
	int getH();
	int getL();
	virtual void setXY(int _x, int _y);
	void setSprite(int _h, int _l, string textureName);
	void draw();

private:
	int x;
	int y;
	int h;
	int l;
	sf::Sprite sprite;
};