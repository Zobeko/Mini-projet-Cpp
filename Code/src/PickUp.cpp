#include "PickUp.h"
#include "Unite.h"
#include "Joueur.h"
#include "SceneManager.h"

using namespace std;

// Contructeur : doit simplement appeler celui de la classe de base Unite
PickUp::PickUp(int _x, int _y, int _h, int _l, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary) : Unite(_x, _y, _h, _l, textureName, textDictionnary)
{
}

// Calcule s'il y a intersection avec _unite : renvoie un bool
bool PickUp::intersect(Unite & _unite) {
	//test sur la hauteur :
		// est-ce qu'il y a correspondance par le dessus (unite plus haut que this)
	bool uniteInterDessus = (getY() - getH() < _unite.getY()) & (getY() > _unite.getY() - _unite.getH());
		// est-ce qu'il y a correspondance par le dessous (unite plus bas que this)
	bool uniteInterDessous = (_unite.getY() - _unite.getH() < getY()) & (_unite.getY() > getY() + getH());

	if (uniteInterDessus || uniteInterDessous) {
		//hauteur : ok => intersection possible => test sur la longueur :
			// est-ce qu'il y a correspondance par la droite (unite plus à droite que this)
		bool uniteInterDroite = (getX() < _unite.getX() + _unite.getL()) & (getX() + getL() > _unite.getX());
			// est-ce qu'il y a correspondance par le dessous (unite plus bas que this)
		bool uniteInterDessous = (_unite.getX() < getX() + getL()) & (_unite.getX() + _unite.getL() > getX());

		if (uniteInterDroite || uniteInterDessous) {
			// Il y a bien intersection => on renvoie true (on aurait pu renvoyé directement uniteInterDroite || uniteInterDessous mais c'est plus clair
			return true;
		}
	}
	return false;	// si on arrive là c'est qu'il n'y a pas d'intersection
}

// Routine de jeu du pickup : par défaut, regarde s'il y a intersection avec le joueur et si oui fait son action
void PickUp::Update(SceneManager & sceneManager) {
	if (intersect(*sceneManager.getJoueur())) {
		deleteFlag = true;
	}
}

bool PickUp::getDeleteFlag() {
	return deleteFlag;
}
