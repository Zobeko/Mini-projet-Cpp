#include "SceneManager.h"
#include <vector>

#include "pugixml.hpp"
#include <SFML/Graphics.hpp>

// à enlever après
#include <iostream>

using namespace std;

// Constructeur
SceneManager::SceneManager(std::map<std::string, sf::Texture>& textDictionnary, b2World& world) {
    joueur = std::make_unique<Joueur>(textDictionnary, world);
    idSalle = 0;
    chargerSalle(textDictionnary, world);
}

// Dessine le jeu (appelé à chaque fin de frame)
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
    std::cout << "Joueur Unite : (" << joueur->getX() << ", " << joueur->getY() << ")" << endl;
    std::cout << "Joueur Box : (" << joueur->getBox()->GetPosition().x << ", " << joueur->getBox()->GetPosition().y << ")" << endl;
    //joueur->getBox()->GetFixtureList();
}

// Méthode appelée à chaque frame pour mettre à jour l'état du jeu
void SceneManager::Update(std::map<std::string, sf::Texture>& textDictionnary, b2World& world) {
	joueur->SetALAbri(false); //On réinitialise le bool indiquant que le joueur est à l'abri ; s'il l'est toujours il le redeviendra à l'update des pickups
    /*
    for (auto& i : pickUps) {
        i.Update(this);
    }
    
    for (int i = 0; i < ennemis.size(); i++) {
        ennemis[i]->Update(*this, i);
    }*/
    joueur->update();
    
}



#pragma region Méthodes liées à la manipulation des éléments du niveau
// Renvoie une référence vers le joueur
Joueur& SceneManager::getJoueur() {
    return *joueur;
}
// Bloque le jeu pendant un certain temps puis recharge la salle précédente
void SceneManager::tuerJoueur() {
    /*
    idSalle -= 1;
    if (idSalle < 0) {
        idSalle = 0;    //On vérifies que le joueur n'aille pas à une salle inexistante
    }
    //joueur => animation de mort + set velocity à 0
    //trouver un moyen d'afficher la fenetre
    chargerSalle(textDictionnary, world);
    */
}
void SceneManager::MettreJoueurAbri() {
	joueur->SetALAbri(true);
}
// Enlève un pickup donné du vector
void SceneManager::RemovePickUp(int idPickUp) {
    pickUps.erase(pickUps.begin() + idPickUp);
}
// Enlève un ennemi donné du vector
void SceneManager::RemoveEnnemi(int idEnnemi) {
    ennemis.erase(ennemis.begin() + idEnnemi);
}
#pragma endregion

#pragma region Méthodes liées à la porte et la clef
// Débloque la porte (appelé lorsqu'une clef est attrapée)
void SceneManager::unLockDoor() {
    clefRecupere = true;
}
// Renvoie un bool indiquant si la porte est ouverte ou non
bool SceneManager::getClefRecupere() {
    return clefRecupere;
}
void SceneManager::chargerSalleSuivante() {
    /*
    idSalle += 1;
    // Si le joueur a atteint le dernier niveau, on termine le jeu et affiche son temps total
    if (idSalle >= idLastSalle) {
        std::cout << "Fin du jeu ! Vous avez mis : " << std::to_string(timerSalle.getElapsedTime().asSeconds()) << endl;
        idSalle = idLastSalle;
        // faire finir le jeu
    }
    chargerSalle(textDictionnary, world);
    */
}
#pragma endregion

#pragma region Méthodes pour load un niveau
// Charge la salle correspondant à l'idSalle actuel
void SceneManager::chargerSalle(std::map<std::string, sf::Texture>& textDictionnary, b2World& world) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("Resources/Salle.xml");
    if (!result)
    {
        std::cerr << "Erreur : impossible d'ouvrir le xml" << std::endl;
    }
    else
    {
        //Attente();

        std::string nomNoeud = "Salle" + to_string(idSalle);
        //pugi::xml_node node = doc.child(nomNoeud); // On recupère le noeud XML de la salle à charger
        pugi::xml_node node = doc.child("Salle0");

       
        joueur->setXY(node.child("Joueur").attribute("x").as_int(), node.child("Joueur").attribute("y").as_int());

        AddStatic(textDictionnary, world, node.child("Statics"));
        AddEnnemi(textDictionnary, world, node.child("Ennemis"));
        AddPickup(textDictionnary, world, node.child("PickUps"));

    }
    timerSalle.restart();   // on redemmarre le timer de la salle
}
// Ajoute un Static depuis un noeud XML
void SceneManager::AddStatic(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n) {
    for (pugi::xml_node _n : n.children("Pierre")) {
        cout << "Ajout d'une pierre" << endl;
        auto st = std::make_unique<Static>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), 32, 32, "TilePierre.png", textDictionnary, world);
        std::cout << "Pierre position : (" << _n.attribute("x").as_int() << ", " << _n.attribute("y").as_int() << ")" << std::endl;
        tiles.push_back(std::move(st));
    }
    // faire une boucle for pour les tiles plus générales, désignées par Static et comportant tous les attributs
}
// Ajoute un Ennemi depuis un noeud XML
void SceneManager::AddEnnemi(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n) {
    for (pugi::xml_node _n : n.children("Ennemi")) {
        cout << "Ajout d'un ennemi" << endl;
        auto st = std::make_unique<Ennemi>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), _n.attribute("h").as_int(), _n.attribute("l").as_int(), "ennemi.png", textDictionnary, _n.attribute("mortel").as_int(), world);
        ennemis.push_back(std::move(st));
    }
}
// Ajoute un Pickup depuis un noeud XML
void SceneManager::AddPickup(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n) {
    for (pugi::xml_node _n : n.children("Piece")) {
        cout << "Ajout d'une piece" << endl;
        if (_n.attribute("value").as_int() == 1) {
            auto st = std::make_unique<PickUp>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), 32, 32, "Piece1.png", textDictionnary);
            pickUps.push_back(std::move(st));
        }
        else if (_n.attribute("value").as_int() == 5) {
            auto st = std::make_unique<PickUp>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), 32, 32, "Piece5.png", textDictionnary);
            pickUps.push_back(std::move(st));
        }
        else if (_n.attribute("value").as_int() == 10) {
            auto st = std::make_unique<PickUp>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), 32, 32, "Piece10.png", textDictionnary);
            pickUps.push_back(std::move(st));
        }
        
    }
    for (pugi::xml_node _n : n.children("Porte")) {
        cout << "Ajout d'une porte" << endl;
        auto st = std::make_unique<PickUp>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), 64, 64, "Porte.png", textDictionnary);
        pickUps.push_back(std::move(st));
    }
    for (pugi::xml_node _n : n.children("Clef")) {
        cout << "Ajout d'une clef" << endl;
        auto st = std::make_unique<PickUp>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), 32, 32, "Clef.png", textDictionnary);
        pickUps.push_back(std::move(st));
    }

}
// Méthode permettant de faire une petite attente
void SceneManager::Attente() {
    // Attente pour qu'il y ait une coupure entre les niveaux (quand joueur meurt ou passe la porte
    int i = 0;
    while (i < delaiMort) {
        //Boucle pour mettre en pause le jeu
        i++;
    }
}
#pragma endregion





