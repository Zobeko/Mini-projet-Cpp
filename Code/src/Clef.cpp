#include "Clef.h"

#include "PickUp.h"
#include "SceneManager.h"

using namespace std;

// Constructeur : associe une valeur et un sprite correspondant /!\ en l'état seules les pièces 1,5 et 10 ont un sprite
Clef::Clef(int _x, int _y, std::map<std::string, sf::Texture>& textDictionnary) : PickUp(_x, _y, 32, 32, "Clef.png", textDictionnary) {
}

// Comportement de la clef à chaque frame
void Clef::Update(SceneManager& sceneManager, int iDpickUp) {
	if (intersect(*sceneManager.getJoueur())) {
		sceneManager.unLockDoor();
		sceneManager.RemovePickUp(iDpickUp);
	}
}