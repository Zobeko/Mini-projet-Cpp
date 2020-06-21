#pragma once

#include "Joueur.h"
class Ennemi;	//Permet d'avoir l'owner 

// Classe d�signant un des4 cot�s d'un ennemi
// Permet d'impl�menter le design Pattern Strat�gie
// Lorsue le joueur est au contact d'un cot�, selon son type
	// cela tue le joueur, tue l'ennemi ou le cot� agit comme une plateforme (dont on peut sauter)
class CoteEnnemi
{
public:
	CoteEnnemi(int _cote, Ennemi* _owner);
	virtual bool Update(SceneManager& sceneManager) = 0;

protected:
	bool CheckCollision(Joueur& j);
	int cote;			// Indique de quel cot� est le CoteEnnemi : 0 : haut, 1: gauche, 2: droite, 3 : bas

private:	
	Ennemi* owner;
	int margeDetectDept = 5;
	int margeDetectWidth = 20;
};