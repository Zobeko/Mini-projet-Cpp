#include "Clef.h"

#include "CollisionCallback.h"
#include <iostream>

using namespace std;

//Méthode servant à gérer les collisions, est appelée toute seule par box2D lors d'une collision
void CollisionCallback::BeginContact(b2Contact* contact) {
    b2Fixture* f1 = contact->GetFixtureA();
    b2Fixture* f2 = contact->GetFixtureB();

    b2Body* b1 = f1->GetBody();
    b2Body* b2 = f2->GetBody();

    void* o1 = b1->GetUserData();
    void* o2 = b1->GetUserData();

    CheckObjectColliding(o1, o2);
    CheckObjectColliding(o2, o1); //le joueur ne peut pas collisionne ravec lui-même : soit 1 des 2 sera activé parce que le joueur collisionne, soit aucun des deux car le joueur n'est pas impliqué
}

void CollisionCallback::CheckObjectColliding(void* & o1, void* & o2) {
    Joueur* j = static_cast<Joueur*>(o1);
    if (j)
    {
        // C'est que le premier pointeur renvoie au joueur
        // On check en premier si l'autre est un ennemi
        Ennemi* e = static_cast<Ennemi*>(o2);
        if (e) {
            // l'autre pointeur est vers un ennemi : on le dit à l'ennemi
            e->SetCollisionFlagOn();
        }
        else {
            // l'autre pointeur n'est pas vers un ennemi : normalement c'est vers un static (vu que y a pas d'autre dynamic que le joueur)
            Static* st = static_cast<Static*>(o2);
            // Comme on fait un cast on le vérifie
            if (st) {
                if (j->getY() >= st->getY() + st->getH() * 0.9) {
                    //mettre le joueur à grounded
                }
                else if (j->getY() + j->getH() > st->getY()) {
                    //mettre le joueur à walled
                }
            }
            else {
                cout << "Erreur lors du traitement de la collision : le joueur n'a ni touché un ennemi ni un static" << endl;
            }
        }
    }
}