#include "CoteEnnemi_Hurt.h"
#include "SceneManager.h"

#include <iostream>

CoteEnnemi_Hurt::CoteEnnemi_Hurt(int _cote, Ennemi* _owner) : CoteEnnemi(_cote, _owner){
}

// M�thode Update qui regarde si le joueur est en collision avec le cot�
bool CoteEnnemi_Hurt::Update(SceneManager& sceneManager) {
	if (CheckCollision(*sceneManager.getJoueur()))
		sceneManager.setDeathFlagTrue();
	return false;
}