#pragma once

#include "Static.h"
#include "CoteEnnemi.h"
#include "CoteEnnemi_Hurt.h"
#include "CoteEnnemi_kill.h"
#include "CoteEnnemi_Plateforme.h"
class SceneManager;


// Classe des ennemis. Il possède 4 cotés qui sont dans des classes
// séparées en accord avec le Programming Pattern Stratégie
class Ennemi : public Static
{
public:
	Ennemi(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world, int typeCote0, int typeCote1, int typeCote2, int typeCote3);
	void Update(SceneManager& sceneManager);	// Regarde la collision entre le joueur et chacun des cotés, et agit en conséquence
	bool getDeleteFlag();						// Renvoie le drapeau de destruction

private:
	std::vector<std::unique_ptr<CoteEnnemi>> cote;	// Les 4 cotés de l'ennemi
	void addCote(int _cote, int _type);				// Ajout un coté de la bonne sous-classe en fonction de _type
	bool deleteFlag = false;						// Drapeau de destruction de l'ennemi
};

