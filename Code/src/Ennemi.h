#pragma once

#include "Static.h"
#include "CoteEnnemi.h"
#include "CoteEnnemi_Hurt.h"
#include "CoteEnnemi_kill.h"
#include "CoteEnnemi_Plateforme.h"
class SceneManager;


// Classe des ennemis. Il poss�de 4 cot�s qui sont dans des classes
// s�par�es en accord avec le Programming Pattern Strat�gie
class Ennemi : public Static
{
public:
	Ennemi(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world, int typeCote0, int typeCote1, int typeCote2, int typeCote3);
	void Update(SceneManager& sceneManager);	// Regarde la collision entre le joueur et chacun des cot�s, et agit en cons�quence
	bool getDeleteFlag();						// Renvoie le drapeau de destruction

private:
	std::vector<std::unique_ptr<CoteEnnemi>> cote;	// Les 4 cot�s de l'ennemi
	void addCote(int _cote, int _type);				// Ajout un cot� de la bonne sous-classe en fonction de _type
	bool deleteFlag = false;						// Drapeau de destruction de l'ennemi
};

