#pragma once

#include "Static.h"
#include "Joueur.h"
#include "CoteEnnemi.h"
//#include "SceneManager.h"
class SceneManager;

class Ennemi : public Static
{
public:
	Ennemi(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world, int typeCote0, int typeCote1, int typeCote2, int typeCote3);
	void Update(SceneManager& sceneManager, int idEnnemi);
	int margeDetect = 5;

private:
	std::unique_ptr<CoteEnnemi> cote0;
	std::unique_ptr<CoteEnnemi> cote1;
	std::unique_ptr<CoteEnnemi> cote2;
	std::unique_ptr<CoteEnnemi> cote3;
};

