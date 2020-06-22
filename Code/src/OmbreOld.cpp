#include "OmbreOld.h"
#include "Unite.h"
#include <iostream>

// Constructeur : la largeur est calculée automatique à partir de la hauteur : on prend un angle de 30°
OmbreOld::OmbreOld(int _x, int _y, int _h, std::map<std::string, sf::Texture>& textDictionnary) : PickUp(_x, _y, _h, abs(_h*tan(60)), "Ombre.png", textDictionnary) {
	getSprite().setScale(abs(_h * tan(60) / 32), _h / 32);
}

/* Pour les ombres, on considère que le joueur est à l'ombre si le point
 * situé à son centre sur l'axe x et à l'extremité haute sur y est dans
 * le triangle (pour le moment c'est le point (x+l/2 ; y+h)
 */
bool OmbreOld::intersect(Unite & _unite) {
	// On commence par enregistrer les coordonnées du point à tester (comme ce sont les mêmes x et y pour les 2 conditions autant les sauvegarder pour faire moins d'appels
	int xATester = _unite.getX() + _unite.getL()/2;
	int yATester = _unite.getY();
	// Puis on vérifie si le y est ok
	if ((getY() - getH() < yATester) & (yATester< getY())) {
		// Alors on teste sur x
		// C'est un triangle d'angle 30 : il faut utiliser de la trigonométrie
		if ((getX() < xATester) & (xATester < (abs(tan(60))*((getY() - yATester) + getH() ) + getX()))) {
			return true;
		}			
	}
	return false;
}

void OmbreOld::Update(SceneManager& sceneManager) {
	if (intersect(*sceneManager.getJoueur())) {
		sceneManager.MettreJoueurAbri();
	}
}
