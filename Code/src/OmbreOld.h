#pragma once
#include "SceneManager.h"
#include "Unite.h"
#include "PickUp.h"

// [Depr�ci�e] Ancienne lasse des Ombres. Lorsque la t�te du joueur est dans l'ombre, il est prot�g� de M�duse et peut donc regarder dans les 2 directions sans craintes
// Toujours existante pour assurer la lecture des anciens fichiers XML si besoin
class OmbreOld : public PickUp
{
public:
	OmbreOld(int _x, int _y, int _h, std::map<std::string, sf::Texture>& textDictionnary);
	bool intersect(Unite & _unite) override;							// R��criture de la m�thode de calcul d'intersection pour qu'il y ait interection si le point en haut au milieu de l'Unite est dans le triangle
	void Update(SceneManager& sceneManager) override;		// R��criture de la m�thode Update qui met le joueur � l'abri s'il est dans l'ombre
};

