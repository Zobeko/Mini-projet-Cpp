#include "UnitePhysic.h"
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

//Le constructeur de UnitePhysic permet d'instancier une boite de collision et de lui donner une position et des dimensions
//Le constructeur de UnitePhysic appelle le constructeur de Unite ce qui permet d'instancier aussi un Unite, donc la partie graphique de l'élément
//avec la meme position, les mêmes dimensions
//Le parametre b2BodyDef bodyType sera précisé dans les constructeurs des 2 classes filles de UnitePhysic : Dynamic (bodyType = b2_dynamicBody) et
//Static (bodyType = b2_staticBody)
UnitePhysic::UnitePhysic(float _x, float _y, float _h, float _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2BodyType bodyType, b2World &world) : Unite(_x, _y, _h, _l, textureName, textDictionnary)
{
    //Crée une boite de collision et initialise sa position et son bodyType (static ou dynamic)
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;

    bodyDef.fixedRotation = true;
    bodyDef.position.Set((_x + (_l/2))/10.f, (_y - (_h/2))/10.f);
    b2Body* body = world.CreateBody(&bodyDef);


    // Defini la forme de la boite de collision souhaitée qui est un rectangle (on modifiera les fixtures dans les sous-classes si besoin) et initialise ses dimensions
    b2PolygonShape shape;    
    shape.SetAsBox((_l/2.f)/10.f, (_h/2.f)/10.f);

    // Défini les caractéristiques de notre boite de collision
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.9f;
    body->CreateFixture(&fixtureDef);

    box = body;
}

//Permet de récupéré la boite de collision
b2Body* UnitePhysic::getBox()
{
    return box;
}

//Permet de modifier la position de la boite de collision
void UnitePhysic::setXY(float _x, float _y)
{
	Unite::setXY(_x, _y);
    box->SetTransform(b2Vec2(_x/10.f, _y/10.f), 0);
}

//Destructeur qui doit détruire la boite physique
UnitePhysic::~UnitePhysic() {
    box->GetWorld()->DestroyBody(box);
}

