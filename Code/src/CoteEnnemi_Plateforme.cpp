#include "CoteEnnemi_Plateforme.h"
#include "SceneManager.h"

#include <iostream>

CoteEnnemi_Plateforme::CoteEnnemi_Plateforme(int _cote, Ennemi* _owner) : CoteEnnemi(_cote, _owner){
}

// Méthode Update qui regarde si le joueur est en collision avec le coté
bool CoteEnnemi_Plateforme::Update(SceneManager& sceneManager) {
	if (CheckCollision(*sceneManager.getJoueur()))
		if (cote == 0) {
			// c'est le dessus
			sceneManager.getJoueur()->SetGroundedFlag(true);
		}
		else if (cote == 1 || cote == 2) {
			// c'est un coté vertical
			sceneManager.getJoueur()->SetWalledFlag(true);
		}
	//Sinon c'est une erreur ou le coté du bas -> on fais rien
	return false;
}