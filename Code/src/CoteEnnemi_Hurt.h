#pragma once

#include "CoteEnnemi.h"

// Cot� tuant le joueur au contact
class CoteEnnemi_Hurt : public CoteEnnemi
{
public:
	CoteEnnemi_Hurt(int _cote, Ennemi* _owner);
	bool Update(SceneManager& sceneManager) override;
};

