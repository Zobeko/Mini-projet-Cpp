#include "Dynamic.h"


Dynamic::Dynamic(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world) : UnitePhysic(_x, _y, _h, _l, textureName, textDictionnary, b2_dynamicBody, world)
{
}

void Dynamic::setVelocityXY(int speedX, int speedY) {
	//Modifie la vitesse de déplacement de la boite de collision
	b2Body* box = getBox();
	b2Vec2 vel = getBox()->GetLinearVelocity();
	vel.x = speedX;
	vel.y = speedY;
	getBox()->SetLinearVelocity(vel);
}

int Dynamic::getVelocityX() {
	b2Vec2 vel = getBox()->GetLinearVelocity();
	return vel.x;
}

int Dynamic::getVelocityY() {
	b2Vec2 vel = getBox()->GetLinearVelocity();
	return vel.y;
}

// A chaque instant on replace l'unite là où se situe sa boite de collision en faisant la conversion des échelles
void Dynamic::update() {
	Unite::setXY((getBox()->GetPosition().x*10.f - getL()/2), (getBox()->GetPosition().y*10.f + getH() / 2));
}