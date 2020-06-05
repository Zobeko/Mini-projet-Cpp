#include "Clef.h"

#include "CollisionCallback.h"

using namespace std;

//Méthode servant à gérer les collisions, est appelée toute seule par box2D lors d'une collision
void CollisionCallback::BeginContact(b2Contact* contact) {
    b2Fixture* f1 = contact->GetFixtureA();
    b2Fixture* f2 = contact->GetFixtureB();

    b2Body* b1 = f1->GetBody();
    b2Body* b2 = f2->GetBody();

    void* o1 = b1->GetUserData();
    void* o2 = b1->GetUserData();

    if (true) {
        int a;
    }
}