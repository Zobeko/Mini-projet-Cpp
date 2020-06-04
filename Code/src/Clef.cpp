#include "Clef.h"

#include "PickUp.h"
#include "SceneManager.h"

using namespace std;

// Constructeur : associe une valeur et un sprite correspondant /!\ en l'�tat seules les pi�ces 1,5 et 10 ont un sprite
Clef::Clef(int _x, int _y) : PickUp(_x, _y, 32, 32, "Clef.png") {
}



// (Override) Action � r�aliser lorsque le joueur touche la clef : d�bloquer la salle + detruire la pi�ce
void Clef::ActionOnIntersect(SceneManager& sceneManager, int iDpickUp) {
	sceneManager.unlockDoor();
	sceneManager.RemovePickUp(iDpickUp);
}
