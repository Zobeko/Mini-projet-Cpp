#include "CoteEnnemi_Plateforme.h"
#include "SceneManager.h"

CoteEnnemi_Plateforme::CoteEnnemi_Plateforme(int _cote, Ennemi* _owner) : CoteEnnemi(_cote, _owner){
}

// M�thode Update qui regarde si le joueur est en collision avec le cot�
bool CoteEnnemi_Plateforme::Update(SceneManager& sceneManager) {
	if (CheckCollision(*sceneManager.getJoueur()))
		if (cote == 0) {
			// c'est le dessus
			sceneManager.getJoueur()->SetGroundedFlag(true);
		}
		else if (cote == 1) {
			// c'est un cot� vertical
			sceneManager.getJoueur()->SetWalledFlag(sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
		}
		else if (cote == 2) {
			// c'est un cot� vertical
			sceneManager.getJoueur()->SetWalledFlag(sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
		}
	//Sinon c'est une erreur ou le cot� du bas -> on fais rien
	return false;
}