#include "Static.h"
#include "Joueur.h"
#include "SceneManager.h"

//A enlever
#include <iostream>

Static::Static(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world) : UnitePhysic(_x, _y, _h, _l, textureName, textDictionnary, b2_staticBody, world) {

}


void Static::Update(SceneManager& sceneManager) {
	//Joueur j = *sceneManager.getJoueur();
	CheckGrounded(*sceneManager.getJoueur());
	CheckWalled(*sceneManager.getJoueur());
	//Unite::setXY(getBox()->GetPosition().x, getBox()->GetPosition().y);
}


void Static::CheckGrounded(Joueur& j) {
	int centre = getY();
	if (centre - margeDetect*3 < (j.getY() - j.getH()) && (j.getY() - j.getH()) < centre + margeDetect*3) {
		getSprite().setColor(sf::Color::Red);
		// Ok pour la hauteur, checkons sur x
		int limiteGaucheX = j.getGauche(); //t;
		int limiteDroiteX = j.getDroite();  //+margeDetect;
		if (((limiteGaucheX < getX()) && (getX() < limiteDroiteX)) || ((limiteGaucheX < getX() + getL()) && (getX() + getL() < limiteDroiteX))) {
			//Le joueur est bien au-dessus de la tile : on le définie comme grounded :
			j.SetGroundedFlag(true);
			getSprite().setColor(sf::Color::Blue);
		}
	}
	else {
		getSprite().setColor(sf::Color::White);
	}
}
void Static::CheckWalled(Joueur& j) {
	//On commence par récupérer la direction vers laquelle regarde le joueur
	if (j.getDirection()) {
		CheckWalledDroite(j);
	}
	else {
		CheckWalledGauche(j);
	}
}
void Static::CheckWalledDroite(Joueur& j) {
	int centreXjoueur = j.getDroite();
	int centreYjoueur = j.getY() - j.getH() / 2;
	if (((getX() - margeDetect < centreXjoueur) & (centreXjoueur < getX() + margeDetect)) & ((getY() - margeDetect - getH() < centreYjoueur) & (centreYjoueur < getY() + margeDetect))) {
		j.SetWalledFlag(true);
		getSprite().setColor(sf::Color::Green);
	}
}
void Static::CheckWalledGauche(Joueur& j) {
	int centreXjoueur = j.getGauche();
	int centreYjoueur = j.getY() - j.getH() / 2;
	if (((getX() + getL() - margeDetect < centreXjoueur) & (centreXjoueur < getX() + getL() + margeDetect)) & ((getY() - margeDetect - getH() < centreYjoueur) & (centreYjoueur < getY() + margeDetect))) {
		j.SetWalledFlag(true);
		getSprite().setColor(sf::Color::Yellow);
	}
}