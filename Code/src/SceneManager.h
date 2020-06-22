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
	int nbPiece = 0;	//Nombre de pieces 
	SceneManager(std::map<std::string, sf::Texture>& textDictionnary, b2World& world);	//Constructeur
	void draw(sf::RenderWindow& window);	// Dessine le jeu (appel� � chaque fin de frame)
	void Update();		// M�thode appel�e � chaque frame pour mettre � jour l'�tat du jeu
	void CheckTimer();	//Si le temps de la salle est ecoul�, le joueur meurt

	std::unique_ptr<Joueur> &getJoueur();	// Renvoie une r�f�rence vers le joueur
	void checkMort(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world, sf::RenderWindow& window, sf::Music & musique);	// Bloque le jeu pendant un certain temps puis recharge la salle pr�c�dente en relan�ant la musique
	void MettreJoueurAbri();		//Mets joueur.ALabri � true

	void unLockDoor();				// D�bloque la porte (appel� lorsqu'une clef est attrap�e)
	bool getClefRecupere();			// Renvoie un bool indiquant si la porte est ouverte ou non
	void checkSalleSuivante(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world);		// M�thode appel�e lorsqu'on veut passer au niveau suivant
	void chargerSalle(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world);			// Charge la salle correspondant � l'idSalle actuel (doit �tre chang� avant l'appel � la fonction pour changer la salle)
	void setLevelFlagTrue();	// Mets le bool indiquant qu'il faut changer de niveau � true
	void setDeathFlagTrue();	// Mets le bool indiquant que le joueur est mort � true

	void finirJeu();			//Si on finit la derniere salle, on a finit le jeu


private:
	// Elements de SFML Graphics pour avoir le fond, les textes de HUD, l'image de tuto et la police des textes
	sf::Sprite ImageDefond;
	sf::Sprite ImageTuto;
	sf::Texture texture;
	sf::Texture textureTuto;
	sf::Text textIDSalle;
	sf::Text textChronoSalle;
	sf::Text textPiece;
	sf::Font font;

	// Elements de SFML Audio pour avoir les bruitages
	sf::SoundBuffer bufferClef;
	sf::SoundBuffer bufferMort;
	sf::SoundBuffer bufferCoin;
	sf::SoundBuffer bufferKill;
	sf::SoundBuffer bufferDoor;
	sf::Sound soundClef;
	sf::Sound soundMort;
	sf::Sound soundCoin;
	sf::Sound soundKill;
	sf::Sound soundDoor;

	int idSalle;				//Identifiant de la salle actuel
	int idLastSalle;			//Nombre de salles maximales, calcul� dans le constructeur
	void ComputeIDLastSalle();	//Calcule le nombre de salles max en fonction du nombre de fichiers XML que le programme arrive � ouvrir
	int const delaiMort = 50;	//nombre de boucle while a faire pour "mettre en pause" le jeu lorsque le joueur meurt avant de redemmarer le niveau
	sf::Clock timerTotal;		//Timer comptant le temps que mets le joueur � finir le jeu
	sf::Clock timerTransition;	//Timer pour mettre une pause entre les transitions de salles
	void attenteChangementSalle();	//M�thodes � appeler pour attendre pendant les transitions de salles
	int tempsAttente = 250;		//Temps � attendre pendant les transitions (en millisec)
	sf::Clock timerSalle;		//Timer pour compter le temps pass� dans une salle et donc faire un compte � rebours
	int tempsSalle;				//Temps donn� au joueur pour finir la salle (en sec)
	
	std::unique_ptr<Joueur> joueur;						//Pointeur du joueur
	std::vector<std::unique_ptr<Ennemi>> ennemis;		//Vecteur contenant les ennemis
	std::vector<std::unique_ptr<Static>> tiles;			//Vecteur contenant les statics
	std::vector<std::unique_ptr<PickUp>> pickUps;		//Vecteur contenant les pickups
	std::vector<std::unique_ptr<Ombre>> shadows;		//Vecteur contenant les ombres
	bool clefRecupere = false;							//Indique si la clef a �t� r�cup�r�e

	// M�thodes pour charger la salle � partir d'un fichier XML fait sur Tiled
	void chargerSalleTiled(pugi::xml_node& node, std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world);
	int GetXtoPop(int i, int nbTileHoriz);
	int GetYtoPop(int i, int nbTileHoriz, int nbTileVert);
	void AddElementTiled(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n, int nbTileHoriz, int nbTileVert);// Ajoute tous les �l�ments sauf les ombres depuis un noeud XML
	void AddShadowTiled(std::map<std::string, sf::Texture>& textDictionnary, pugi::xml_node n, int nbTileHoriz, int nbTileVert);// Ajoutetoutes les ombres depuis un noeud XML
	
	// M"thodes pour charger la salle � partir des anciens XML faits � la main
	void chargerSalleMain(pugi::xml_node& node, std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world);
	void AddStaticMain(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n);// Ajoute un Static depuis un noeud XML
	void AddEnnemiMain(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n);// Ajoute un Ennemi depuis un noeud XML
	void AddPickupMain(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n);// Ajoute un Pickup depuis un noeud XML
	
	void ClearSalle();				//M�thode pour effacer tous les elements de la salle (pour en charger une autre)

	bool levelSuivantFlag = false;	//se met � true pour passer � la salle suivante
	bool mortFlag = false;			//se met � true pour tuer le joueur
	bool gameFlag = true;			//se met � false pour indiquer que le jeu est fini
};