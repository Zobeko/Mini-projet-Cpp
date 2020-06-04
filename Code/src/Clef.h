#pragma once

#include "PickUp.h"
#include "SceneManager.h"


class Clef : public PickUp
{
public:
	Clef(int _x, int _y);

private:
	void ActionOnIntersect(SceneManager& sceneManager, int iDpickUp) override;
};