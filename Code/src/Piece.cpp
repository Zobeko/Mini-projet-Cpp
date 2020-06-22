#include "Piece.h"

using namespace std;

// Constructeur : associe une valeur et un sprite correspondant /!\ en l'�tat seules les pi�ces 1, 5 et 10 ont un sprite
Piece::Piece(int _x, int _y, std::map<std::string, sf::Texture>& textDictionnary, int _value) : PickUp(_x, _y, 32, 32, "Piece" + std::to_string(_value) + ".png", textDictionnary) {
	value = _value;
}



// (Override) Action � r�aliser lorsque le joueur touche la pi�ce : augmenter le compteur de SceneManager + detruire la pi�ce
void Piece::Update(SceneManager& sceneManager) {
	if (intersect(*sceneManager.getJoueur())) {
		sceneManager.nbPiece += value;
		deleteFlag = true;
	}	
}