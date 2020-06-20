#pragma once

#include "Joueur.h"
#include "CoteEnnemi.h"
class Ennemi;	//Permet d'avoir l'owner 

// Classe d�signant un des4 cot�s d'un ennemi
// Permet d'impl�menter le design Pattern Strat�gie
// Lorsue le joueur est au contact d'un cot�, selon son type
	// cela tue le joueur, tue l'ennemi ou le cot� agit comme une plateforme (dont on peut sauter)
class CoteEnnemi_Hurt : public CoteEnnemi
{
public:
	CoteEnnemi_Hurt(int _cote, Ennemi* _owner);
	bool Update(SceneManager& sceneManager) override;
};

