#pragma once

#include "UnitePhysic.h"
#include "Joueur.h"
class SceneManager;

// Classe dont h�ritent les objets poss�dant une boite physique statique
class Static : public UnitePhysic
{
public:
	Static(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2World& world);
	virtual ~Static() = default;
	void Update(SceneManager& sceneManager);
	
protected: // Pour que les classes h�rit�es y aient acc�s et puissent r��crire leur m�thodes de collision
	void CheckGrounded(Joueur& j);
	void CheckWalled(Joueur& j);
	void CheckWalledDroite(Joueur& j);
	void CheckWalledGauche(Joueur& j);
	float const margeDetect = 6.f;

};

