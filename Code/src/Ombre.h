#pragma once
#include "SceneManager.h"
#include "Unite.h"
#include "PickUp.h"

// Classe des Ombres. Lorsque la tête du joueur est dans l'ombre, il est protégé de Méduse et peut donc regarder dans les 2 directions sans craintes
class Ombre : public PickUp
{
public:
	Ombre(int _x, int _y, int _h, std::map<std::string, sf::Texture>& textDictionnary);
	bool intersect(Unite & _unite) override;							// Réécriture de la méthode de calcul d'intersection pour qu'il y ait interection si le point en haut au milieu de l'Unite est dans le triangle
	void Update(SceneManager& sceneManager, int iDpickUp) override;		// Réécriture de la méthode Update qui met le joueur à l'abri s'il est dans l'ombre
};

