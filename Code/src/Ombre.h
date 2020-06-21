#pragma once

#include "Unite.h"
class SceneManager;

// Classe des Ombres. Lorsque la t�te du joueur est dans l'ombre, il est prot�g� de M�duse et peut donc regarder dans les 2 directions sans craintes
class Ombre : public Unite
{
public:
	Ombre(int _x, int _y, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary);
	virtual bool intersect(Unite & _unite);
	void Update(SceneManager& sceneManager);

protected:
	int const marge = 3;
};

