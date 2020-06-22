#include "OmbreOld.h"
#include "Unite.h"
#include <iostream>

// Constructeur : la largeur est calcul�e automatique � partir de la hauteur : on prend un angle de 30�
OmbreOld::OmbreOld(int _x, int _y, int _h, std::map<std::string, sf::Texture>& textDictionnary) : PickUp(_x, _y, _h, abs(_h*tan(60)), "Ombre.png", textDictionnary) {
	getSprite().setScale(abs(_h * tan(60) / 32), _h / 32);
}

/* Pour les ombres, on consid�re que le joueur est � l'ombre si le point
 * situ� � son centre sur l'axe x et � l'extremit� haute sur y est dans
 * le triangle (pour le moment c'est le point (x+l/2 ; y+h)
 */
bool OmbreOld::intersect(Unite & _unite) {
	// On commence par enregistrer les coordonn�es du point � tester (comme ce sont les m�mes x et y pour les 2 conditions autant les sauvegarder pour faire moins d'appels
	int xATester = _unite.getX() + _unite.getL()/2;
	int yATester = _unite.getY();
	// Puis on v�rifie si le y est ok
	if ((getY() - getH() < yATester) & (yATester< getY())) {
		// Alors on teste sur x
		// C'est un triangle d'angle 30 : il faut utiliser de la trigonom�trie
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
