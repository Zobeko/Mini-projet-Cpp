#pragma once

#include "SceneManager.h"
#include "Unite.h"
#include "PickUp.h"


class Piece : public PickUp
{
public:
	Piece(int _x, int _y, int _value);

private:
	int value;
	void ActionOnIntersect(SceneManager& sceneManager, int iDpickUp) override;
};