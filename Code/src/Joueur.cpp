#include "Joueur.h"
#include <vector>
#include "SceneManager.h"

Joueur::Joueur() : Dynamic(0, 0, dimensions, dimensions, "Hero.png", world) {
	direction = false;
	mirror = false;
	std::vector<int> anim = {0, 0}; //A confirmer avec Louis
}

//Permet de modifier l'etat "� l'abri" du joueur
void Joueur::SetALAbri(bool abri) {
	aLAbri = abri;
}

//M�thode qui tue le joueur si il regarde Meduse sans utiliser le mirroir o etre � l'abri
void Joueur::checkMeduse(SceneManager& sceneManager) {

	//Si le joueur regarde � droite et qu'il n'est pas � l'abri 
	//et que le mirroir n'est pas activ�, alors il meurt
	if ( direction == true && aLAbri == false && mirror == false) {
		sceneManager.tuerJoueur();
	}
}

//Gestions des inputs (appel des diff�rentes gestion d'inputs)
//gestionInputsTypeDep appel�e en 1ere obligatoirement car elle modifie
//la vitesse et les autes gestionInputs d�pendent de cette vitesse
void Joueur::getInputs() {

	gestionInputsTypeDep();
	gestionInputsDir();
	gestionInputsJump();

	//Si le joueur n'est pas au sol, alors on d�clenche l'animation de saut
	if (!grounded) {
		anim[1] = 3;
	}
	//Si le joueur n'est pas au sol et est coll� � un mur, alors on d�clenche
	//l'animation de wall jump tant qu'il est coll� au mur
	if (!grounded && walled) {
		anim[1] = 4;
	}
	
}

//Gestions des inputs de direction, changement de vitesse ad�quat
//et changement de sprite
void Joueur::gestionInputsDir() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		direction = false;
		setVelocityXY(-speed, getVelocityY());

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		direction = true;
		setVelocityXY(speed, getVelocityY());
	}

}

//Gestion des inputs li�s aux differents types de saut (jump et wall jump)
//changement de vitesse ad�quat
//changement de sprite li� au saut g�r� dans getInputs() 
void Joueur::gestionInputsJump() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		setVelocityXY(getVelocityX(), jumpForce);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && grounded == false && walled == true) {
		if (direction == false) {

			setVelocityXY(speed, jumpForce);
		}
		if (direction == false) {

			setVelocityXY(-speed, jumpForce);
		}
	}


}

//Gestion des inputs de de type de d�placements (marche, course ou mirroir)
//Modification des vitesses et num�ros de sprites ad�quat
void Joueur::gestionInputsTypeDep() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		anim[1] = 0;
		speed = 1.5 * speedBase;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		anim[1] = 1;
		speed = -0.6 * speedBase;
	}
	
	anim[1] = 0;
	speed = speedBase;
}