#pragma once

#include "CoteEnnemi.h"

// Cot� tuant l'ennemi le poss�dant au contact
class CoteEnnemi_Kill : public CoteEnnemi
{
public:
	CoteEnnemi_Kill(int _cote, Ennemi* _owner);
	bool Update(SceneManager& sceneManager) override;
};

