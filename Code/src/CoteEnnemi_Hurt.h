#pragma once

#include "Joueur.h"
#include "CoteEnnemi.h"
class Ennemi;	//Permet d'avoir l'owner 

// Classe désignant un des4 cotés d'un ennemi
// Permet d'implémenter le design Pattern Stratégie
// Lorsue le joueur est au contact d'un coté, selon son type
	// cela tue le joueur, tue l'ennemi ou le coté agit comme une plateforme (dont on peut sauter)
class CoteEnnemi_Hurt : public CoteEnnemi
{
public:
	CoteEnnemi_Hurt(int _cote, Ennemi* _owner);
	bool Update(SceneManager& sceneManager) override;
};

