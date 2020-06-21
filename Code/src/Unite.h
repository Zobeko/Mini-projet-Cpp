#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

// Classe m�re de presque tous les �l�ments ayant une partie graphique
class Unite
{
public:
	virtual ~Unite() = default;
	Unite(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary);
	float getX();
	float getY();
	float getH();
	float getL();
	sf::Sprite& getSprite();
	virtual void setXY(float _x, float _y);			// Est virtual pour pouvoir �tre override dans UnitePhysic
	void setSprite(int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary);		// Permet de modifier la texture du sprite
	void draw(sf::RenderWindow & window);		// Dessine le sprite dans la fenetre

private:
	float x;				// Position X de l'unit�
	float y;				// Position Y de l'unit�
	float h;				// Hauteur de l'unit�. L'axe des Y dans le rep�re des Unit�s est orient� vers le haut : Y est le haut pour les unit�s, Y-H est le bas
	float l;				// Largeur de l'unit�. L'axe des X est orient� vers la droite : X est la gauche, X+L est la droite
	sf::Sprite sprite;	// Sprite de l'unit�
};