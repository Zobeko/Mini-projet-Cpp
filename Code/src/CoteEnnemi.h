#pragma once

#include "Joueur.h"
class Ennemi;	//Permet d'avoir l'owner 

// Classe désignant un des4 cotés d'un ennemi
// Permet d'implémenter le design Pattern Stratégie
// Lorsue le joueur est au contact d'un coté, selon son type
	// cela tue le joueur, tue l'ennemi ou le coté agit comme une plateforme (dont on peut sauter)
class CoteEnnemi
{
public:
	CoteEnnemi(int _cote, Ennemi* _owner);
	virtual bool Update(SceneManager& sceneManager) = 0;

protected:
	bool CheckCollision(Joueur& j);
	int cote;			// Indique de quel coté est le CoteEnnemi : 0 : haut, 1: gauche, 2: droite, 3 : bas

private:	
	Ennemi* owner;
	int margeDetectDept = 5;
	int margeDetectWidth = 20;
};