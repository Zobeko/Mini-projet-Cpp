#include "SceneManager.h"
#include <vector>

#include "pugixml.hpp"
#include <SFML/Graphics.hpp>

// � enlever apr�s
#include <iostream>

using namespace std;

SceneManager::SceneManager() {
    idSalle = 0;
    chargerSalle();
}



void SceneManager::chargerSalle() {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("visage.xml");
    if (!result)
    {
        std::cerr << "Could not open file visage.xml" << std::endl;
    }
    else
    {
        //... Constructions du niveau bas�e sur le xml et surtout les consctructeurs des diff�rentes tiles et tout
    }
}

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

void SceneManager::tuerJoueur() {
    idSalle -= 1;
    if (idSalle < 0) {
        idSalle = 0;    //On v�rifies que le joueur n'aille pas � une salle inexistante
    }
    //joueur => animation de mort + set velocity � 0
    //trouver un moyen d'afficher la fenetre
    int i = 0;
    while (i < delaiMort) {
        //Boucle pour mettre en pause le jeu
    }
    chargerSalle();
}

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