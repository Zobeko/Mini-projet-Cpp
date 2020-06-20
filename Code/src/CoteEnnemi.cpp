#include "CoteEnnemi.h"
#include "SceneManager.h"

#include <iostream>

CoteEnnemi::CoteEnnemi(int _cote, Ennemi* _owner) {
	cote = _cote;	
	owner = _owner;
}

/*
// Méthode Update qui regarde si le joueur est en collision avec le coté
bool CoteEnnemi::Update(SceneManager& sceneManager) {
	if (CheckCollision(*sceneManager.getJoueur())) {
		if (type == 0) {
			sceneManager.setDeathFlagTrue();
		}
		else if (type == 1) {
			return true;	// l'ennemi est à tuer
		}
		else if (type == 2) {
			if (cote == 0) {
				// c'est le dessus
				sceneManager.getJoueur()->SetGroundedFlag(true);
			}
			else if (cote == 1 || cote == 2) {
				// c'est un coté vertical
				sceneManager.getJoueur()->SetWalledFlag(true);
			}
			//Sinon c'est une erreur ou le coté du bas -> on fais rien
		}
	}
	return false;
}*/

// Regarde si le joueur "touche" l'ennemi
bool CoteEnnemi::CheckCollision(Joueur& j) {

	int marge = owner->margeDetect;
	if (cote == 0) {
		//Cote haut
		bool hauteur = (owner->getY() - marge < j.getY() - j.getH()) & (j.getY() - j.getH() < owner->getY() + marge);
		bool gauche = owner->getX() < j.getX() + j.getL();
		bool droite = j.getX()  < owner->getX() + owner->getL();
		return (hauteur & gauche & droite);
	}
	else if (cote == 1) {
		//Cote gauche
		bool haut = owner->getY() > j.getY() - j.getH();
		bool bas = j.getY() > owner->getY() - owner->getH();
		bool gauche = (owner->getX()-marge < j.getX() + j.getL()) && (j.getX() + j.getL() < owner->getX() + marge);
		return (haut & bas & gauche);
	}
	else if (cote == 2) {
		//Cote Droit
		bool haut = owner->getY() > j.getY() - j.getH();
		bool bas = j.getY() > owner->getY() - owner->getH();
		bool droite = (owner->getX() + owner->getL() - marge < j.getX()) && (j.getX() < owner->getX() + owner->getL() + marge);
		return (haut & bas & droite);
	}
	else if (cote == 3) {
		//Cote bas
		bool bas = (owner->getY() - owner->getH() - marge < j.getY()) & (j.getY() < owner->getY() - owner->getH() + marge);
		bool gauche = owner->getX() < j.getX() + j.getL();
		bool droite = j.getX() < owner->getX() + owner->getL();
		return (bas & gauche & droite);
	}

	//Securité, pas vraiment nécessaire car normalement on est dans un des cas précédents
	return false;
}
