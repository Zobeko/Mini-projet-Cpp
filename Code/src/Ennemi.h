#pragma once

#include "Static.h"

//#include "SceneManager.h"
class SceneManager;

class Ennemi : public Static
{
public:
	Ennemi(int _x, int _y, int _h, int _l, std::string textureName, bool _mortel);
	void Update(SceneManager& sceneManager, int idEnnemi);
	void SetCollisionFlagOn();

private:
	bool mortel;
	bool collisionFlag;		// Sert à savoir si il y a eu collision avec le joueur pour la traiter dans l'update
};

