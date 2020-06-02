#include "Unite.h"
#include "UnitePhysic.h"
#include <vector>
#include <SFML/Graphics.hpp>

// à enlever après
#include <iostream>
#include <myMain.cpp>

using namespace std;

UnitePhysic::UnitePhysic(int _x, int _y, int _h, int _l, b2BodyType bodyType) {
    b2BodyDef bodyDef;
    bodyDef.type = bodyType;
    bodyDef.position.Set(_x, _y);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape shape;
    shape.SetAsBox(_l, _h);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;


    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);

    box = body;
}

b2Body* UnitePhysic::getBox()
{
    return box;
}

void UnitePhysic::setXY(int _x, int _y)
{
    box->SetTransform(b2Vec2(_x, _y), 0);
}


