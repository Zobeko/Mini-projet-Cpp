#include "Static.h"
#include "Joueur.h"
#include "SceneManager.h"

//A enlever
#include <iostream>

Static::Static(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world) : UnitePhysic(_x, _y, _h, _l, textureName, textDictionnary, b2_staticBody, world) {
	std::cout << "Constructeur de Static : (" << _h << ", " << _l << ")" << std::endl;
}


void Static::Update(SceneManager& sceneManager) {
	Joueur j = sceneManager.getJoueur();
	CheckGrounded(j);
	CheckWalled(j);
	Unite::setXY(getBox()->GetPosition().x, getBox()->GetPosition().y);
}


void Static::CheckGrounded(Joueur& j) {
	int centre = getY() + getH();
	if (centre - margeDetect < j.getY() < centre + margeDetect) {
		// Ok pour la hauteur, checkons sur x
		int limiteGaucheX = getX() - margeDetect;
		int limiteDroiteX = getX() + getL() + margeDetect;
		if (((limiteGaucheX < j.getX()) & (j.getX() < limiteDroiteX)) || ((limiteGaucheX < j.getX() + j.getL()) & (j.getX() + j.getL() < limiteDroiteX))) {
			//Le joueur est bien au-dessus de la tile : on le définie comme grounded :
			j.SetGroundedFlag(true);
		}
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
	int centreXjoueur = j.getX() + j.getL();
	int centreYjoueur = j.getY() + j.getH() / 2;
	if (((getX() - margeDetect < centreXjoueur) & (centreXjoueur < getX() + margeDetect)) & ((getY() - margeDetect < centreYjoueur) & (centreYjoueur < getY() + getH() + margeDetect))) {
		j.SetWalledFlag(true);
	}
}
void Static::CheckWalledGauche(Joueur& j) {
	int centreX = getX() + getL();
	int centreYjoueur = j.getY() + j.getH() / 2;
	if (((centreX - margeDetect < j.getX()) & (j.getX() < centreX + margeDetect)) & ((getY() - margeDetect < centreYjoueur) & (centreYjoueur < getY() + getH() + margeDetect))) {
		j.SetWalledFlag(true);
	}
}