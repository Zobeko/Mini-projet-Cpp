#pragma once

#include "Dynamic.h"
#include "Unite.h"
#include <vector>

class SceneManager;

class Joueur : public Dynamic	
{
public:
	Joueur();
	void SetALAbri(bool abri); // Modifie le bool aLAbri
	void checkMeduse(SceneManager &sceneManager); // Regarde si le joueur est � l'abri et si il regarde Meduse, 
													//si il n'est pas � l'abri et regarde Meduse,alors il meurt
	void getInputs();
	void gestionInputsDir();
	void gestionInputsJump();
	void gestionInputsTypeDep();

private:
	bool aLAbri = false; //False : joueur pas � l'abri, tuable par le regard de Meduse
							//True : joueur � l'abri, peut regarder dans toutes les directions sans rien craindre
	int speedBase = 0; //Vitesse de base du joueur
	int speed = 0; //Vitesse courante du joueur (diminu�e si mirroir...)
	int jumpForce = 0; // Force de saut du joueur
	bool direction; // direction = false : regarde vers la gauche, direction = true : regarde vers la droite
	bool mirror; //mirror = true : mirroir activ� ; mirror = false : d�sactiv�
	std::vector<int> anim; //Vecteur dont x contient les num�ro de sprite � afficher (de 1 � 3) et y un bool disant que quelle direction on est
	enum animationStates {Marcher, Mirroir, Mourir, Jump, WallJump }; //Enum des diff�rents types de d�placement, et donc diff�rents sprites
	bool grounded = true;
	bool walled = false;
	int const dimensions = 128;

};

