#pragma once

#include "Joueur.h"

//#include "SceneManager.h"
class Ennemi;

class CoteEnnemi
{
public:
	CoteEnnemi(int _cote, int _type, Ennemi* _owner);
	bool Update(SceneManager& sceneManager);

protected:
	bool CheckCollision(Joueur& j);

private:
	int cote;
	int type;
	Ennemi* owner;
};

