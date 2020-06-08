#pragma once
#include <vector>
#include <Unite.h>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class UnitePhysic : public Unite
{
public:
	virtual ~UnitePhysic() = default;
	UnitePhysic(float _x, float _y, float _h, float _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2BodyType bodyType, b2World &world);
	b2Body* getBox();
	void setXY(int _x, int _y) override;

private:
	b2Body* box;
};