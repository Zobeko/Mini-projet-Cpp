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
	void draw(sf::RenderWindow& window);
	void Update();

	Joueur& getJoueur();
	void tuerJoueur();
	void RemovePickUp(int idPickUp);

	void unLockDoor();
	bool getClefRecupere();
	void chargerSalleSuivante();
	void chargerSalle();

private:
	int idSalle;
	int idLastSalle = 1;
	int const delaiMort = 50;	//nombre de boucle while a faire pour "mettre en pause" le jeu lorsque le joueur meurt avant de redemmarer le niveau
	sf::Clock timerTotal;
	sf::Clock timerSalle;
	
	Joueur joueur;
	//vector<Ennemi> ennemis;
	//vector<Static> tiles;
	std::vector<std::unique_ptr<PickUp>> pickUps;
	bool clefRecupere = false;

	//musique
};