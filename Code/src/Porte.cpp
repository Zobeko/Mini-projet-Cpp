#include "Porte.h"

using namespace std;

// Constructeur : associe une valeur et un sprite correspondant /!\ en l'état seules les pièces 1,5 et 10 ont un sprite
Porte::Porte(int _x, int _y, std::map<std::string, sf::Texture>& textDictionnary) : PickUp(_x, _y, 32, 32, "Porte.png", textDictionnary) {
}


// Lorsqu'il y a contact, on vérifie si la clef a été récupérée et si on oui on met le drapeau pour changer de salle
void Porte::Update(SceneManager& sceneManager) {
	if (intersect(*sceneManager.getJoueur())) {
		if (sceneManager.getClefRecupere()) {
			sceneManager.setLevelFlagTrue();
		}
	}
}