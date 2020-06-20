#pragma once

#include "Static.h"
#include "Joueur.h"
#include "CoteEnnemi.h"
#include "CoteEnnemi_Hurt.h"
#include "CoteEnnemi_kill.h"
#include "CoteEnnemi_Plateforme.h"
class SceneManager;


// Classe des ennemis. Il poss�de 4 cot�s qui sont dans des classes
// s�par�es en accorda avec le Programming Pattern Strat�gie
class Ennemi : public Static
{
public:
	Ennemi(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world, int typeCote0, int typeCote1, int typeCote2, int typeCote3);
	void Update(SceneManager& sceneManager, int idEnnemi);	// Regarde la collision entre le joueur et chacun des cot�s, et agit en cons�quence
	int margeDetect = 5;									// Marge de Detection, car avec les boites on peut avoir un peu de jeu

private:
	// Les 4 cot�s de l'ennemi : 
	std::vector<std::unique_ptr<CoteEnnemi>> cote;
	/*std::unique_ptr<CoteEnnemi> cote0;
	std::unique_ptr<CoteEnnemi> cote1;
	std::unique_ptr<CoteEnnemi> cote2;
	std::unique_ptr<CoteEnnemi> cote3;*/
	void addCote(int _cote, int _type);
};

