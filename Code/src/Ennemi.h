#pragma once

#include "Static.h"
#include "Joueur.h"
//#include "SceneManager.h"
class SceneManager;

class Ennemi : public Static
{
public:
	Ennemi(int _x, int _y, int _h, int _l, std::string textureName, bool _mortel, b2World& world);
	void Update(SceneManager& sceneManager, int idEnnemi);

protected:
	bool CheckCollision(Joueur& j);

private:
	void OnCollisionAction(SceneManager& sceneManager, int idEnnemi);
	bool mortel;
};

