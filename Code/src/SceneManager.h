#pragma once
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "pugixml.hpp"

#include "Joueur.h"
#include "PickUp.h"
#include "Ennemi.h"
#include "Ombre.h"

class SceneManager
{
public:
	int nbPiece = 0;//Nombre de pieces 
	SceneManager(std::map<std::string, sf::Texture>& textDictionnary, b2World& world);//Constructeur
	void draw(sf::RenderWindow& window);// Dessine le jeu (appelé à chaque fin de frame)
	void Update();// Méthode appelée à chaque frame pour mettre à jour l'état du jeu
	void CheckTimer();//Si le temps est ecoule, le joueur meurt

	std::unique_ptr<Joueur> &getJoueur();// Renvoie une référence vers le joueur
	void checkMort(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world, sf::Music& musique);// Bloque le jeu pendant un certain temps puis recharge la salle précédente
	void MettreJoueurAbri();//Mets joueur.ALabri à true
	//void RemovePickUp(int idPickUp);// Enlève un pickup donné du vector
	//void RemoveEnnemi(int idEnnemi);// Enlève un ennemi donné du vector + fait sauter le joueur (car si l'ennemi meurt c'est que le joueur lui saute dessus)

	void unLockDoor();// Débloque la porte (appelé lorsqu'une clef est attrapée)
	bool getClefRecupere();// Renvoie un bool indiquant si la porte est ouverte ou non
	void checkSalleSuivante(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world);// Méthode appelée lorsqu'on veut passer au niveau suivant
	void chargerSalle(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world);// Charge la salle correspondant à l'idSalle actuel
	void setLevelFlagTrue();// Mets le bool indiquant qu'il faut changer de niveau à true
	void setDeathFlagTrue();// Mets le bool indiquant que le joueur est mort à true

	void finirJeu();//Si on finit la derniere salle, on a finit le jeu


private:
	sf::Sprite ImageDefond;
	sf::Sprite ImageTuto;
	sf::Texture texture;
	sf::Texture textureTuto;
	sf::Text textIDSalle;
	sf::Text textChronoSalle;
	sf::Text textPiece;
	sf::Font font;

	int idSalle;
	int idLastSalle = 5;		//Nombre de salles à change avant rendu
	int const delaiMort = 50;	//nombre de boucle while a faire pour "mettre en pause" le jeu lorsque le joueur meurt avant de redemmarer le niveau
	sf::Clock timerTotal;
	sf::Clock timerSalle;
	int tempsSalle;
	
	std::unique_ptr<Joueur> joueur;
	std::vector<std::unique_ptr<Ennemi>> ennemis;
	std::vector<std::unique_ptr<Static>> tiles;
	std::vector<std::unique_ptr<PickUp>> pickUps;
	std::vector<std::unique_ptr<Ombre>> shadows;
	bool clefRecupere = false;


	void chargerSalleTiled(pugi::xml_node& node, std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world);
	int GetXtoPop(int i, int nbTileHoriz);
	int GetYtoPop(int i, int nbTileHoriz, int nbTileVert);
	void AddElementTiled(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n, int nbTileHoriz, int nbTileVert);// Ajoute tous les éléments sauf les ombres depuis un noeud XML
	void AddShadowTiled(std::map<std::string, sf::Texture>& textDictionnary, pugi::xml_node n, int nbTileHoriz, int nbTileVert);// Ajoutetoutes les ombres depuis un noeud XML
	
	void chargerSalleMain(pugi::xml_node& node, std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world);
	void AddStaticMain(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n);// Ajoute un Static depuis un noeud XML
	void AddEnnemiMain(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n);// Ajoute un Ennemi depuis un noeud XML
	void AddPickupMain(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n);// Ajoute un Pickup depuis un noeud XML
	
	void ClearSalle();//Efface tous les elements de la salle (pour en charger une autre)

	bool levelSuivantFlag = false;
	bool mortFlag = false;
	bool gameFlag = true; //se met à false pour indiquer que le jeu est fini

	void ComputeIDLastSalle();
	//musique
};