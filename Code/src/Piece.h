#pragma once

#include "SceneManager.h"
#include "Unite.h"
#include "PickUp.h"


class Piece : public PickUp
{
public:
	Piece(int _x, int _y, std::map<std::string, sf::Texture>& textDictionnary, int _value);
	void Update(SceneManager& sceneManager, int iDpickUp) override;

private:
	int value;
};