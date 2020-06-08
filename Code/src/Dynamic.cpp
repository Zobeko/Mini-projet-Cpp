#include "Dynamic.h"

//Pour les tests, a enlever apres
#include <iostream>



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

	//box->ApplyForce(b2Vec2(speedX*50000, 50000*speedY), box->GetWorldCenter(), true);

	//box->ApplyLinearImpulse(b2Vec2(speedX, speedY), box->GetWorldCenter(), true);
	//box->SetTransform(b2Vec2(box->GetPosition().x + 2*box->GetLinearVelocity().x, box->GetPosition().y + box->GetLinearVelocity().y), 0);


	/*float x = box->GetPosition().x;
	float y = box->GetPosition().y;

	box->SetTransform(b2Vec2(x + speedX, y + speedY), 0);*/

	std::cout << "Vitesse : (" << getBox()->GetLinearVelocity().x << ", " << getBox()->GetLinearVelocity().y << ")" << std::endl;
	
}

int Dynamic::getVelocityX() {

	b2Vec2 vel = getBox()->GetLinearVelocity();
	return vel.x;
}

int Dynamic::getVelocityY() {

	b2Vec2 vel = getBox()->GetLinearVelocity();
	return vel.y;
}


void Dynamic::update() {

	Unite::setXY(getBox()->GetPosition().x - getL()/2, getBox()->GetPosition().y + getH() / 2);
}