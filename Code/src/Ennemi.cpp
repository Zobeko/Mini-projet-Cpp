#include "Ennemi.h"

Ennemi::Ennemi(int _x, int _y, int _h, int _l, std::string textureName, bool _mortel) : Static(_x, _y, _h, _l, textureName) {
	_mortel = mortel;
}

void Ennemi::Update(SceneManager& sceneManager, int idEnnemi) {
	Joueur j = sceneManager.getJoueur();
	//if collision
	if (false)
	{
		if (mortel) {
			//test sur la hauteur
			if (j.getY() > getY() + 0.95 * getH()) {
				//le joueur est au dessus : il faut tuer l'ennemi
				sceneManager.RemoveEnnemi(idEnnemi);
			}
			else {
				// le joueur n'est pas au-dessus : il doit mourrir
				sceneManager.tuerJoueur();
			}
		}
		else {
			//tuer le joueur:
			sceneManager.tuerJoueur();
		}
	}
}
