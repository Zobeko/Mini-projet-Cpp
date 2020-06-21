#include "Ennemi.h"
#include "SceneManager.h"
#include <iostream>


Ennemi::Ennemi(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world, int typeCote0, int typeCote1, int typeCote2, int typeCote3) : Static(_x, _y, _h, _l, textureName, textDictionnary, world) {
	/*cote0 = std::make_unique<CoteEnnemi>(0, typeCote0, this);
	cote1 = std::make_unique<CoteEnnemi>(1, typeCote1, this);
	cote2 = std::make_unique<CoteEnnemi>(2, typeCote2, this);
	cote3 = std::make_unique<CoteEnnemi>(3, typeCote3, this);*/
	addCote(0, typeCote0);
	addCote(1, typeCote1);
	addCote(2, typeCote2);
	addCote(3, typeCote3);
}

// Méthode Update qui regarde si le joueur touche les cotés de l'ennemi et agit en conséquence
void Ennemi::Update(SceneManager& sceneManager) {
	bool tue0 = cote[0]->Update(sceneManager);
	bool tue1 = cote[1]->Update(sceneManager);
	bool tue2 = cote[2]->Update(sceneManager);
	bool tue3 = cote[3]->Update(sceneManager);
	if (tue0 || tue1 || tue2 || tue3) {
		deleteFlag = true;
	}
}

void Ennemi::addCote(int _cote, int _type) {
	switch (_type)
	{
	case 0:
		// Le coté blesse le joueur quand touché
		std::cout << _type << std::endl;
		cote.push_back(std::make_unique<CoteEnnemi_Hurt>(_cote, this));
		break;
	case 1:
		// Le coté tue l'ennemi quand touché
		std::cout << _type << std::endl;
		cote.push_back(std::make_unique<CoteEnnemi_Kill>(_cote, this));
		break;
	case 2:
		// Le coté agis comme une plateforme
		std::cout << _type << std::endl;
		cote.push_back(std::make_unique<CoteEnnemi_Plateforme>(_cote, this));
		break;
	default:
		// Erreur
		std::cerr << "Le type de coté demandé n'existe pas ou n'a pas été implémenté dans Ennemi : " << _type << std::endl;
		break;
	}	
}

bool Ennemi::getDeleteFlag() {
	return deleteFlag;
}