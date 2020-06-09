#pragma once

#include "SceneManager.h"
#include "Unite.h"
#include "PickUp.h"

// Classe des pi�ces. Lorsqu'elles sont ramass�es elles augmentent le compteur de pi�ce d'une certaine valeur
// Le nombre de pi�ce ne change rien au gameplay
class Piece : public PickUp
{
public:
	Piece(int _x, int _y, std::map<std::string, sf::Texture>& textDictionnary, int _value);
	void Update(SceneManager& sceneManager, int iDpickUp) override;

private:
	int value;	//Valeur de la pi�ve
};