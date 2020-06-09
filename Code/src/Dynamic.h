#pragma once

#include "UnitePhysic.h"


//Classe Mère de toutes les Unités possèdant un corps dynamique
class Dynamic : public UnitePhysic
{
public : 
	Dynamic(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world);
	virtual ~Dynamic() = default;
	void setVelocityXY(int speedX, int speedY);		// Donne une vitesse précise au body de dynamique
	int getVelocityX();								// Recupère la vitesse sur x du body
	int getVelocityY();								// Recupère la vitesse sur x du body
	void update();									// Met à jour la position de l'unite et de son sprite en fonction de la position du dynamicBody
};