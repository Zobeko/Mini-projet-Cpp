#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

// Classe mère de presque tous les éléments ayant une partie graphique
class Unite
{
public:
	virtual ~Unite() = default;
	Unite(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary);
	int getX();
	int getY();
	int getH();
	int getL();
	sf::Sprite& getSprite();
	virtual void setXY(int _x, int _y);			// Est virtual pour pouvoir être override dans UnitePhysic
	void setSprite(int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary);		// Permet de modifier la texture du sprite
	void draw(sf::RenderWindow & window);		// Dessine le sprite dans la fenetre

private:
	int x;				// Position X de l'unité
	int y;				// Position Y de l'unité
	int h;				// Hauteur de l'unité. L'axe des Y dans le repère des Unités est orienté vers le haut : Y est le haut pour les unités, Y-H est le bas
	int l;				// Largeur de l'unité. L'axe des X est orienté vers la droite : X est la gauche, X+L est la droite
	sf::Sprite sprite;	// Sprite de l'unité
};