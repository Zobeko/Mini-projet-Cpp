#pragma once

#include "PickUp.h"
#include "SceneManager.h"


class Porte : public PickUp
{
public:
	Porte(int _x, int _y, std::map<std::string, sf::Texture>& textDictionnary);

private:
	//void ActionOnIntersect(SceneManager& sceneManager, int iDpickUp) override;
};