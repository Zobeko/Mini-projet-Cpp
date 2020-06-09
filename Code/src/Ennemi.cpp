#include "Ennemi.h"
#include "SceneManager.h"

#include <iostream>

Ennemi::Ennemi(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world, int typeCote0, int typeCote1, int typeCote2, int typeCote3) : Static(_x, _y, _h, _l, textureName, textDictionnary, world) {
	cote0 = std::make_unique<CoteEnnemi>(0, typeCote0, this);
	cote1 = std::make_unique<CoteEnnemi>(1, typeCote1, this);;
	cote2 = std::make_unique<CoteEnnemi>(2, typeCote2, this);;
	cote3 = std::make_unique<CoteEnnemi>(3, typeCote3, this);;
}

// Méthode Update qui regarde si le joueur est en collision avec l'ennemi en question (this)
// Malgrès une similitude d'utilisation, elle n'est pas hérité de Static car a des arguments différents,
// un comportement différent, et est appelée à un autre endroit
void Ennemi::Update(SceneManager& sceneManager, int idEnnemi) {
	/*if (CheckCollision(*sceneManager.getJoueur())) {
		OnCollisionAction(sceneManager, idEnnemi);
	}*/

	// On est obligé de les stocker dans des variables locales sinon si l'ennemi meurt le reste n'est pas check
		// En meme si temps si l'ennemi meurt il y a pas besoin de check les autres normalement
	bool tue0 = cote0->Update(sceneManager);
	bool tue1 = cote1->Update(sceneManager);
	bool tue2 = cote2->Update(sceneManager);
	bool tue3 = cote3->Update(sceneManager);
	if (tue0 || tue1 || tue2 || tue3) {
		// C'est que l'ennemi a été tué par le joueur
		sceneManager.RemoveEnnemi(idEnnemi);
	}
}

/*
// Regarde si le joueur "touche" l'ennemi
bool Ennemi::CheckCollision(Joueur& j) {
	bool uniteInterDessus = (getY() - margeDetect < j.getY() + j.getH()) & (getY() + getH() + margeDetect > j.getY());
	// est-ce qu'il y a correspondance par le dessous (unite plus bas que this)
	bool uniteInterDessous = (j.getY() < getY() + getH() + margeDetect) & (j.getY() + j.getH() > getY() - margeDetect);

	if (uniteInterDessus || uniteInterDessous) {
		//hauteur : ok => intersection possible => test sur la longueur :
			// est-ce qu'il y a correspondance par la droite (unite plus à droite que this)
		bool uniteInterDroite = (getX() - margeDetect < j.getX() + j.getL()) & (getX() + getL() + margeDetect > j.getX());
		// est-ce qu'il y a correspondance par le dessous (unite plus bas que this)
		bool uniteInterDessous = (j.getX() < getX() + getL() + margeDetect) & (j.getX() + j.getL() > getX() - margeDetect);

		if (uniteInterDroite || uniteInterDessous) {
			// Il y a bien intersection => on renvoie true (on aurait pu renvoyé directement uniteInterDroite || uniteInterDessous mais c'est plus clair
			return true;
		}
	}
	return false;
}

void Ennemi::OnCollisionAction(SceneManager& sceneManager, int idEnnemi) {
	if (mortel) {
		//test sur la hauteur
		if (sceneManager.getJoueur()->getY() > getY() + 0.95 * getH()) {
			//le joueur est au dessus : il faut tuer l'ennemi
			sceneManager.RemoveEnnemi(idEnnemi);
		}
		else {
			// le joueur n'est pas au-dessus : il doit mourrir
			sceneManager.setDeathFlagTrue();
		}
	}
	else {
		//tuer le joueur:
		sceneManager.setDeathFlagTrue();
	}
}
*/