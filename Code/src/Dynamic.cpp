#include "Dynamic.h"



Dynamic::Dynamic(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world) : UnitePhysic(_x, _y, _h, _l, textureName, textDictionnary, b2_dynamicBody, world)
{
}

void Dynamic::setVelocityXY(int speedX, int speedY) {

	//Modifie la vitesse de déplacement de la boite de collision
	b2Body* box = getBox();
	b2Vec2 vel = box->GetLinearVelocity();
	vel.x = speedX;
	vel.y = speedY;
	box->SetLinearVelocity(vel);
	
}

int Dynamic::getVelocityX() {
	b2Body* box = getBox();
	b2Vec2 vel = box->GetLinearVelocity();
	return vel.x;
}

int Dynamic::getVelocityY() {
	b2Body* box = getBox();
	b2Vec2 vel = box->GetLinearVelocity();
	return vel.y;
}


void Dynamic::update() {

	Unite::setXY(getBox()->GetPosition().x, getBox()->GetPosition().y);
}