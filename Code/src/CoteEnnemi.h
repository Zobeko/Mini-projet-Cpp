#pragma once

#include "Joueur.h"
class Ennemi;	//Permet d'avoir l'owner 

// Classe désignant un des4 cotés d'un ennemi
// Permet d'implémenter le design Pattern Stratégie
// Le comportement lorsque le joueur est en contact avec le coté dépend la classe dérivée du coté
class CoteEnnemi
{
public:
	CoteEnnemi(int _cote, Ennemi* _owner);
	virtual ~CoteEnnemi() = default;
	virtual bool Update(SceneManager& sceneManager) = 0;		// Méthode définissant le comportement à la collision, redéfini dans les sous-classes

protected:
	bool CheckCollision(Joueur& j);		// méthode regardant si le joueur est en contact avec le coté (dépend des coord du joueur, de l'ennemi et de l'attribut cote)
	int cote;			// Indique de quel coté est le CoteEnnemi : 0 : haut, 1: gauche, 2: droite, 3 : bas

private:	
	Ennemi* owner;
	int margeDetectDept = 5;	//marge pour donner de la profondeur à la zone de détection du coté
	int margeDetectWidth = 20;	// marge pour enlever de la longueur à la zone de détection quand c'est un coté vertical ;
								//permet de ne pas activer le coté vertical dès que le joueur descend du coté haut
								//(mais induit une zone "morte" de collision \\ cette zone est moins génant que le problème réglé)
};