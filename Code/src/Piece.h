#pragma once

#include "SceneManager.h"
#include "Unite.h"
#include "PickUp.h"

// Classe des pièces. Lorsqu'elles sont ramassées elles augmentent le compteur de pièce d'une certaine valeur
// Le nombre de pièce ne change rien au gameplay
class Piece : public PickUp
{
public:
	Piece(int _x, int _y, std::map<std::string, sf::Texture>& textDictionnary, int _value);
	void Update(SceneManager& sceneManager) override;					// La pièce doit incrémenter le compteur de pièce de sa valeur + se détruire si il y a contact

private:
	int value;	//Valeur de la pièce
};