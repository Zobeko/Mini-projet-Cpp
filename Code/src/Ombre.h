#pragma once

#include "Unite.h"
class SceneManager;

// Classe des Ombres. Lorsque la t�te du joueur est dans l'ombre, il est prot�g� de M�duse et peut donc regarder dans les 2 directions sans craintes
class Ombre : public Unite
{
public:
	Ombre(int _x, int _y, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary);
	bool intersect(Unite & _unite);						// M�thode pour savoir si le joueur est en intersection avec l'ombre
	void Update(SceneManager& sceneManager);			// M�thode appel�e pour chaque ombre � chaque frame pour savoir si le joueur est � l'abri

protected:
	int const marge = 3;								// Marge de d�tection des ombres
};

