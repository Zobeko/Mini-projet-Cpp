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
	CoteEnnemi(int _cote, int _type, Ennemi* _owner);
	bool Update(SceneManager& sceneManager);

protected:
	bool CheckCollision(Joueur& j);

private:
	int cote;			// Indique de quel cot� est le CoteEnnemi : 0 : haut, 1: gauche, 2: droite, 3 : bas
	int type;			// Indique le type du cot�, c'est ce qui va d�finir son comportement : 0 : tue le joueur, 1 : tue l'ennemi, 3 : agit comme un static (cond sur cote pour faire Walled ou Grounded)
	Ennemi* owner;
};

