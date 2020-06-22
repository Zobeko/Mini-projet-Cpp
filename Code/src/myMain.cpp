#include "myMain.h"

#include "pugixml.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "box2d/box2d.h"
#include "SceneManager.h"

#include <iostream>
#include <stdio.h>
#include <assert.h>




using namespace std;


int myMain()
{   
    //Création de la fenetre
    sf::RenderWindow window(sf::VideoMode(800, 600), "Medusé");
    window.setFramerateLimit(60);   //limite des fps

     

    // Mise en place des paramétres pour la simulation
    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    b2Vec2 gravity(0.0f, -250.0f);
    b2World world(gravity);
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

	// Dictionnaire conservant toutes les textures
    std::map<std::string, sf::Texture> textDictionnary;

	// Gestionnaire du jeu, c'est lui qui possède tous les éléments
    SceneManager manager(textDictionnary, world);

	//Mise en place de la musique 
	/*sf::Music musique;
	if (!musique.openFromFile("musique_base.mp3"))
		return -1;
    */


    // Game Loop
	while (window.isOpen())
	{

		//netoyage de la fenetre
		window.clear(sf::Color::White);

		//Evenement de fermeture de la fenetre
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// Evolution du monde physique (Avant les updates pour que les inputs du joueur correspondent à la situation)
		world.Step(timeStep, velocityIterations, positionIterations);

		//On vérifie les flags du SceneManager et si besoin on change de niveau
		manager.checkSalleSuivante(textDictionnary, world);
		manager.checkMort(textDictionnary, world, window);

		// Update des éléments
		manager.Update();

		// Dessin des différents sprites
		manager.draw(window);

		// Affichage des elements
		window.display();
	}
    return 0;
}

