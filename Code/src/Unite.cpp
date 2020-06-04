#include "Unite.h"
#include <vector>
#include <SFML/Graphics.hpp>

// à enlever après
#include <iostream>

using namespace std;

Unite::Unite(int _x, int _y, int _h, int _l, std::string textureName) {
	x = _x;
	y = _y;
	h = _h;
	l = _l;
	//sprite.setTexture(texture);
	sprite.setPosition(x, y);	// à modifier pour avoir le sprite au bon endroit
	sprite.setTextureRect(sf::IntRect(0, 0, _l, _h)); //idem ?
}

Unite::Unite(){}

int Unite::getX() {
	return x;
}
int Unite::getY() {
	return y;
}
int Unite::getH() {
	return h;
}
int Unite::getL() {
	return l;
}

void Unite::setXY(int _x, int _y) {
	x = _x;
	y = _y;
	// Changer la position de la texture
}
void Unite::setSprite(int _h, int _l, std::string textureName) {
	h = _h;
	l = _l;
	sprite.setTextureRect(sf::IntRect(0, 0, _l, _h));
}

void Unite::draw() {
	std::cout << "Afficher l'image ici " << endl;
}