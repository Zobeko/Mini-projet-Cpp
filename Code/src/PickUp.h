#pragma once

#include "Unite.h"
class SceneManager;

// Classe des Pickup, objets sans boite physique mais calculant quand même une intersection avec un autre
class PickUp : public Unite
{
public:
	PickUp(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary);
	virtual ~PickUp() = default;
	virtual bool intersect(Unite & _unite);								// Regarde si l'_unite est en intersection avec le PickUp
	virtual void Update(SceneManager & sceneManager);		// Supprime le pickup du vecteur de Pickup de SceneManager si le joueur le touche (cad intersectionne avec lui)
	bool getDeleteFlag();

protected:
	bool deleteFlag = false;
};