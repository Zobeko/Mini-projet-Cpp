#include <gtest/gtest.h>
#include "Piece.h"
#include "Unite.h"
#include "box2d/box2d.h"
#include "Joueur.h"
#include "Static.h"

namespace myNameSpace {

TEST(TestUnitaire, TestIntersectPickUp) {
    std::map<std::string, sf::Texture> textDictionnary;

    Piece pieceTest(0,0, textDictionnary, 1);   // On peut utiliser Piece pour tester la methode intersect de la classe abstraite PickUp car elle n'est pas reecrite
    Unite UniteTest1(10, 0, 32, 32, "Pierre.png", textDictionnary);
    Unite UniteTest2(100, 0, 32, 32, "Pierre.png", textDictionnary);

    EXPECT_TRUE(pieceTest.intersect(UniteTest1));
    EXPECT_FALSE(pieceTest.intersect(UniteTest2));
}

TEST(TestUnitaire, TestGrounded) {
    b2Vec2 gravity(0.0f, -250.0f);
    b2World world(gravity);
    std::map<std::string, sf::Texture> textDictionnary;

    Joueur joueurGrounded(textDictionnary, world); //Les joueurs sont de base en (400, 400)
    Joueur joueurNotGrounded(textDictionnary, world);

    joueurGrounded.setXY(100, 64);
    joueurNotGrounded.setXY(400, 400);

    Static staticTest(100, 0, 32, 32, "Pierre.png", textDictionnary, world);//On ajoute une tile sous le joueurGrounded

    staticTest.CheckGrounded(joueurGrounded);
    staticTest.CheckGrounded(joueurNotGrounded);

    EXPECT_TRUE(joueurGrounded.getGrounded());
    EXPECT_FALSE(joueurNotGrounded.getGrounded());
}


}
