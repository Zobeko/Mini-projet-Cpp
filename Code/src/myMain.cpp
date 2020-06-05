#include "myMain.h"
#include "pugixml.hpp"
#include <SFML/Graphics.hpp>

#include "shapeEx.h"
#include <iostream>

#include "box2d/box2d.h"
#include <stdio.h>
#include <assert.h>


using namespace std;

//Variables globales

// Define the gravity vector.
b2Vec2 gravity(0.0f, -10.0f);

// Construct a world object, which will hold and simulate the rigid bodies.
b2World world(gravity);

int persoDimension = 64*2;
sf::CircleShape cercle;
sf::RectangleShape rect;
sf::Vector2i positionSouris;
sf::Sprite persoSprite;
enum persoEtat {Marche, Mirroir, Autre};    // indique l'état du joueur pour pouvoir l'animer en accord ; Il faudra modifier la sheet pour qu'il y ait toujours 3 images même si pas d'animation (3 images identiques)
sf::Vector2i anim(1, Marche);
bool updateFps = true;
const int VitesseFrame = 60;

//Méthode artisanale pour réduire la vitesse d'animation
int animDelayIndice = 0;
const int animDelay = 10;
bool direction = false; //false : vers la gauche, true : vers la droite

int speed = 4;
const int baseSpeed = 4;

// Utiliser un dictionnaire pour les textures !!!


void CapPosition() {
    if (persoSprite.getPosition().x <= 0) {
        persoSprite.setPosition(0, persoSprite.getPosition().y);
    }
    if (persoSprite.getPosition().y <= 0) {
        persoSprite.setPosition(persoSprite.getPosition().x, 0);
    }
}
void GestionInputs() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        persoSprite.move(0, -speed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        persoSprite.move(0, speed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        persoSprite.move(-speed, 0);
        direction = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        persoSprite.move(speed, 0);
        direction = true;
       
    }
    else {
        //on ne joue pas l'animation :
        updateFps = false;
    }

    CapPosition();
}
void GestionInputsRun() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        speed = 2 * baseSpeed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        anim.y = Mirroir;
        speed = -0.5 * baseSpeed;
    }
    else {
        anim.y = Marche;
        speed = baseSpeed;
    }
}
/*
void GestionAnimation(sf::Texture persoTexture) {
    anim.x++; // on avance dans l'animation du pt de bue temporel
    //if (anim.x >= 3) anim.x = 0;
    if (anim.x * 64 >= persoTexture.getSize().x) anim.x = 0;

    persoSprite.setTextureRect(sf::IntRect(anim.x * 64, anim.y * 64, 64, 64));
}
*/
void dessin(sf::RenderWindow & win) {
    win.draw(persoSprite);
}










int myMain()
{   
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tuto Jeu SFML");
#pragma region Initialisation de la fenetre avec SFML
    //Variables posant un problème quand globales
    
    sf::Texture persoTexture;

    //Ouverture de la fenetre
    //window.create(sf::VideoMode(800, 600), "Tuto Jeu SFML");

    //placement de la fenetre
        //window.setPosition(sf::Vector2i(0, 0));

    //limite des fps
    window.setFramerateLimit(60);

    /*
    //Création d'un cercle simple
    cercle.setFillColor(sf::Color(100, 250, 20));
    cercle.setRadius(50);
    cercle.setPosition(100, 100);
    cercle.setOutlineColor(sf::Color::White);
    cercle.setOutlineThickness(10);

    //Création d'un recangle en utilisant un .h
    rect = PB_Rect(50,50,60,80);
    */

    //Mise en place d'une horloge pour régler l'animation du joueur
    sf::Clock time;
    float fpsCount = 0,
        switchFps = 100,
        fpsSpeed = 500;


    //Chargement du sprite du joueur
    if (!persoTexture.loadFromFile("resources/Hero.png")) {                                       // la ressource doit être dans build/MainLauncher, au niveau des .vcxproj
        cout << "Error loading hero texture" << endl;
    }
    /*if (!persoTexture.loadFromFile("Hero.png", sf::IntRect(64,0,64,64))) {           // la ressource doit être dans build/MainLauncher, au niveau des .vcxproj
        cout << "Error loading hero texture" << endl;
    }
    */
    persoTexture.setSmooth(true);
    persoSprite.setTexture(persoTexture);

#pragma endregion
#pragma region Initialisation du monde avec Box2D
    

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Prepare for simulation. Typically we use a time step of 1/60 of a
    // second (60Hz) and 10 iterations. This provides a high quality simulation
    // in most game scenarios.
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
#pragma endregion
#pragma region Création du Dynamic Body du joueur
    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();
#pragma endregion


    //
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
            }
        }
        #pragma endregion

        
        /*
        //Gestion des inputs clavier
        GestionInputsRun();
        updateFps = true;   //par defaut on joue l'animation
        GestionInputs();
            //Exemple d'input de souris
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            positionSouris = sf::Mouse::getPosition(window);
            std::cout << "Mx : " << positionSouris.x << " - My : " << positionSouris.y << endl;
        }
        */

        #pragma region Evolution du monde physique
        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        world.Step(timeStep, velocityIterations, positionIterations);

        // Now print the position and angle of the body.

        body->SetTransform(b2Vec2(4, 4), 0);
        position = body->GetPosition();
        angle = body->GetAngle();

        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
        #pragma endregion

        //Mis à jour de la position du joueur
        persoSprite.setPosition(position.x, 500-position.y*100);



        //Gestion de l'Animation
        if (updateFps == true) {
            if (time.getElapsedTime().asMilliseconds() >= VitesseFrame * baseSpeed / abs(speed)) {  // * baseSpeed / abs(speed) : permet d'avoir une vitesse différente pour la course et le bouclier
                anim.x++;
                if (anim.x  >= 3)
                    anim.x = 0;
                time.restart();

            }
        }

        //GestionAnimation(persoTexture);
        /*if (updateFps) {
            fpsCount += fpsSpeed * time.restart().asSeconds();
        }
        else {
            fpsCount = 0;
        }

        if (fpsCount >= switchFps*baseSpeed/abs(speed)) {
            fpsCount = 0;
            anim.x++;
            if (anim.x >= 3) anim.x = 0;
        }*/
        /* Implementation de la Méthode artisanale pour régler les fps de l'anim
        animDelayIndice++;
        if (animDelayIndice > animDelay) {
            anim.x++;                   // on avance dans l'animation du pt de bue temporel
            animDelayIndice = 0;
        }
        if (anim.x >= 3) anim.x = 0;    //Bouclage de l'animation
        */
        //if (anim.x * 64 >= persoTexture.getSize().x) anim.x = 0;
        if (direction) persoSprite.setTextureRect(sf::IntRect((anim.x +1)* persoDimension, anim.y * persoDimension, -persoDimension, persoDimension));
        else persoSprite.setTextureRect(sf::IntRect(anim.x * persoDimension, anim.y * persoDimension, persoDimension, persoDimension));
        

        //Ajout des elements
        //window.draw(cercle);
        //window.draw(rect);
        
        //window.draw(persoSprite);
        dessin(window);

        //Affichage des elements
        window.display();
    }

    return 0;
}

