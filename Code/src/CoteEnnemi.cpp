#include "CoteEnnemi.h"
#include "SceneManager.h"

#include <iostream>

CoteEnnemi::CoteEnnemi(int _cote, Ennemi* _owner) {
	cote = _cote;	
	owner = _owner;
}

// Regarde si le joueur "touche" l'ennemi
bool CoteEnnemi::CheckCollision(Joueur& j) {
	if (cote == 0) {
		//Cote haut
		bool hauteur = (owner->getY() - margeDetectDept < j.getY() - j.getH()) & (j.getY() - j.getH() < owner->getY() + margeDetectDept);
		bool gauche = owner->getX() < j.getDroite();
		bool droite = j.getGauche() < owner->getX() + owner->getL();
		return (hauteur & gauche & droite);
	}
	else if (cote == 1) {
		//Cote gauche
		bool haut = owner->getY() - margeDetectWidth > j.getY() - j.getH();
		bool bas = j.getY() > owner->getY() - owner->getH() + margeDetectWidth;
		bool gauche = (owner->getX()-margeDetectDept < j.getDroite()) && (j.getDroite() < owner->getX() + margeDetectDept);
		return (haut & bas & gauche);
	}
	else if (cote == 2) {
		//Cote Droit
		bool haut = owner->getY() - margeDetectWidth > j.getY() - j.getH();
		bool bas = j.getY() > owner->getY() - owner->getH() + margeDetectWidth;
		bool droite = (owner->getX() + owner->getL() - margeDetectDept < j.getGauche()) && (j.getGauche() < owner->getX() + owner->getL() + margeDetectDept);
		return (haut & bas & droite);
	}
	else if (cote == 3) {
		//Cote bas
		bool bas = (owner->getY() - owner->getH() - margeDetectDept < j.getY()) & (j.getY() < owner->getY() - owner->getH() + margeDetectDept);
		bool gauche = owner->getX() < j.getDroite();
		bool droite = j.getGauche() < owner->getX() + owner->getL();
		return (bas & gauche & droite);
	}

	//Securité, pas vraiment nécessaire car normalement on est dans un des cas précédents
	return false;
}
