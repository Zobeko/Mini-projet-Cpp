#pragma once

#include "Dynamic.h"
#include "Unite.h"
#include <vector>
class SceneManager;

class Joueur : public Dynamic	
{
public:
	Joueur(std::map<std::string, sf::Texture>& textDictionnary, b2World& world);
	bool getDirection();
	void checkMeduse(SceneManager &sceneManager); // Regarde si le joueur est � l'abri et si il regarde Meduse, 
													//si il n'est pas � l'abri et regarde Meduse,alors il meurt
	void getInputs();
	void gestionInputsDir();
	void gestionInputsJump();
	void gestionInputsTypeDep();

	void SetALAbri(bool abri); // Modifie le bool aLAbri
	void SetGroundedFlag(bool GF);
	void SetWalledFlag(bool WF);

	void update();

	bool walled = false;
	

private:
	bool aLAbri = false; //False : joueur pas � l'abri, tuable par le regard de Meduse
							//True : joueur � l'abri, peut regarder dans toutes les directions sans rien craindre
	float speedBase = 80.f; //Vitesse de base du joueur
	float speed = 80.f; //Vitesse courante du joueur (diminu�e si mirroir...)
	int jumpForce = 500000; // Force de saut du joueur
	bool direction; // direction = false : regarde vers la gauche, direction = true : regarde vers la droite
	bool mirror; //mirror = true : mirroir activ� ; mirror = false : d�sactiv�
	 //Vecteur dont x contient les num�ro de sprite � afficher (de 1 � 3) et y un bool disant que quelle direction on est
	enum animationStates {Marcher, Mirroir, Mourir, Jump, WallJump }; //Enum des diff�rents types de d�placement, et donc diff�rents sprites
	sf::Vector2i anim = { 1, Marcher};//Vecteur dont x contient les num�ro de sprite � afficher (de 1 � 3) et y un bool disant que quelle direction on est
	bool grounded = true;
	int const dimensions = 64;
	sf::Texture texturePerso;
	sf::Clock clock;
	float fpsCount = 0, fpsSpeed = 700, fpsSwitch = 100;

};

