#include "Ennemi.h"
#include "SceneManager.h"


Ennemi::Ennemi(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world, int typeCote0, int typeCote1, int typeCote2, int typeCote3) : Static(_x, _y, _h, _l, textureName, textDictionnary, world) {
	cote0 = std::make_unique<CoteEnnemi>(0, typeCote0, this);
	cote1 = std::make_unique<CoteEnnemi>(1, typeCote1, this);;
	cote2 = std::make_unique<CoteEnnemi>(2, typeCote2, this);;
	cote3 = std::make_unique<CoteEnnemi>(3, typeCote3, this);;
}

// Méthode Update qui regarde si le joueur touche les cotés de l'ennemi et agit en conséquence
void Ennemi::Update(SceneManager& sceneManager, int idEnnemi) {
	bool tue0 = cote0->Update(sceneManager);
	bool tue1 = cote1->Update(sceneManager);
	bool tue2 = cote2->Update(sceneManager);
	bool tue3 = cote3->Update(sceneManager);
	if (tue0 || tue1 || tue2 || tue3) {
		// C'est que l'ennemi a été tué par le joueur
		sceneManager.RemoveEnnemi(idEnnemi);
	}
}
