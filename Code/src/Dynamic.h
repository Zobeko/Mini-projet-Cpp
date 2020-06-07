#pragma once

#include "UnitePhysic.h"

class Dynamic : public UnitePhysic
{
public : 
	Dynamic(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world);
	void setVelocityXY(int speedX, int speedY);
	int getVelocityX();
	int getVelocityY();
	void update();

private:


};