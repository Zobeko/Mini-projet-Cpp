#include "Clef.h"

#include "PickUp.h"
#include "SceneManager.h"

using namespace std;

// Constructeur : associe une valeur et un sprite correspondant /!\ en l'état seules les pièces 1,5 et 10 ont un sprite
Clef::Clef(int _x, int _y) : PickUp(_x, _y, 32, 32, "Clef.png") {
}



// (Override) Action à réaliser lorsque le joueur touche la clef : débloquer la salle + detruire la pièce
void Clef::ActionOnIntersect(SceneManager& sceneManager, int iDpickUp) {
	sceneManager.unlockDoor();
	sceneManager.RemovePickUp(iDpickUp);
}
