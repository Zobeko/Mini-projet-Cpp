#include "Unite.h"
#include <vector>
#include <SFML/Graphics.hpp>


// à enlever après
#include <iostream>

#define WINDOW_HEIGHT 568

using namespace std;

Unite::Unite(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture> & textDictionnary) {
	x = _x;
	y = _y;

	setSprite(_h, _l, textureName, textDictionnary);
	
	sprite.setPosition(x, (WINDOW_HEIGHT - y));	// à modifier pour avoir le sprite au bon endroit
	//sprite.setTextureRect(sf::IntRect(0, 0, _l, _h)); //idem 	
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

sf::Sprite& Unite::getSprite() {
	return sprite;
}

void Unite::setXY(int _x, int _y) {
	//Change la position de Unite
	x = _x;
	y = _y;

	

	// Change la position de la texture sur celle de Unite
	sprite.setPosition(x, (WINDOW_HEIGHT - y));
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
		if (!texture.loadFromFile("resources/" + textureName)) {                                       // la ressource doit être dans build/MainLauncher, au niveau des .vcxproj
			cout << "Error loading texture : " + textureName << endl;
		}
		texture.setSmooth(true);
		textDictionnary.insert(std::pair<std::string, sf::Texture>(textureName, texture));
		// On assigne bien la texture issue du dictionnaire à l'unite pour eviter les pb de variables locales
		sprite.setTexture(textDictionnary[textureName]);
	}
	//sprite.setTextureRect(sf::IntRect(0, 0, _l, _h));
}

void Unite::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}