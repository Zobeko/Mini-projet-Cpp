#include "Unite.h"
#include <vector>
#include <SFML/Graphics.hpp>


// à enlever après
#include <iostream>

#define WINDOW_HEIGHT 600

using namespace std;

Unite::Unite(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture> & textDictionnary) {
	x = _x;
	y = _y;
	setSprite(_h, _l, textureName, textDictionnary);	
	sprite.setPosition(x, (WINDOW_HEIGHT - y));
}


float Unite::getX() {
	return x; 
}
float Unite::getY() {
	return y;
}
float Unite::getH() {
	return h;
}
float Unite::getL() {
	return l;
}

sf::Sprite& Unite::getSprite() {
	return sprite;
}

void Unite::setXY(float _x, float _y) {
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
		// la texture a été chargée : l'objet existe et on le charge
		sprite.setTexture(textDictionnary[textureName]);
	}
	else {
		// la texture n'existe pas encore : il faut l'ajouter au dictionnaire
		sf::Texture texture;
		if (!texture.loadFromFile("resources/" + textureName)) {
			cerr << "Error loading texture : " + textureName << endl;
		}
		texture.setSmooth(true);
		textDictionnary.insert(std::pair<std::string, sf::Texture>(textureName, texture));
		sprite.setTexture(textDictionnary[textureName]);
	}
}

void Unite::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}