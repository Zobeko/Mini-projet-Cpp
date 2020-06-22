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
	void Update(SceneManager& sceneManager);	// Regarde � chaque frame si le joueur est walled ou grounded sur le static
	void CheckGrounded(Joueur& j);		// Regarde si le joueur est sur le static pour le marquer grounded
	void CheckWalled(Joueur& j);		// Regarde si le joueur est sur un cot� du static
	
protected: // Pour que les classes h�rit�es y aient acc�s et puissent r��crire leur m�thodes de collision si bsoin
	void CheckWalledDroite(Joueur& j);	// Regarde si le joueur est sur le cot� droit du static ; necessite d'appuyer sur "gauche" pour valider
	void CheckWalledGauche(Joueur& j);	// Regarde si le joueur est sur le cot� gauche du static ; necessite d'appuyer sur "droite" pour valider
	int const margeDetect = 6;			// Marge de d�tection

};

