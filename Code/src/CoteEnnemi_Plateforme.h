#pragma once

#include "CoteEnnemi.h"

// Coté agissant comme un static normal cad plateforme ou mur
class CoteEnnemi_Plateforme : public CoteEnnemi
{
public:
	CoteEnnemi_Plateforme(int _cote, Ennemi* _owner);
	bool Update(SceneManager& sceneManager) override;
};

