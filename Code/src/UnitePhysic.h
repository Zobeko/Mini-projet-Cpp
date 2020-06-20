#pragma once
#include <vector>
#include <Unite.h>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

// Classe dont h�ritent Static et Dynamic
class UnitePhysic : public Unite
{
public:
	virtual ~UnitePhysic();		// Le destructeur doit supprimer les bo�tes de collisions 
	UnitePhysic(float _x, float _y, float _h, float _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2BodyType bodyType, b2World &world);
	b2Body* getBox();
	void setXY(float _x, float _y) override;	// doit �galement changer les x et y de la boite physique

private:
	b2Body* box;	// Pointeur vers la boite associ�e � l'unit�
};