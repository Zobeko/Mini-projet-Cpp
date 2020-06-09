#include "SceneManager.h"
#include <vector>

#include "pugixml.hpp"
#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Clef.h"
#include "Porte.h"
#include "Ombre.h"

// � enlever apr�s
#include <iostream>

using namespace std;

// Constructeur
SceneManager::SceneManager(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world) {
    joueur = std::make_unique<Joueur>(_textDictionnary, _world);
    idSalle = 0;    

    chargerSalle(_textDictionnary, _world);
}

// Dessine le jeu (appel� � chaque fin de frame)
void SceneManager::draw(sf::RenderWindow& window) {
    for (auto& i : tiles) {
        i->draw(window);
        
    }
    for (auto& i : pickUps) {
        i->draw(window);
    }
    for (auto& i : ennemis) {
        i->draw(window);
    }
    joueur->draw(window);
    //std::cout << "Joueur Unite : (" << joueur->getX() << ", " << joueur->getY() << ")" << endl;
    //std::cout << "Joueur Box : (" << joueur->getBox()->GetPosition().x << ", " << joueur->getBox()->GetPosition().y << ")" << endl;
    
    //joueur->getBox()->GetFixtureList();
}

// M�thode appel�e � chaque frame pour mettre � jour l'�tat du jeu
void SceneManager::Update() {
    joueur->SetGroundedFlag(false);
    joueur->SetWalledFlag(false);
	joueur->SetALAbri(false); //On r�initialise le bool indiquant que le joueur est � l'abri ; s'il l'est toujours il le redeviendra � l'update des pickups
    
    
    for (int i = 0; i < pickUps.size(); i++) {
        pickUps[i]->Update(*this,i);
        //std::cout << joueur->walled << endl;
    }
    for (int i = 0; i < ennemis.size(); i++) {
        ennemis[i]->Update(*this, i);
    }
    //std::cout << "--------------------------------------------" << endl;
    /*for (auto& i : tiles) {
        i->Update(this);
        std::cout << joueur->grounded << endl;
    }*/
    for (int i = 0; i < tiles.size(); i++) {
        tiles[i]->Update(*this);
        //std::cout << joueur->walled << endl;
    }

    joueur->update();
    
    
}



#pragma region M�thodes li�es � la manipulation des �l�ments du niveau
// Renvoie une r�f�rence vers le joueur
std::unique_ptr<Joueur>& SceneManager::getJoueur() {
    return joueur;
}
// Bloque le jeu pendant un certain temps puis recharge la salle pr�c�dente
void SceneManager::checkMort(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world) {
    if (mortFlag) {
        idSalle -= 1;
        ClearSalle();
        if (idSalle < 0) {
            idSalle = 0;    //On v�rifies que le joueur n'aille pas � une salle inexistante
        }
        //joueur => animation de mort + set velocity � 0
        //trouver un moyen d'afficher la fenetre
        chargerSalle(_textDictionnary, _world);
    }
}
void SceneManager::MettreJoueurAbri() {
	joueur->SetALAbri(true);
}
// Enl�ve un pickup donn� du vector
void SceneManager::RemovePickUp(int idPickUp) {
    pickUps.erase(pickUps.begin() + idPickUp);
}
// Enl�ve un ennemi donn� du vector + fait sauter le joueur (car si l'ennemi meurt c'est que le joueur lui saute dessus)
void SceneManager::RemoveEnnemi(int idEnnemi) {
    cout << "Fly you fool ! (Faire sauter le joueur" << endl;
    ennemis.erase(ennemis.begin() + idEnnemi);
}
#pragma endregion

#pragma region M�thodes li�es � la porte et la clef
// D�bloque la porte (appel� lorsqu'une clef est attrap�e)
void SceneManager::unLockDoor() {
    clefRecupere = true;
}
// Renvoie un bool indiquant si la porte est ouverte ou non
bool SceneManager::getClefRecupere() {
    return clefRecupere;
}
// M�thode appel�e lorsqu'on veut passer au niveau suivant
void SceneManager::checkSalleSuivante(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world) {
    // On regarde s'il faut changer de salle
    if (levelSuivantFlag) {
        idSalle += 1;
        ClearSalle();
        // Si le joueur a atteint le dernier niveau, on termine le jeu et affiche son temps total
        if (idSalle >= idLastSalle) {
            std::cout << "Fin du jeu ! Vous avez mis : " << std::to_string(timerSalle.getElapsedTime().asSeconds()) << endl;
            idSalle = idLastSalle;
            // faire finir le jeu
        }
        else {
            chargerSalle(_textDictionnary, _world);
        }
    }   
}
// Mets le bool indiquant qu'il faut changer de niveau � true
void SceneManager::setLevelFlagTrue() {
    levelSuivantFlag = true;
}
// Mets le bool indiquant que le joueur est mort � true
void SceneManager::setDeathFlagTrue() {
    mortFlag = true;
    cout << "Joueur mort" << endl;
}
#pragma endregion

#pragma region M�thodes pour load un niveau
// Charge la salle correspondant � l'idSalle actuel
void SceneManager::chargerSalle(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world) {
    pugi::xml_document doc;
    std::string nomNoeud = "resources/Salle" + to_string(idSalle) + ".xml";
    //pugi::xml_parse_result result = doc.load_file("resources/Salle0.xml");
    pugi::xml_parse_result result = doc.load_file(nomNoeud.c_str());
    cout << nomNoeud << endl;
    if (!result)
    {
        std::cerr << "Erreur : impossible d'ouvrir le xml" << std::endl;
    }
    else
    {
        //Attente();

        
        pugi::xml_node node = doc.child("Salle"); // On recup�re le noeud XML de la salle � charger
        //pugi::xml_node node = doc.child("Salle0");

       
        joueur->setXY(node.child("Joueur").attribute("x").as_int(), node.child("Joueur").attribute("y").as_int());

        AddStatic(_textDictionnary, _world, node.child("Statics"));
        AddEnnemi(_textDictionnary, _world, node.child("Ennemis"));
        AddPickup(_textDictionnary, _world, node.child("PickUps"));

    }
    timerSalle.restart();   // on redemmarre le timer de la salle
    levelSuivantFlag = false;
    mortFlag = false;
}
// Ajoute un Static depuis un noeud XML
void SceneManager::AddStatic(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n) {
    for (pugi::xml_node _n : n.children("Pierre")) {
        cout << "Ajout d'une pierre" << endl;
        auto st = std::make_unique<Static>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), 32, 32, "TilePierre.png", textDictionnary, world);
        std::cout << "Pierre position : (" << _n.attribute("x").as_int() << ", " << _n.attribute("y").as_int() << ")" << std::endl;
        tiles.push_back(std::move(st));
    }
    // faire une boucle for pour les tiles plus g�n�rales, d�sign�es par Static et comportant tous les attributs
}
// Ajoute un Ennemi depuis un noeud XML
void SceneManager::AddEnnemi(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n) {
    for (pugi::xml_node _n : n.children("Ennemi")) {
        cout << "Ajout d'un ennemi" << endl;
        if (_n.attribute("mortel").as_int() == 1) {
            // L'ennemi est Mortel
            auto st = std::make_unique<Ennemi>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), _n.attribute("h").as_int(), _n.attribute("l").as_int(), "EnnemiMortel.png", textDictionnary, true, world);
            ennemis.push_back(std::move(st));
        }
        else {
            auto st = std::make_unique<Ennemi>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), _n.attribute("h").as_int(), _n.attribute("l").as_int(), "Ennemi.png", textDictionnary, false, world);
            ennemis.push_back(std::move(st));
        }
        
    }
}
// Ajoute un Pickup depuis un noeud XML
void SceneManager::AddPickup(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n) {
    for (pugi::xml_node _n : n.children("Piece")) {
        cout << "Ajout d'une piece" << endl;
        auto st = std::make_unique<Piece>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), textDictionnary, _n.attribute("value").as_int());
        pickUps.push_back(std::move(st));     
    }
    for (pugi::xml_node _n : n.children("Porte")) {
        cout << "Ajout d'une porte" << endl;
        auto st = std::make_unique<Porte>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), textDictionnary);
        pickUps.push_back(std::move(st));
    }
    for (pugi::xml_node _n : n.children("Clef")) {
        cout << "Ajout d'une clef" << endl;
        auto st = std::make_unique<Clef>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), textDictionnary);
        pickUps.push_back(std::move(st));
    }

}
// M�thode permettant de faire une petite attente
void SceneManager::Attente() {
    // Attente pour qu'il y ait une coupure entre les niveaux (quand joueur meurt ou passe la porte
    int i = 0;
    while (i < delaiMort) {
        //Boucle pour mettre en pause le jeu
        i++;
    }
}
// M�thode pour supprimer le contenu d'un niveau
void SceneManager::ClearSalle() {
    pickUps.erase(pickUps.begin(), pickUps.end());
    tiles.erase(tiles.begin(), tiles.end());
    ennemis.erase(ennemis.begin(), ennemis.end());
}
#pragma endregion





