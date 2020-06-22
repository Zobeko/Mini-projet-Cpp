#include "Clef.h"

using namespace std;

// Constructeur : associe une valeur et un sprite correspondant /!\ en l'�tat seules les pi�ces 1,5 et 10 ont un sprite
Clef::Clef(int _x, int _y, std::map<std::string, sf::Texture>& textDictionnary) : PickUp(_x, _y, 32, 32, "Clef.png", textDictionnary) {
}

// Comportement de la clef � chaque frame
void Clef::Update(SceneManager& sceneManager) {
	if (intersect(*sceneManager.getJoueur())) {
		sceneManager.unLockDoor();
		deleteFlag = true;
	}
}