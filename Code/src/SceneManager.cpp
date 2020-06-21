#include "SceneManager.h"
#include <vector>

#include "pugixml.hpp"
#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Clef.h"
#include "Porte.h"
#include "OmbreOld.h"
#include <iostream>

using namespace std;

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

#pragma region Initialisation
// Constructeur
SceneManager::SceneManager(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world) {
    ComputeIDLastSalle();
    if (!texture.loadFromFile("resources/BackGd.png")) {                                       // la ressource doit être dans build/MainLauncher, au niveau des .vcxproj
        cout << "Error loading texture : BackGd.png" << endl;
    }
    ImageDefond.setTexture(texture);
    ImageDefond.setPosition(0, 0);
    ImageDefond.setScale(WINDOW_WIDTH / 312.f, WINDOW_HEIGHT / 162.f);
    joueur = std::make_unique<Joueur>(_textDictionnary, _world);
    idSalle = 0;

    chargerSalle(_textDictionnary, _world);


    if (!font.loadFromFile("resources/Pixeled.ttf"))
    {
        cout << "Error loading font : Pixeled" << endl;
    }
    textIDSalle.setFont(font);
    textIDSalle.setCharacterSize(10);
    textIDSalle.setColor(sf::Color::White);
    textIDSalle.setPosition(10, 5);

    textChronoSalle.setFont(font);
    textChronoSalle.setCharacterSize(10);
    textChronoSalle.setColor(sf::Color::White);
    textChronoSalle.setPosition(10, 20);

    textPiece.setFont(font);
    textPiece.setCharacterSize(15);
    textPiece.setColor(sf::Color::Yellow);
    textPiece.setPosition(750, 10);
}
//Méthode pour calculer l'ID de la dernière salle => appelée dans le constructeur uniquement
void SceneManager::ComputeIDLastSalle() {
    pugi::xml_document doc;
    std::string nomNoeud;
    idLastSalle = 0;
    bool canOpen = true;
    while (canOpen) {
        nomNoeud = "resources/Salle" + to_string(idLastSalle) + ".xml";
        pugi::xml_parse_result result = doc.load_file(nomNoeud.c_str());
        cout << "Fichier " << nomNoeud << endl;
        if (!result)
        {
            canOpen = false;
        }
        else
            idLastSalle++;
    }
    std::cout << "IdLastSalle = " << idLastSalle << std::endl;
}
#pragma endregion




#pragma region Routine de jeu
// Dessine le jeu (appelé à chaque fin de frame)
void SceneManager::draw(sf::RenderWindow& window) {
    window.draw(ImageDefond);
    if (gameFlag) {
        for (auto& i : shadows) {
            i->draw(window);
        }
        for (auto& i : tiles) {
            i->draw(window);
        }
        for (auto& i : pickUps) {
            i->draw(window);
        }
        for (auto& i : ennemis) {
            i->draw(window);
        }
        joueur->draw(window);
        textIDSalle.setString("Salle : " + to_string(idSalle));
        window.draw(textIDSalle);
        textChronoSalle.setString("Temps Restant : " + to_string(tempsSalle - timerSalle.getElapsedTime().asSeconds()));
        window.draw(textChronoSalle);
        textPiece.setString(to_string(nbPiece) + "$");
        window.draw(textPiece);
    }
    else {
        // On affiche le score du joueur à savoir le temps qu'il a fait
        window.draw(textChronoSalle);
    }
}

// Méthode appelée à chaque frame pour mettre à jour l'état du jeu
void SceneManager::Update() {
    if (gameFlag) {
        joueur->SetGroundedFlag(false);
        joueur->SetWalledFlag(false);
        joueur->SetALAbri(false); //On réinitialise le bool indiquant que le joueur est à l'abri ; s'il l'est toujours il le redeviendra à l'update des pickups

        for (int i = 0; i < shadows.size(); i++) {
            shadows[i]->Update(*this);
        }
        for (int i = 0; i < pickUps.size(); i++) {
            pickUps[i]->Update(*this);
        }
        for (int i = 0; i < ennemis.size(); i++) {
            ennemis[i]->Update(*this);
        }
        for (int i = 0; i < tiles.size(); i++) {
            tiles[i]->Update(*this);
        }

        joueur->update(*this);

        CheckTimer();

        for (int i = 0; i < pickUps.size(); i++) {
            if (pickUps[i]->getDeleteFlag())
                pickUps.erase(pickUps.begin() + i);
        }
        for (int i = 0; i < ennemis.size(); i++) {
            if (ennemis[i]->getDeleteFlag())
                ennemis.erase(ennemis.begin() + i);
        }
    }
}
/*
// Enlève un pickup donné du vector
void SceneManager::RemovePickUp(int idPickUp) {
    pickUps.erase(pickUps.begin() + idPickUp);
}
// Enlève un ennemi donné du vector
void SceneManager::RemoveEnnemi(int idEnnemi) {
    ennemis.erase(ennemis.begin() + idEnnemi);
}*/
#pragma endregion





#pragma region Méthodes à la gestion de la mort du joueur
// Renvoie une référence vers le joueur
std::unique_ptr<Joueur>& SceneManager::getJoueur() {
    return joueur;
}
// Bloque le jeu pendant un certain temps puis recharge la salle précédente
void SceneManager::checkMort(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world) {
    if (mortFlag) {
        idSalle -= 1;
        ClearSalle();
        if (idSalle < 0) {
            idSalle = 0;    //On vérifies que le joueur n'aille pas à une salle inexistante
        }
        //joueur => animation de mort + set velocity à 0
        //trouver un moyen d'afficher la fenetre
        chargerSalle(_textDictionnary, _world);
    }
}
//Si le temps est ecoule, le joueur meurt
void SceneManager::CheckTimer() {
    if (tempsSalle - timerSalle.getElapsedTime().asSeconds() < 0) {
        mortFlag = true;
    }
}
//Mets joueur.ALabri à true
void SceneManager::MettreJoueurAbri() {
	joueur->SetALAbri(true);
}
#pragma endregion

#pragma region Méthodes liées à la porte et la clef
// Débloque la porte (appelé lorsqu'une clef est attrapée)
void SceneManager::unLockDoor() {
    clefRecupere = true;
}
// Renvoie un bool indiquant si la porte est ouverte ou non
bool SceneManager::getClefRecupere() {
    return clefRecupere;
}
// Méthode appelée lorsqu'on veut passer au niveau suivant
void SceneManager::checkSalleSuivante(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world) {
    // On regarde s'il faut changer de salle
    if (levelSuivantFlag) {
        idSalle += 1;
        ClearSalle();
        // Si le joueur a atteint le dernier niveau, on termine le jeu et affiche son temps total
        if (idSalle >= idLastSalle) {
            idSalle = idLastSalle;
            finirJeu();
        }
        else {
            chargerSalle(_textDictionnary, _world);
        }
    }   
}
// Mets le bool indiquant qu'il faut changer de niveau à true
void SceneManager::setLevelFlagTrue() {
    levelSuivantFlag = true;
}
// Mets le bool indiquant que le joueur est mort à true
void SceneManager::setDeathFlagTrue() {
    mortFlag = true;
    cout << "Joueur mort" << endl;
}
void SceneManager::finirJeu() {
    if (!texture.loadFromFile("resources/EcranFin.png")) {                                       // la ressource doit être dans build/MainLauncher, au niveau des .vcxproj
        cout << "Error loading texture : EcranFin.png" << endl;
    }
    ImageDefond.setTexture(texture);
    ImageDefond.setPosition(0, 0);
    ImageDefond.setScale(WINDOW_WIDTH / 200.f, WINDOW_HEIGHT / 150.f);   
    levelSuivantFlag = false;
    joueur.reset();
    textChronoSalle.setString(to_string(timerTotal.getElapsedTime().asSeconds()));
    textChronoSalle.setCharacterSize(30);
    textChronoSalle.setPosition(300, 550);
    gameFlag = false;
}
#pragma endregion

#pragma region Méthodes pour load un niveau

// Charge la salle correspondant à l'idSalle actuel
void SceneManager::chargerSalle(std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world) {
    pugi::xml_document doc;
    std::string nomNoeud = "resources/Salle" + to_string(idSalle) + ".xml";
    pugi::xml_parse_result result = doc.load_file(nomNoeud.c_str());
    cout << "Fichier " << nomNoeud << endl;
    if (!result)
    {
        std::cerr << "Erreur : impossible d'ouvrir le xml" << std::endl;
    }
    else
    {        
        pugi::xml_node node = doc.child("Salle"); // On recupère le noeud XML de la salle à charger
        if (node == NULL) {
            // Chargement d'une map éditée sur Tiled
            chargerSalleTiled(doc.child("map"), _textDictionnary, _world);
        }
        else {
            // Chargement d'une map écrite à la main
            chargerSalleMain(node, _textDictionnary, _world);
        }

    }
    timerSalle.restart();   // on redemmarre le timer de la salle
    levelSuivantFlag = false;
    mortFlag = false;
}
#pragma region Méthodes pour load un niveau avec les xml faits sur Tiled
// Fait le chargement de la salle quand 
void SceneManager::chargerSalleTiled(pugi::xml_node& node, std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world) {
    tempsSalle = node.child("properties").child("property").attribute("value").as_int();
    int nbTileHoriz = node.attribute("width").as_int();
    int nbTileVert = node.attribute("height").as_int();
    cout << "On ouvre une salle faite sur Tiled "<< nbTileHoriz<< " " << nbTileVert << " " << tempsSalle << endl;
    
    for (pugi::xml_node _l : node.children("layer")) {
        if (_l.attribute("id").as_int() == 1)
            AddElementTiled(_textDictionnary, _world, _l.child("data"), nbTileHoriz, nbTileVert);
        else
            AddShadowTiled(_textDictionnary, _l.child("data"), nbTileHoriz, nbTileVert);
    }
}
// Calcule la position depuis l'indice et le nb de tiles
int SceneManager::GetXtoPop(int i, int nbTileHoriz) {
    return (i % nbTileHoriz)*32;
}
int SceneManager::GetYtoPop(int i, int nbTileHoriz, int nbTileVert) {
    return (nbTileVert - (i / nbTileHoriz))*32;
}

// Ajoute les elements du niveau depuis le xml généré par Tiled
void SceneManager::AddElementTiled(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n, int nbTileHoriz, int nbTileVert) {
    int i = -1;  // indice de la tile regardée
    for (pugi::xml_node _n : n.children("tile")) {
        i++;
        if (_n.attribute("gid").as_int() == 1) {
            // Tile de pierre
            auto st = std::make_unique<Static>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert), 32, 32, "TilePierre.png", textDictionnary, world);
            tiles.push_back(std::move(st));
        }
        else if (_n.attribute("gid").as_int() == 2) {
            // Tile de mur
            auto st = std::make_unique<Static>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert), 32, 32, "TileBrique.png", textDictionnary, world);
            tiles.push_back(std::move(st));
        }
        else if (_n.attribute("gid").as_int() == 3) {
            // Porte
            auto st = std::make_unique<Porte>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert)+32, textDictionnary);
            pickUps.push_back(std::move(st));
        }
        else if (_n.attribute("gid").as_int() == 4) {
            // C'est le joueur
            joueur->init(GetXtoPop(i, nbTileHoriz)+32, GetYtoPop(i, nbTileHoriz, nbTileVert) + 32);
        }
        else if (_n.attribute("gid").as_int() == 5) {
            // Ennemi blindé
            auto st = std::make_unique<Ennemi>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert) + 32, 64, 64, "Ennemi.png", textDictionnary, world, 0, 0, 0, 0);
            ennemis.push_back(std::move(st));
        }
        else if (_n.attribute("gid").as_int() == 6) {
            // Ennemi exposé
            auto st = std::make_unique<Ennemi>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert) + 32, 64, 64, "EnnemiMortel.png", textDictionnary, world, 1, 0, 0, 0);
            ennemis.push_back(std::move(st));
        }
        else if (_n.attribute("gid").as_int() == 7) {
            // Ennemi Plafond
            std::cout << "Ennemi au plafond" << std::endl;
            auto st = std::make_unique<Ennemi>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert) + 32, 64, 64, "EnnemiPlaf.png", textDictionnary, world, 2, 0, 0, 0);
            ennemis.push_back(std::move(st));
        }        
        else if (_n.attribute("gid").as_int() == 8) {
            // Ennemi Wall
            auto st = std::make_unique<Ennemi>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert) + 32, 64, 64, "EnnemiWall.png", textDictionnary, world, 0, 2, 2, 0);
            ennemis.push_back(std::move(st));
        }
        else if (_n.attribute("gid").as_int() == 9) {
            // Ennemi Plateforme
            auto st = std::make_unique<Ennemi>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert) + 32, 64, 64, "EnnemiPlat.png", textDictionnary, world, 2, 0, 0, 0);
            ennemis.push_back(std::move(st));
        }
        //else if == 10
        else if (_n.attribute("gid").as_int() == 11) {
            // Clef
            auto st = std::make_unique<Clef>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert), textDictionnary);
            pickUps.push_back(std::move(st));
        }
        else if (_n.attribute("gid").as_int() == 12) {
            // Piece de 1
            auto st = std::make_unique<Piece>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert), textDictionnary, 1);
            pickUps.push_back(std::move(st));
        }
        else if (_n.attribute("gid").as_int() == 13) {
            // Piece de 5
            auto st = std::make_unique<Piece>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert), textDictionnary, 5);
            pickUps.push_back(std::move(st));
        }
        else if (_n.attribute("gid").as_int() == 14) {
            // Piece de 10
            auto st = std::make_unique<Piece>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert), textDictionnary, 10);
            pickUps.push_back(std::move(st));
        }
    }
}
// Ajoute les ombres du niveau depuis le xml généré par Tiled
void SceneManager::AddShadowTiled(std::map<std::string, sf::Texture>& textDictionnary, pugi::xml_node n, int nbTileHoriz, int nbTileVert) {
    int i = -1;  // indice de la tile regardée
    for (pugi::xml_node _n : n.children("tile")) {
        i++;
        if (_n.attribute("gid").as_int() == 15) {
            // Tile de pierre
            auto st = std::make_unique<Ombre>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert) + 32, "OmbreTriangTrue.png", textDictionnary);
            shadows.push_back(std::move(st));
        }
        else if (_n.attribute("gid").as_int() == 16) {
            // Tile de pierre
            auto st = std::make_unique<Ombre>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert)+32, "OmbreRect.png", textDictionnary);
            shadows.push_back(std::move(st));
        }
        else if (_n.attribute("gid").as_int() == 17) {
            // Tile de pierre
            auto st = std::make_unique<Ombre>(GetXtoPop(i, nbTileHoriz), GetYtoPop(i, nbTileHoriz, nbTileVert) + 32, "OmbreTriangFalse.png", textDictionnary);
            shadows.push_back(std::move(st));
        }
    }
}
#pragma endregion

#pragma region Méthodes pour load un niveau avec les xml à la main
// Fait le chargement de la salle quand 
void SceneManager::chargerSalleMain(pugi::xml_node& node, std::map<std::string, sf::Texture>& _textDictionnary, b2World& _world) {
    tempsSalle = node.child("Temps").attribute("t").as_int();
    cout << tempsSalle << endl;

    joueur->init(node.child("Joueur").attribute("x").as_int(), node.child("Joueur").attribute("y").as_int());

    AddStaticMain(_textDictionnary, _world, node.child("Statics"));
    AddEnnemiMain(_textDictionnary, _world, node.child("Ennemis"));
    AddPickupMain(_textDictionnary, _world, node.child("PickUps"));
}
// Ajoute un Static depuis un noeud XML
void SceneManager::AddStaticMain(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n) {
    for (pugi::xml_node _n : n.children("Pierre")) {
        auto st = std::make_unique<Static>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), 32, 32, "TilePierre.png", textDictionnary, world);
        tiles.push_back(std::move(st));
    }
    // faire une boucle for pour les tiles plus générales, désignées par Static et comportant tous les attributs
}
// Ajoute un Ennemi depuis un noeud XML
void SceneManager::AddEnnemiMain(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n) {
    for (pugi::xml_node _n : n.children("EnnemiBlinde")) {
        auto st = std::make_unique<Ennemi>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), _n.attribute("h").as_int(), _n.attribute("l").as_int(), "Ennemi.png", textDictionnary, world, 0,0,0,0);
        ennemis.push_back(std::move(st));        
    }
    for (pugi::xml_node _n : n.children("EnnemiExpose")) {
        auto st = std::make_unique<Ennemi>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), _n.attribute("h").as_int(), _n.attribute("l").as_int(), "EnnemiMortel.png", textDictionnary, world, 1, 0, 0, 0);
        ennemis.push_back(std::move(st));
    }
    for (pugi::xml_node _n : n.children("EnnemiPlat")) {
        auto st = std::make_unique<Ennemi>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), _n.attribute("h").as_int(), _n.attribute("l").as_int(), "EnnemiPlat.png", textDictionnary, world, 2, 0, 0, 0);
        ennemis.push_back(std::move(st));
    }
    for (pugi::xml_node _n : n.children("EnnemiWall")) {
        auto st = std::make_unique<Ennemi>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), _n.attribute("h").as_int(), _n.attribute("l").as_int(), "EnnemiWall.png", textDictionnary, world, 0, 2, 2, 0);
        ennemis.push_back(std::move(st));
    }
}
// Ajoute un Pickup depuis un noeud XML
void SceneManager::AddPickupMain(std::map<std::string, sf::Texture>& textDictionnary, b2World& world, pugi::xml_node n) {
    for (pugi::xml_node _n : n.children("Piece")) {
        auto st = std::make_unique<Piece>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), textDictionnary, _n.attribute("value").as_int());
        pickUps.push_back(std::move(st));     
    }
    for (pugi::xml_node _n : n.children("Porte")) {
        auto st = std::make_unique<Porte>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), textDictionnary);
        pickUps.push_back(std::move(st));
    }
    for (pugi::xml_node _n : n.children("Clef")) {
        auto st = std::make_unique<Clef>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), textDictionnary);
        pickUps.push_back(std::move(st));
    }
    for (pugi::xml_node _n : n.children("Ombre")) {
        auto st = std::make_unique<OmbreOld>(_n.attribute("x").as_int(), _n.attribute("y").as_int(), _n.attribute("h").as_int(), textDictionnary);
        pickUps.push_back(std::move(st));
    }
}
#pragma endregion


// Méthode pour supprimer le contenu d'un niveau
void SceneManager::ClearSalle() {
    pickUps.erase(pickUps.begin(), pickUps.end());
    tiles.erase(tiles.begin(), tiles.end());
    ennemis.erase(ennemis.begin(), ennemis.end());
    shadows.erase(shadows.begin(), shadows.end());
    clefRecupere = false;
}
#pragma endregion





