#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

#include "SceneManager.h"
#include "Unite.h"

class PickUp : Unite
{
public:
	PickUp(int _x, int _y, int _h, int _l, string textureName);
	bool intersect(Unite* _unite);
	void Update(SceneManager & sceneManager);

private:

};