#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

#include "Joueur.h"
#include "PickUp.h"

class SceneManager
{
public:
	int nbPiece = 0;
	SceneManager();
	void chargerSalle();
	void draw(sf::RenderWindow& window);
	void tuerJoueur();
	void Update();
	Joueur* getJoueur();

private:
	int idSalle;
	int const delaiMort = 50;	//nombre de boucle while a faire pour "mettre en pause" le jeu lorsque le joueur meurt avant de redemmarer le niveau
	sf::Clock timerTotal;
	sf::Clock timerSalle;
	
	Joueur joueur;
	//vector<Ennemi> ennemis;
	//vector<Static> tiles;
	//vector<PickUp> pickUps;
	bool cleRecupere = false;

	//musique
};