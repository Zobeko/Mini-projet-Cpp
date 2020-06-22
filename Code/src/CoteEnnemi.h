#pragma once

#include "Joueur.h"
class Ennemi;	//Permet d'avoir l'owner 

// Classe d�signant un des4 cot�s d'un ennemi
// Permet d'impl�menter le design Pattern Strat�gie
// Le comportement lorsque le joueur est en contact avec le cot� d�pend la classe d�riv�e du cot�
class CoteEnnemi
{
public:
	CoteEnnemi(int _cote, Ennemi* _owner);
	virtual ~CoteEnnemi() = default;
	virtual bool Update(SceneManager& sceneManager) = 0;		// M�thode d�finissant le comportement � la collision, red�fini dans les sous-classes

protected:
	bool CheckCollision(Joueur& j);		// m�thode regardant si le joueur est en contact avec le cot� (d�pend des coord du joueur, de l'ennemi et de l'attribut cote)
	int cote;			// Indique de quel cot� est le CoteEnnemi : 0 : haut, 1: gauche, 2: droite, 3 : bas

private:	
	Ennemi* owner;
	int margeDetectDept = 5;	//marge pour donner de la profondeur � la zone de d�tection du cot�
	int margeDetectWidth = 20;	// marge pour enlever de la longueur � la zone de d�tection quand c'est un cot� vertical ;
								//permet de ne pas activer le cot� vertical d�s que le joueur descend du cot� haut
								//(mais induit une zone "morte" de collision \\ cette zone est moins g�nant que le probl�me r�gl�)
};