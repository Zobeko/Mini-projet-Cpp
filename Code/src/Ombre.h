#pragma once
#include "SceneManager.h"
#include "Unite.h"
#include "PickUp.h"

class Ombre : PickUp
{
public:
	Ombre(int _x, int _y, int _h);
	bool intersect(Unite & _unite) override;

private:
	void ActionOnIntersect(SceneManager& sceneManager, int iDpickUp) override; 
};

