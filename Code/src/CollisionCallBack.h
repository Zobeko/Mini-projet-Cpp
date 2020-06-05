#pragma once

#include "PickUp.h"
#include "SceneManager.h"


class CollisionCallback : public b2ContactListener
{
public:
    // Called when two fixtures begin to touch
    void BeginContact(b2Contact* contact);

    // Called when two fixtures cease to touch
    void EndContact(b2Contact* contact);

    void CheckObjectColliding(void* & o1, void* & o2);
};