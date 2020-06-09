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
	bool getDirection();//Renvoie walled
	bool getGrounded();//Renvoie grounded

	void checkMeduse(SceneManager &sceneManager); // Regarde si le joueur est � l'abri et si il regarde Meduse, 
													//si il n'est pas � l'abri et regarde Meduse, alors il meurt
	void getInputs();
	void gestionInputsDir();//Gestion des inputs Left et Right qui deplacent le joueur et modifient la direction du joueur
	void gestionInputsJump();//Gestion des inputs de jump et de wall jump
	void gestionInputsTypeDep();//Gestion des inputs de course(LShift) et mirroir(Lcontrol)

	void SetALAbri(bool abri); // Modifie le bool aLAbri
	void SetGroundedFlag(bool GF);// Modifie le bool grounded
	void SetWalledFlag(bool WF);// Modifie le bool walled

	void init(float _x, float _y);//initialise la vitesse du joueur � (0,0), sa direction � false (gauche) 
									//et sa position(r�cup�r�e dans le xmldans SceneManager::chargerSalle()

	void update(SceneManager &sceneManager);//update du joueur
	

private:
	bool grounded = false;//False : le joueur ne touche pas le sol
							//True : le joueur touche le sol
	bool walled = false;//false : le joueur ne touche pas de mur
						//True : le joueur touche un mur
	bool aLAbri = false; //False : joueur pas � l'abri, tuable par le regard de Meduse
							//True : joueur � l'abri, peut regarder dans toutes les directions sans rien craindre

	float speedBase = 22.f; //Vitesse de base du joueur
	float speed = 22.f; //Vitesse courante du joueur (diminu�e si mirroir, augment�e si course...)

	float jumpForce = 90;//Force de saut du joueur
	float wallJumpForce = 40.f;// Force de wall jump du joueur
	bool direction; // direction = false : regarde vers la gauche, direction = true : regarde vers la droite
	bool mirror; //mirror = true : mirroir activ� ; mirror = false : d�sactiv�
	 //Vecteur dont x contient les num�ro de sprite � afficher (de 1 � 3) et y un bool disant que quelle direction on est
	enum animationStates {Marcher, Mirroir, Mourir, Jump, WallJump }; //Enum des diff�rents types de d�placement, et donc diff�rents sprites
	sf::Vector2i anim = { 1, Marcher};//Vecteur dont x contient les num�ro de sprite � afficher (de 1 � 3) et y un bool disant que quelle direction on est

	int const dimensions = 64;//Dimension du sprite du joueur
	sf::Texture texturePerso;//Texture du joueur
	sf::Clock clockAnimation;//Horloge des animations
	sf::Clock clockWallJump;//Horloge du wall jump
	float fpsCount = 0, fpsSpeed = 700, fpsSwitch = 100; //Constantes pour reduire la fr�quence d'affichage des animations

};

