#include "myMain.h"

#include "pugixml.hpp"
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "SceneManager.h"

#include <iostream>
#include <stdio.h>
#include <assert.h>




using namespace std;


int myMain()
{   
    //Création de la fenetre
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tuto Jeu SFML");
    window.setFramerateLimit(60);   //limite des fps

    //Mise en place d'une horloge pour régler l'animation du joueur         //A mettre chez le joueur ?
    sf::Clock time;
    float fpsCount = 0,
        switchFps = 100,
        fpsSpeed = 500;

    

    // Mise en place des paramétres pour la simulation
    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    b2Vec2 gravity(0.0f, -200.0f);
    b2World world(gravity);
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    std::map<std::string, sf::Texture> textDictionnary;
    SceneManager manager(textDictionnary, world);

    


    // Game Loop
    while (window.isOpen())
    {
        #pragma region Update de la fenetre graphique
        //netoyage de la fenetre
        window.clear(sf::Color::White);

        //Evenement de fermeture de la fenetre
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                // nettoyer les variables globales
            }
        }
        #pragma endregion

        // Evolution du monde physique (Avant les updates pour que les inputs du joueur correspondent à la situation)
        world.Step(timeStep, velocityIterations, positionIterations);

        //On vérifie le flag du SceneManager et si besoin on change de niveau
        manager.checkSalleSuivante(textDictionnary, world);

        // Update des éléments
        manager.Update();
        

        // Dessin des différents sprites
        manager.draw(window);

        // Affichage des elements
        window.display();
    }

    return 0;
}

