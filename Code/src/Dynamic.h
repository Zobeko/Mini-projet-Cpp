#pragma once

#include "UnitePhysic.h"

class Dynamic : public UnitePhysic
{
public : 
	Dynamic(int _x, int _y, int _h, int _l, std::string textureName);
	void setVelocityXY(int speedX, int speedY);

private:


};