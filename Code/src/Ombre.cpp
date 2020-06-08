#include "Ombre.h"

#include "Unite.h"

// Constructeur : la largeur est calculée automatique à partir de la hauteur : on prend un angle de 30°
Ombre::Ombre(int _x, int _y, int _h, std::map<std::string, sf::Texture>& textDictionnary) : PickUp(_x, _y, _h, _h*tan(30), "Ombre", textDictionnary) {
}

/* Pour les ombres, on considère que le joueur est à l'ombre si le point
 * situé à son centre sur l'axe x et à l'extremité haute sur y est dans
 * le triangle (pour le moment c'est le point (x+l/2 ; y+h)
 */
bool Ombre::intersect(Unite & _unite) {
	// On commence par enregistrer les coordonnées du point à tester (comme ce sont les mêmes x et y pour les 2 conditions autant les sauvegarder pour faire moins d'appels
	int xATester = _unite.getX() + _unite.getL()/2;
	int yATester = _unite.getY() + _unite.getH();
	// Puis on vérifie si le y est ok
	if (getY() < yATester & yATester< getY() + getH()) {
		// Alors on teste sur x
		// C'est un triangle d'angle 30 : il faut utiliser de la trigonométrie
		if (getX() < xATester & xATester < (tan(30)*(getY() + getH() - yATester) + getX())) {
			return true;
		}			
	}
	return false;
}

/*
// Action à executer quand le joueur est dans l'ombre : il faut le déclarer à l'abri
// Comme pour la porte, le iDpickUp est inutile mais conservé de l'héritage
void Ombre::ActionOnIntersect(SceneManager& sceneManager, int iDpickUp) {
	sceneManager.MettreJoueurAbri();
}
*/