#pragma once

#include "Static.h"
#include "Joueur.h"
#include "CoteEnnemi.h"
#include "CoteEnnemi_Hurt.h"
#include "CoteEnnemi_kill.h"
#include "CoteEnnemi_Plateforme.h"
class SceneManager;


// Classe des ennemis. Il possède 4 cotés qui sont dans des classes
// séparées en accorda avec le Programming Pattern Stratégie
class Ennemi : public Static
{
public:
	Ennemi(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world, int typeCote0, int typeCote1, int typeCote2, int typeCote3);
	void Update(SceneManager& sceneManager, int idEnnemi);	// Regarde la collision entre le joueur et chacun des cotés, et agit en conséquence
	int margeDetect = 5;									// Marge de Detection, car avec les boites on peut avoir un peu de jeu

private:
	// Les 4 cotés de l'ennemi : 
	std::vector<std::unique_ptr<CoteEnnemi>> cote;
	/*std::unique_ptr<CoteEnnemi> cote0;
	std::unique_ptr<CoteEnnemi> cote1;
	std::unique_ptr<CoteEnnemi> cote2;
	std::unique_ptr<CoteEnnemi> cote3;*/
	void addCote(int _cote, int _type);
};

