#pragma once
#include "SceneManager.h"
#include "Unite.h"

class PickUp : public Unite
{
public:
	PickUp(int _x, int _y, int _h, int _l, std::string textureName);
	virtual bool intersect(Unite & _unite);
	void Update(SceneManager & sceneManager, int iDpickUp);

private:
	virtual void ActionOnIntersect(SceneManager& sceneManager, int iDpickUp);
};