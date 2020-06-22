#include "CoteEnnemi_Kill.h"
#include "SceneManager.h"

CoteEnnemi_Kill::CoteEnnemi_Kill(int _cote, Ennemi* _owner) : CoteEnnemi(_cote, _owner){
}

// M�thode Update qui regarde si le joueur est en collision avec le cot�
bool CoteEnnemi_Kill::Update(SceneManager& sceneManager) {
	if (CheckCollision(*sceneManager.getJoueur()))
		return true;	// l'ennemi est � tuer
	return false;
}