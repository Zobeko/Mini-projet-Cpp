#include "Unite.h"
#include "UnitePhysic.h"
#include <vector>
#include <SFML/Graphics.hpp>

// à enlever après
#include <iostream>
#include <myMain.cpp>

using namespace std;

//Le constructeur de UnitePhysic permet d'instancier une boite de collision et de lui donner une position et des dimensions
//Le constructeur de UnitePhysic appelle le constructeur de Unite ce qui permet d'instancier aussi un Unite, donc la partie graphique de l'élément
//avec la meme position, les mêmes dimensions
//Le parametre b2BodyDef bodyType sera précisé dans les constructeurs des 2 classes filles de UnitePhysic : Dynamic (bodyType = b2_dynamicBody) et
//Static (bodyType = b2_staticBody)
UnitePhysic::UnitePhysic(int _x, int _y, int _h, int _l, std::string textureName, b2BodyType bodyType) : Unite(_x, _y, _h, _l, textureName)
{
    //Crée une boite de collision et initialise sa position et son bodyType (static ou dynamic)
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(_x, _y);
    b2Body* body = world.CreateBody(&bodyDef);

    // Defini la forme de la boite de collision souhaitée (ici un rectangle) et initialise ses dimensions
    b2PolygonShape shape;
    shape.SetAsBox(_l, _h);

    // Défini les caractéristiques de notre boite de collision
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);

    box = body;
}

//Permet de récupéré la boite de collision
b2Body* UnitePhysic::getBox()
{
    return box;
}

//Permet de modifier la position de la boite de collision
void UnitePhysic::setXY(int _x, int _y)
{
	Unite::setXY(_x, _y);
    box->SetTransform(b2Vec2(_x, _y), 0);
}


