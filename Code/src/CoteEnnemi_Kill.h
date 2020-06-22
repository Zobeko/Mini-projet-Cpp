#pragma once

#include "CoteEnnemi.h"

// Coté tuant l'ennemi le possédant au contact
class CoteEnnemi_Kill : public CoteEnnemi
{
public:
	CoteEnnemi_Kill(int _cote, Ennemi* _owner);
	bool Update(SceneManager& sceneManager) override;
};

