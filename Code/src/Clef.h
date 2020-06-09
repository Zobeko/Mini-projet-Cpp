#pragma once

#include "PickUp.h"
#include "SceneManager.h"

// Classe des objets clef
// Lorsqu'en contact avec le joueur, la clef est ramassée et l'indique au SceneManager
// Le joueur pourra alors ouvrir la porte
class Clef : public PickUp
{
public:
	Clef(int _x, int _y, std::map<std::string, sf::Texture>& textDictionnary);
	void Update(SceneManager& sceneManager, int iDpickUp) override;
};