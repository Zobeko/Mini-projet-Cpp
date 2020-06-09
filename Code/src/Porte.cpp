#include "Porte.h"

#include "PickUp.h"
#include "SceneManager.h"

using namespace std;

// Constructeur : associe une valeur et un sprite correspondant /!\ en l'état seules les pièces 1,5 et 10 ont un sprite
Porte::Porte(int _x, int _y, std::map<std::string, sf::Texture>& textDictionnary) : PickUp(_x, _y, 32, 32, "Porte.png", textDictionnary) {
}


/*
// (Override) Action à réaliser lorsque le joueur touche la clef : débloquer la salle + detruire la pièce
// remarque : ici le iDpickUp ne sert à rien mais on le garde de l'hérite de l'override
void Porte::ActionOnIntersect(SceneManager& sceneManager, int iDpickUp) {
	//On regarde si la porte est déverrouillée
	if (sceneManager.getClefRecupere()) {
		sceneManager.chargerSalleSuivante();
	}
}
*/
void Porte::Update(SceneManager& sceneManager, int iDpickUp) {
	if (intersect(*sceneManager.getJoueur())) {
		if (sceneManager.getClefRecupere()) {
			sceneManager.setLevelFlagTrue();
		}
	}
}