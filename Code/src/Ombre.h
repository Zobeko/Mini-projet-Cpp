#pragma once

#include "Unite.h"
class SceneManager;

// Classe des Ombres. Lorsque la tête du joueur est dans l'ombre, il est protégé de Méduse et peut donc regarder dans les 2 directions sans craintes
class Ombre : public Unite
{
public:
	Ombre(int _x, int _y, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary);
	bool intersect(Unite & _unite);						// Méthode pour savoir si le joueur est en intersection avec l'ombre
	void Update(SceneManager& sceneManager);			// Méthode appelée pour chaque ombre à chaque frame pour savoir si le joueur est à l'abri

protected:
	int const marge = 3;								// Marge de détection des ombres
};

