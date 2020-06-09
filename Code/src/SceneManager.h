#pragma once
#include <vector>

#include <SFML/Graphics.hpp>
#include "pugixml.hpp"

#include "Joueur.h"
#include "PickUp.h"
#include "Ennemi.h"

class SceneManager
{
public:
	int nbPiece = 0;
	SceneManager(std::map<std::string, sf::Texture>& textDictionnary, b2World& world);
	void draw(sf::RenderWindow& window);
	void Update();
	void CheckTimer();

	std::unique_ptr<Joueur> &getJoueur();
	void checkMort(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world);
	void MettreJoueurAbri();
	void RemovePickUp(int idPickUp);
	void RemoveEnnemi(int idEnnemi);

	void unLockDoor();
	bool getClefRecupere();
	void checkSalleSuivante(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world);
	void chargerSalle(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world);
	void setLevelFlagTrue();
	void setDeathFlagTrue();

	void finirJeu();


private:
	sf::Sprite ImageDefond;
	sf::Texture texture;
	sf::Text textIDSalle;
	sf::Text textChronoSalle;
	sf::Text textPiece;
	sf::Font font;

	int idSalle;
	int idLastSalle = 2;		//Nombre de salles � change avant rendu
	int const delaiMort = 50;	//nombre de boucle while a faire pour "mettre en pause" le jeu lorsque le joueur meurt avant de redemmarer le niveau
	sf::Clock timerTotal;
	sf::Clock timerSalle;
	int tempsSalle;
	
	std::unique_ptr<Joueur> joueur;
	std::vector<std::unique_ptr<Ennemi>> ennemis;
	std::vector<std::unique_ptr<Static>> tiles;
	std::vector<std::unique_ptr<PickUp>> pickUps;
	bool clefRecupere = false;

	void AddStatic(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n);
	void AddEnnemi(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n);
	void AddPickup(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n);
	void ClearSalle();

	bool levelSuivantFlag = false;
	bool mortFlag = false;
	bool gameFlag = true; //se met � false pour indiquer que le jeu est fini

	//musique
};