#pragma once

#include "Static.h"

#include "SceneManager.h"

class Ennemi : public Static
{
public:
	Ennemi(int _x, int _y, int _h, int _l, std::string textureName, bool _mortel);
	void Update(SceneManager& sceneManager, int idEnnemi);

private:
	bool mortel;
};

