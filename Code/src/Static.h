#pragma once

#include "UnitePhysic.h"
#include "Joueur.h"
class SceneManager;


class Static : public UnitePhysic
{
public:
	Static(int _x, int _y, int _h, int _l, std::string textureName, b2World& world);
	void Update(SceneManager & sceneManager);
	
protected: // Pour que les classes héritées y aient accès et puissent réécrire leur méthodes de collision
	void CheckGrounded(Joueur& j);
	void CheckWalled(Joueur& j);
	void CheckWalledDroite(Joueur& j);
	void CheckWalledGauche(Joueur& j);
	float const margeDetect = 0.1;

};

