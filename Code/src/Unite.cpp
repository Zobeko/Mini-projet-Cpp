#include "Unite.h"
#include <vector>
#include <SFML/Graphics.hpp>


// � enlever apr�s
#include <iostream>

using namespace std;

Unite::Unite(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture> & textDictionnary) {
	x = _x;
	y = _y;
	h = _h;
	l = _l;

	setSprite(_h, _l, textureName, textDictionnary);
	
	sprite.setPosition(x, y);	// � modifier pour avoir le sprite au bon endroit
	sprite.setTextureRect(sf::IntRect(0, 0, _l, _h)); //idem ?
}


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
void Unite::setSprite(int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary) {
	h = _h;
	l = _l;
	if (textDictionnary.find(textureName) != textDictionnary.end()) {
		// la texture existe
		sprite.setTexture(textDictionnary[textureName]);
	}
	else {
		// la texture n'existe pas encore : il faut l'ajouter au dictionnaire
		sf::Texture texture;
		if (!texture.loadFromFile("resources/" + textureName)) {                                       // la ressource doit �tre dans build/MainLauncher, au niveau des .vcxproj
			cout << "Error loading texture : " + textureName << endl;
		}
		texture.setSmooth(true);
		textDictionnary.insert(std::pair<std::string, sf::Texture>(textureName, texture));
		// On assigne bien la texture issue du dictionnaire � l'unite pour eviter les pb de variables locales
		sprite.setTexture(textDictionnary[textureName]);
	}
	sprite.setTextureRect(sf::IntRect(0, 0, _l, _h));
}

void Unite::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}