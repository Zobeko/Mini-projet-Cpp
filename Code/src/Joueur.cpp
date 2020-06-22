#include "Joueur.h"
#include <vector>
#include "SceneManager.h"
#include "myMain.h"

#include <iostream>


Joueur::Joueur(std::map<std::string, sf::Texture>& textDictionnary, b2World& world) : Dynamic(400, 400, 64, 64, "Hero.png", textDictionnary, world) {
	direction = false;
	mirror = false;
	
	// Pour le joueur on met une boite de collision différente
	box->DestroyFixture(box->GetFixtureList());

	/*//Ajout de la sphère (partie basse)
	b2CircleShape  circle;
	circle.m_radius = ((64.f / 2.f) / 10.f);
	// 10.f, b2Vec2(0, 1.6f), 0); //_h=54 et _l=54 pour que ca marche bien pour le perso
	// Défini les caractéristiques de notre boite de collision
	b2FixtureDef fixtureCircleDef;
	fixtureCircleDef.shape = &circle;
	fixtureCircleDef.density = 1.0f;
	fixtureCircleDef.friction = 0.9f;
	box->CreateFixture(&fixtureCircleDef);*/

	//Ajout de la sphère (partie basse)
	b2CircleShape  circle1;
	circle1.m_radius = ((64.f - affineCote*2.f) / 2.f) / 10.f;
	circle1.m_p.Set(0, -(affineCote / 10.f));
	// 10.f, b2Vec2(0, 1.6f), 0); //_h=54 et _l=54 pour que ca marche bien pour le perso
	// Défini les caractéristiques de notre boite de collision
	b2FixtureDef fixtureCircleDef1;
	fixtureCircleDef1.shape = &circle1;
	fixtureCircleDef1.density = 1.0f;
	fixtureCircleDef1.friction = 0.9f;
	box->CreateFixture(&fixtureCircleDef1);

	//Ajout de la sphère (partie haute)
	b2CircleShape  circle2;
	circle2.m_radius = ((64.f - affineCote*2.f) / 2.f) / 10.f;
	circle2.m_p.Set(0, (affineCote-1) / 10.f);
	// 10.f, b2Vec2(0, 1.6f), 0); //_h=54 et _l=54 pour que ca marche bien pour le perso
	// Défini les caractéristiques de notre boite de collision
	b2FixtureDef fixtureCircleDef2;
	fixtureCircleDef2.shape = &circle2;
	fixtureCircleDef2.density = 1.0f;
	fixtureCircleDef2.friction = 0.9f;
	box->CreateFixture(&fixtureCircleDef2);
}

float Joueur::getDroite() {
	return getX() + getL() - affineCote;
}
float Joueur::getGauche() {
	return getX() + affineCote;	
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
		sceneManager.setDeathFlagTrue();
	}
}

void Joueur::checkCadre(SceneManager& sceneManager) {
	if (getX() < -64 || getX() > 864 || getY() < -64 || getY() > 664) {
		sceneManager.setDeathFlagTrue();

	}

}

void Joueur::init(float _x, float _y) {
	setXY(_x, _y);
	direction = false;
	setVelocityXY(0, 0);
}

void Joueur::update(SceneManager& sceneManager) {

	
	Dynamic::update();
	getInputs();
	checkMeduse(sceneManager);
	checkCadre(sceneManager);


	//Gestion animation personnage déplacements
	playAnim();

}

void Joueur::setDeathAnim() {
	if (direction) {
		getSprite().setTextureRect(sf::IntRect(dimensions, 2 * dimensions, -dimensions, dimensions));
	}
	else {
		getSprite().setTextureRect(sf::IntRect(dimensions, 2 * dimensions, dimensions, dimensions));
	}
	std::cout << "On a mis l'anim de mort" << std::endl;
}
void Joueur::playAnim() {
	fpsCount += fpsSpeed * clockAnimation.restart().asSeconds();

	if (fpsCount >= fpsSwitch) {
		anim.x++;
		if (anim.x * 32 >= 96) {
			anim.x = 0;
		}
		fpsCount = 0;
	}

	if (direction) {
		getSprite().setTextureRect(sf::IntRect((anim.x + 1) * dimensions, anim.y * dimensions, -dimensions, dimensions));
	}
	else {
		getSprite().setTextureRect(sf::IntRect(anim.x * dimensions, anim.y * dimensions, dimensions, dimensions));
	}
}

#pragma region Méthodes liées aux inputs

//Gestions des inputs (appel des différentes gestion d'inputs)
//gestionInputsTypeDep appelée en 1ere obligatoirement car elle modifie
//la vitesse et les autes gestionInputs dépendent de cette vitesse
void Joueur::getInputs() {

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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && grounded == true) {
			direction = false;
			setVelocityXY(-speed, getVelocityY());

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && grounded == false && getVelocityY() > 0) {
			direction = false;
			setVelocityXY(-speed, getVelocityY());
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && grounded == false && getVelocityY() < 20) {
			direction = false;
			setVelocityXY(-speed, -speed);
		}



		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && grounded == true) {
			direction = true;
			setVelocityXY(speed, getVelocityY());
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && grounded == false && getVelocityY() > 0) {
			direction = true;
			setVelocityXY(speed, getVelocityY());
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && grounded == false && getVelocityY() < 0) {
			direction = true;
			setVelocityXY(speed, -speed);
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
		if (direction == false) {	//& sf::Keyboard::isKeyPressed(sf::Keyboard::Left)

			setVelocityXY(wallJumpForce, wallJumpForce);
		}
		if (direction == true) {	//& sf::Keyboard::isKeyPressed(sf::Keyboard::Right)

			setVelocityXY(-wallJumpForce, wallJumpForce);
		}
	}


}

//Gestion des inputs de de type de déplacements (marche, course ou mirroir)
//Modification des vitesses et numéros de sprites adéquat
void Joueur::gestionInputsTypeDep() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && grounded==true && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
		anim.y = 0;
		speed = 1.5f * speedBase;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && grounded==true && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
		anim.y = 1;
		speed = - 0.5f * speedBase;
		mirror = true;
	}
	else {
		anim.y = 0;
		speed = speedBase;
	}
}

bool Joueur::getGrounded() {
	return grounded;
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
}
//Permet de dire si oui ou non le joueur est sur un mur
void Joueur::SetWalledFlag(bool WF) {
	walled = WF;
}

void Joueur::SetMirror(bool MF) {
	mirror = MF;
}
#pragma endregion
