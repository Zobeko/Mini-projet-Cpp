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
	CoteEnnemi(int _cote, int _type, Ennemi* _owner);
	bool Update(SceneManager& sceneManager);

protected:
	bool CheckCollision(Joueur& j);

private:
	int cote;			// Indique de quel coté est le CoteEnnemi : 0 : haut, 1: gauche, 2: droite, 3 : bas
	int type;			// Indique le type du coté, c'est ce qui va définir son comportement : 0 : tue le joueur, 1 : tue l'ennemi, 3 : agit comme un static (cond sur cote pour faire Walled ou Grounded)
	Ennemi* owner;
};

