#include "Piece.h"

#include "PickUp.h"
#include "SceneManager.h"

using namespace std;

// Constructeur : associe une valeur et un sprite correspondant /!\ en l'�tat seules les pi�ces 1,5 et 10 ont un sprite
Piece::Piece(int _x, int _y, int _value) : PickUp(_x, _y, 32, 32, "Piece" + std::to_string(_value) + ".png") {
	value = _value;
}



// (Override) Action � r�aliser lorsque le joueur touche la pi�ce : augmenter le compteur de SceneManager + detruire la pi�ce
void Piece::ActionOnIntersect(SceneManager& sceneManager, int iDpickUp) {
	sceneManager.nbPiece += value;
	sceneManager.RemovePickUp(iDpickUp);
}