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
	void checkMeduse(SceneManager &sceneManager); // Regarde si le joueur est à l'abri et si il regarde Meduse, 
													//si il n'est pas à l'abri et regarde Meduse,alors il meurt
	void getInputs();
	void gestionInputsDir();
	void gestionInputsJump();
	void gestionInputsTypeDep();

private:
	bool aLAbri = false; //False : joueur pas à l'abri, tuable par le regard de Meduse
							//True : joueur à l'abri, peut regarder dans toutes les directions sans rien craindre
	int speedBase = 0; //Vitesse de base du joueur
	int speed = 0; //Vitesse courante du joueur (diminuée si mirroir...)
	int jumpForce = 0; // Force de saut du joueur
	bool direction; // direction = false : regarde vers la gauche, direction = true : regarde vers la droite
	bool mirror; //mirror = true : mirroir activé ; mirror = false : désactivé
	std::vector<int> anim; //Vecteur dont x contient les numéro de sprite à afficher (de 1 à 3) et y un bool disant que quelle direction on est
	enum animationStates {Marcher, Mirroir, Mourir, Jump, WallJump }; //Enum des différents types de déplacement, et donc différents sprites
	bool grounded = true;
	bool walled = false;
	int const dimensions = 128;

};

