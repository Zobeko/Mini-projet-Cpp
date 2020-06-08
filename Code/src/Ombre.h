#pragma once
#include "SceneManager.h"
#include "Unite.h"
#include "PickUp.h"

class Ombre : public PickUp
{
public:
	Ombre(int _x, int _y, int _h, std::map<std::string, sf::Texture>& textDictionnary);
	bool intersect(Unite & _unite) override;

private:
	//void ActionOnIntersect(SceneManager& sceneManager, int iDpickUp) override; 
};

