#include "Unite.h"
#include "UnitePhysic.h"
#include <vector>
#include <SFML/Graphics.hpp>

// � enlever apr�s
#include <iostream>
//#include "myMain.h"

using namespace std;

//Le constructeur de UnitePhysic permet d'instancier une boite de collision et de lui donner une position et des dimensions
//Le constructeur de UnitePhysic appelle le constructeur de Unite ce qui permet d'instancier aussi un Unite, donc la partie graphique de l'�l�ment
//avec la meme position, les m�mes dimensions
//Le parametre b2BodyDef bodyType sera pr�cis� dans les constructeurs des 2 classes filles de UnitePhysic : Dynamic (bodyType = b2_dynamicBody) et
//Static (bodyType = b2_staticBody)
UnitePhysic::UnitePhysic(float _x, float _y, float _h, float _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary, b2BodyType bodyType, b2World &world) : Unite(_x, _y, _h, _l, textureName, textDictionnary)
{
    std::cout << "Constructeur de UnitePhysic : (" << _h << ", " << _l << ")" << std::endl;
    //Cr�e une boite de collision et initialise sa position et son bodyType (static ou dynamic)
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;

    bodyDef.fixedRotation = true;
    bodyDef.position.Set((_x + (_l/2))/10.f, (_y - (_h/2))/10.f);
    b2Body* body = world.CreateBody(&bodyDef);
    std::cout << "BodyDef position : (" << bodyDef.position.x << ", " << bodyDef.position.y << ")" << std::endl;

    // Defini la forme de la boite de collision souhait�e (ici un rectangle) et initialise ses dimensions
    b2PolygonShape shape;

    
    shape.SetAsBox((_l/2.f)/10.f, (_h/2.f)/10.f); //_h=54 et _l=54 pour que ca marche bien pour le perso
    // D�fini les caract�ristiques de notre boite de collision
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.9f;
    body->CreateFixture(&fixtureDef);


    box = body;
    std::cout << "Box : (" << getBox()->GetPosition().x << ", " << getBox()->GetPosition().y << ")" << endl;
    std::cout << "Box origin : (" << getBox()->GetLocalPoint(b2Vec2 (0, 0)).x << ", " << getBox()->GetLocalPoint(b2Vec2(0, 0)).y << ")" << std::endl;
}

//Permet de r�cup�r� la boite de collision
b2Body* UnitePhysic::getBox()
{
    return box;
}

//Permet de modifier la position de la boite de collision
void UnitePhysic::setXY(int _x, int _y)
{
	Unite::setXY(_x, _y);
    //std::cout << "Unite : (" << Unite::getX() << ", " << Unite::getY() << ")" << endl;
    box->SetTransform(b2Vec2(_x/10.f, _y/10.f), 0);
    //std::cout << "Box : (" << getBox()->GetPosition().x << ", " << getBox()->GetPosition().y << ")" << endl;
    

}

UnitePhysic::~UnitePhysic() {
    box->GetWorld()->DestroyBody(box);
}

