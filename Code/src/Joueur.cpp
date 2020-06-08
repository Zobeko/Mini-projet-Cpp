#include "Joueur.h"
#include <vector>
#include "SceneManager.h"
#include "myMain.h"

//A enlever
#include <iostream>

Joueur::Joueur(std::map<std::string, sf::Texture>& textDictionnary, b2World& world) : Dynamic(400, 400, 64, 64, "Hero.png", textDictionnary, world) {
	direction = false;
	mirror = false;
	texturePerso.loadFromFile("Hero.png");
}



//Méthode renvoyant le bool de la direction du joueur
bool Joueur::getDirection() {
	return direction;
}

//Méthode qui tue le joueur si il regarde Meduse sans utiliser le mirroir o etre à l'abri
void Joueur::checkMeduse(SceneManager& sceneManager) {

	//Si le joueur regarde à droite et qu'il n'est pas à l'abri 
	//et que le mirroir n'est pas activé, alors il meurt
	if ( direction == true && aLAbri == false && mirror == false) {
		sceneManager.tuerJoueur();
	}
}

void Joueur::update() {

	
	Dynamic::update();
	getInputs();


	//Gestion animation personnage déplacements

	fpsCount += fpsSpeed * clockAnimation.restart().asSeconds();



	if (fpsCount >= fpsSwitch) {
		anim.x++;
		if (anim.x * 32 >= 96) {
			anim.x = 0;

		}
		fpsCount = 0;
	}

	//std::cout << "anim.x : " << anim.x << std::endl;
	//std::cout << "anim.y : " << anim.y  << std::endl;

	if (direction) {
		getSprite().setTextureRect(sf::IntRect((anim.x+1) * dimensions, anim.y * dimensions, -dimensions, dimensions));
	}
	else {
		getSprite().setTextureRect(sf::IntRect(anim.x * dimensions, anim.y * dimensions, dimensions, dimensions));
	}

	cout << "Speed : " << speed << endl;
	
	
}

#pragma region Méthodes liées aux inputs

//Gestions des inputs (appel des différentes gestion d'inputs)
//gestionInputsTypeDep appelée en 1ere obligatoirement car elle modifie
//la vitesse et les autes gestionInputs dépendent de cette vitesse
void Joueur::getInputs() {

	//std::cout << "Grounded : " << grounded << std::endl;
	//std::cout << "Walled : " << walled << std::endl;
	gestionInputsTypeDep();
	gestionInputsDir();
	gestionInputsJump();

	//Si le joueur n'est pas au sol, alors on déclenche l'animation de saut
	if (!grounded) {
		anim.y = 3;
	}
	//Si le joueur n'est pas au sol et est collé à un mur, alors on déclenche
	//l'animation de wall jump tant qu'il est collé au mur
	if (!grounded && walled) {
		anim.y = 4;
	}
	
}

//Gestions des inputs de direction, changement de vitesse adéquat
//et changement de sprite
void Joueur::gestionInputsDir() {
	if (clockWallJump.getElapsedTime().asSeconds() > 0.8f) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			direction = false;
			setVelocityXY(-speed, getVelocityY());

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			direction = true;
			setVelocityXY(speed, getVelocityY());
		}
	}
}

//Gestion des inputs liés aux differents types de saut (jump et wall jump)
//changement de vitesse adéquat
//changement de sprite lié au saut géré dans getInputs() 
void Joueur::gestionInputsJump() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && grounded == true) {
		setVelocityXY(getVelocityX(), jumpForce);
		
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && grounded == false && walled == true) {
		clockWallJump.restart().asSeconds();
		if (direction == false) {

			setVelocityXY(jumpForce, jumpForce);
		}
		if (direction == true) {

			setVelocityXY(-speed, jumpForce);
		}
	}


}

//Gestion des inputs de de type de déplacements (marche, course ou mirroir)
//Modification des vitesses et numéros de sprites adéquat
void Joueur::gestionInputsTypeDep() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
		anim.y = 0;
		speed = 1.5f * speedBase;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
		anim.y = 1;
		speed = - 0.5f * speedBase;
	}
	else {
		anim.y = 0;
		speed = speedBase;
	}
}


#pragma endregion

#pragma region Méthodes de mise des drapeaux
//Permet de modifier l'etat "à l'abri" du joueur
void Joueur::SetALAbri(bool abri) {
	aLAbri = abri;
}
//Permet de dire si oui ou non le joueur est au sol
void Joueur::SetGroundedFlag(bool GF) {
	grounded = GF;
	/*if (GF) {
		std::cout << grounded << endl;
	}*/
}
//Permet de dire si oui ou non le joueur est sur un mur
void Joueur::SetWalledFlag(bool WF) {
	walled = WF;
}
#pragma endregion
