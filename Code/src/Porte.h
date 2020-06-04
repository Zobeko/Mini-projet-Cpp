#pragma once

#include "PickUp.h"
#include "SceneManager.h"


class Porte : public PickUp
{
public:
	Porte(int _x, int _y);

private:
	void ActionOnIntersect(SceneManager& sceneManager, int iDpickUp) override;
};