#pragma once

#include "PickUp.h"
#include "SceneManager.h"


class Clef : public PickUp
{
public:
	Clef(int _x, int _y, std::map<std::string, sf::Texture>& textDictionnary);
	void Update(SceneManager& sceneManager, int iDpickUp) override;

private:
};