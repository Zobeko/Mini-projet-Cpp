#pragma once

#include "Dynamic.h"
#include "Unite.h"
#include <vector>
class SceneManager;

// Classe du Joueur
class Joueur : public Dynamic	
{
public:
	Joueur(std::map<std::string, sf::Texture>& textDictionnary, b2World& world);
	bool getDirection();
	void checkMeduse(SceneManager &sceneManager); // Regarde si le joueur est à l'abri et si il regarde Meduse, 
													//si il n'est pas à l'abri et regarde Meduse, alors il meurt
	void getInputs();
	void gestionInputsDir();
	void gestionInputsJump();
	void gestionInputsTypeDep();

	void SetALAbri(bool abri); // Modifie le bool aLAbri
	void SetGroundedFlag(bool GF);
	void SetWalledFlag(bool WF);

	void update(SceneManager &sceneManager);

	bool walled = false;
	

private:
	bool aLAbri = false; //False : joueur pas à l'abri, tuable par le regard de Meduse
							//True : joueur à l'abri, peut regarder dans toutes les directions sans rien craindre
	float speedBase = 22.f; //Vitesse de base du joueur
	float speed = 22.f; //Vitesse courante du joueur (diminuée si mirroir...)
	int jumpForce = 90;
	float wallJumpForce = 40.f;// Force de saut du joueur
	bool direction; // direction = false : regarde vers la gauche, direction = true : regarde vers la droite
	bool mirror; //mirror = true : mirroir activé ; mirror = false : désactivé
	 //Vecteur dont x contient les numéro de sprite à afficher (de 1 à 3) et y un bool disant que quelle direction on est
	enum animationStates {Marcher, Mirroir, Mourir, Jump, WallJump }; //Enum des différents types de déplacement, et donc différents sprites
	sf::Vector2i anim = { 1, Marcher};//Vecteur dont x contient les numéro de sprite à afficher (de 1 à 3) et y un bool disant que quelle direction on est
	bool grounded = true;
	int const dimensions = 64;
	sf::Texture texturePerso;
	sf::Clock clockAnimation;
	sf::Clock clockWallJump;
	float fpsCount = 0, fpsSpeed = 700, fpsSwitch = 100;

};

