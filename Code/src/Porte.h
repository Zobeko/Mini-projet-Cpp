#pragma once

#include "PickUp.h"
#include "SceneManager.h"


// Classe de la porte. Si la clef a �t� ramass�e, toucher la porte permet d'aller au niveau suivant s'il y en a un et de finir le jeu sinon
class Porte : public PickUp
{
public:
	Porte(int _x, int _y, std::map<std::string, sf::Texture>& textDictionnary);
	void Update(SceneManager& sceneManager) override;
};