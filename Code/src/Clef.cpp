#include "Clef.h"

#include "PickUp.h"
#include "SceneManager.h"

using namespace std;

// Constructeur : associe une valeur et un sprite correspondant /!\ en l'état seules les pièces 1,5 et 10 ont un sprite
Clef::Clef(int _x, int _y, std::map<std::string, sf::Texture>& textDictionnary) : PickUp(_x, _y, 32, 32, "Clef.png", textDictionnary) {
}


/*
// (Override) Action à réaliser lorsque le joueur touche la clef : débloquer la salle + detruire la pièce
void Clef::ActionOnIntersect(SceneManager& sceneManager, int iDpickUp) {
	sceneManager.unLockDoor();
	sceneManager.RemovePickUp(iDpickUp);
}
*/
void Clef::Update(SceneManager& sceneManager, int iDpickUp) {
	if (intersect(*sceneManager.getJoueur())) {
		sceneManager.unLockDoor();
		sceneManager.RemovePickUp(iDpickUp);
	}
}