#include "Ennemi.h"
#include "SceneManager.h"
#include <iostream>	// Car on a un message console d'erreur


Ennemi::Ennemi(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world, int typeCote0, int typeCote1, int typeCote2, int typeCote3) : Static(_x, _y, _h, _l, textureName, textDictionnary, world) {
	addCote(0, typeCote0);
	addCote(1, typeCote1);
	addCote(2, typeCote2);
	addCote(3, typeCote3);
}

// M�thode Update qui regarde si le joueur touche les cot�s de l'ennemi et agit en cons�quence
void Ennemi::Update(SceneManager& sceneManager) {
	bool tue0 = cote[0]->Update(sceneManager);
	bool tue1 = cote[1]->Update(sceneManager);
	bool tue2 = cote[2]->Update(sceneManager);
	bool tue3 = cote[3]->Update(sceneManager);
	if (tue0 || tue1 || tue2 || tue3) {
		deleteFlag = true;	// si l'un des cot�s dit que l'ennemi doit mourrir, on active son drapeau
	}
}

// Selon la valeur de _type, on cr�e un CoteEnnemi de la classe d�riv�e correspondante
void Ennemi::addCote(int _cote, int _type) {
	switch (_type)
	{
	case 0:
		// Le cot� blesse le joueur quand touch�
		cote.push_back(std::make_unique<CoteEnnemi_Hurt>(_cote, this));
		break;
	case 1:
		// Le cot� tue l'ennemi quand touch�
		cote.push_back(std::make_unique<CoteEnnemi_Kill>(_cote, this));
		break;
	case 2:
		// Le cot� agis comme une plateforme
		cote.push_back(std::make_unique<CoteEnnemi_Plateforme>(_cote, this));
		break;
	default:
		// Erreur
		std::cerr << "Le type de cot� demand� n'existe pas ou n'a pas �t� impl�ment� dans Ennemi : " << _type << std::endl;
		break;
	}	
}

bool Ennemi::getDeleteFlag() {
	return deleteFlag;
}