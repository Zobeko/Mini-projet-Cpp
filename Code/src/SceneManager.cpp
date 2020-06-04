#include "SceneManager.h"
#include <vector>

#include "pugixml.hpp"
#include <SFML/Graphics.hpp>

// à enlever après
#include <iostream>

using namespace std;

// Constructeur
SceneManager::SceneManager() {
    idSalle = 0;
    chargerSalle();
}

// Dessine le jeu (appelé à chaque fin de frame)
void SceneManager::draw(sf::RenderWindow& window) {
    /*
    for (auto& i : tiles) {
        i.draw(window);
    }
    for (auto& i : pickUps) {
        i.draw(window);
    }
    for (auto& i : ennemis) {
        i.draw(window);
    }
    joueur.draw(window);
    */
}

// Méthode appelée à chaque frame pour mettre à jour l'état du jeu
void SceneManager::Update() {
    /*
    for (auto& i : pickUps) {
        i.Update(this);
    }
    for (auto& i : ennemis) {
        i.Update(this);
    }
    joueur.Update(this);
    */
}



#pragma region Méthodes liées à la manipulation des éléments du niveau
// Renvoie une référence vers le joueur
Joueur& SceneManager::getJoueur() {
    return joueur;
}

// Enlève un pickup donné du vector
void SceneManager::RemovePickUp(int idPickUp) {
    pickUps.erase(pickUps.begin + idPickUp);
}

// Bloque le jeu pendant un certain temps puis recharge la salle précédente
void SceneManager::tuerJoueur() {
    idSalle -= 1;
    if (idSalle < 0) {
        idSalle = 0;    //On vérifies que le joueur n'aille pas à une salle inexistante
    }
    //joueur => animation de mort + set velocity à 0
    //trouver un moyen d'afficher la fenetre
    chargerSalle();
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
    idSalle += 1;
    // Si le joueur a atteint le dernier niveau, on termine le jeu et affiche son temps total
    if (idSalle >= idLastSalle) {
        std::cout << "Fin du jeu ! Vous avez mis : " << std::to_string(timerSalle.getElapsedTime().asSeconds()) << endl;
        idSalle = idLastSalle;
        // faire finir le jeu
    }
    chargerSalle();
}

// Charge la salle correspondant à l'idSalle actuel
void SceneManager::chargerSalle() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("visage.xml");
    if (!result)
    {
        std::cerr << "Could not open file visage.xml" << std::endl;
    }
    else
    {
        // Attente pour qu'il y ait une coupure entre les niveaux (quand joueur meurt ou passe la porte
        int i = 0;
        while (i < delaiMort) {
            //Boucle pour mettre en pause le jeu
        }

        //... Constructions du niveau basée sur le xml et surtout les consctructeurs des différentes tiles et tout
    }
    timerSalle.restart();   // on redemmarre le timer de la salle
}

#pragma endregion

