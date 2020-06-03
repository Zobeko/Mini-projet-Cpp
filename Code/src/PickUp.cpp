#include "PickUp.h"
#include "Unite.h"

using namespace std;

PickUp::PickUp(int _x, int _y, int _h, int _l, string textureName) : Unite(_x, _y, _h, _l, textureName)
{

}


bool PickUp::intersect(Unite* _unite) {
	//test sur la hauteur :
		// est-ce qu'il y a correspondance par le dessus (unite plus haut que this)
	bool uniteInterDessus = (getY() < _unite.getY() + _unite.getH()) & (getY() + getH() > _unite.getY());
		// est-ce qu'il y a correspondance par le dessous (unite plus bas que this)
	bool uniteInterDessous = (_unite.getY() < getY() + getH()) & (_unite.getY() + _unite.getH() > getY());

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

void PickUp::Update(SceneManager & sceneManager) {
	bool intersectJoueur = intersect(sceneManager.getJoueur());
}
