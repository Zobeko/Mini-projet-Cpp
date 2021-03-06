#pragma once

#include "Dynamic.h"
#include "Unite.h"
#include <vector>
#include <SFML/audio.hpp>
class SceneManager;

// Classe du Joueur
class Joueur : public Dynamic	
{
public:
	Joueur(std::map<std::string, sf::Texture>& textDictionnary, b2World& world);
	bool getDirection();
	bool getGrounded();

	void checkMeduse(SceneManager &sceneManager);	// Regarde si le joueur est � l'abri et si il regarde Meduse, si il n'est pas � l'abri et regarde Meduse, alors il meurt
	void checkCadre(SceneManager& seneManager);		// V�rifies que le joueur reste dans le cadre

	void getInputs();					//Regarde les inputs est fait agir le joueur en cons�quence
	void gestionInputsDir();			//Gestion des inputs Left et Right qui deplacent le joueur et modifient la direction du joueur
	void gestionInputsJump();			//Gestion des inputs de jump et de wall jump
	void gestionInputsTypeDep();		//Gestion des inputs de course(LShift) et mirroir(Lcontrol)

	void SetALAbri(bool abri);
	void SetGroundedFlag(bool GF);
	void SetWalledFlag(bool WF);
	void SetMirror(bool MF);

	void init(float _x, float _y);//initialise la vitesse du joueur � (0,0), sa direction � false (gauche) 
									//et sa position(r�cup�r�e dans le xmldans SceneManager::chargerSalle()

	void update(SceneManager &sceneManager);//update du joueur

	float getDroite();			// Renvoie la limite droite de la boite de collision du joueur (comme on l'a affin�, ce n'est pas X+L mais X+L-affineCote
	float getGauche();			// Renvoie la limite gauche de la boite de collision du joueur (comme on l'a affin�, ce n'est pas X mais X+affineCote

	void setDeathAnim();		// Permet de joueur l'animation de mort
	void playAnim();			// Permet de jouer l'animation correspondant � la situation du joueur
	

private:
	sf::SoundBuffer bufferSaut;	// �l�ments de SFML pour le bruitage du saut
	sf::Sound soundSaut;		// �l�ments de SFML pour le bruitage du saut

	bool grounded = false;	//False : le joueur ne touche pas le sol
							//True : le joueur touche le sol
	bool walled = false;	//false : le joueur ne touche pas de mur
							//True : le joueur touche un mur
	bool aLAbri = false;	//False : joueur pas � l'abri, tuable par le regard de Meduse
							//True : joueur � l'abri, peut regarder dans toutes les directions sans rien craindre

	float speedBase = 22.f; //Vitesse de base du joueur
	float speed = 22.f;		//Vitesse courante du joueur (diminu�e si mirroir, augment�e si course...)

	float jumpForce = 90;		//Force de saut du joueur
	float wallJumpForce = 40.f;	// Force de wall jump du joueur
	bool direction;				// direction = false : regarde vers la gauche, direction = true : regarde vers la droite
	bool mirror = false;		//mirror = true : mirroir activ� ; mirror = false : d�sactiv�
								//Vecteur dont x contient les num�ro de sprite � afficher (de 1 � 3) et y un bool disant que quelle direction on est
	enum animationStates {Marcher, Mirroir, Mourir, Jump, WallJump };	//Enum des diff�rents types de d�placement, et donc diff�rents sprites
	sf::Vector2i anim = { 1, Marcher};									//Vecteur dont x contient les num�ro de sprite � afficher (de 1 � 3) et y un bool disant que quelle direction on est

	int const dimensions = 64;	//Dimension du sprite du joueur
	sf::Texture texturePerso;	//Texture du joueur
	sf::Clock clockAnimation;	//Horloge des animations
	sf::Clock clockWallJump;	//Horloge du wall jump
	float fpsCount = 0, fpsSpeed = 700, fpsSwitch = 100; //Constantes pour reduire la fr�quence d'affichage des animations

	float const affineCote = 10.f;	// De combat on affine la boite de collision du joueur par rapport � ses dimensions (64)
};

