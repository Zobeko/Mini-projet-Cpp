#include "Dynamic.h"

Dynamic::Dynamic(int _x, int _y, int _h, int _l, std::string textureName) : UnitePhysic(_x, _y, _h, _l, textureName, b2_dynamicBody) {
}



void Dynamic::setVelocityXY(int speedX, int speedY) {
	b2Body* box = getBox();
	b2Vec2 vel = box->GetLinearVelocity();
	vel.x = speedX;
	vel.y = speedY;
	box->SetLinearVelocity(vel);
}


//Manque update()