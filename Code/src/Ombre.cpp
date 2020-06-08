#include "Ombre.h"

#include "Unite.h"

// Constructeur : la largeur est calcul�e automatique � partir de la hauteur : on prend un angle de 30�
Ombre::Ombre(int _x, int _y, int _h, std::map<std::string, sf::Texture>& textDictionnary) : PickUp(_x, _y, _h, _h*tan(30), "Ombre", textDictionnary) {
}

/* Pour les ombres, on consid�re que le joueur est � l'ombre si le point
 * situ� � son centre sur l'axe x et � l'extremit� haute sur y est dans
 * le triangle (pour le moment c'est le point (x+l/2 ; y+h)
 */
bool Ombre::intersect(Unite & _unite) {
	// On commence par enregistrer les coordonn�es du point � tester (comme ce sont les m�mes x et y pour les 2 conditions autant les sauvegarder pour faire moins d'appels
	int xATester = _unite.getX() + _unite.getL()/2;
	int yATester = _unite.getY() + _unite.getH();
	// Puis on v�rifie si le y est ok
	if (getY() < yATester & yATester< getY() + getH()) {
		// Alors on teste sur x
		// C'est un triangle d'angle 30 : il faut utiliser de la trigonom�trie
		if (getX() < xATester & xATester < (tan(30)*(getY() + getH() - yATester) + getX())) {
			return true;
		}			
	}
	return false;
}

/*
// Action � executer quand le joueur est dans l'ombre : il faut le d�clarer � l'abri
// Comme pour la porte, le iDpickUp est inutile mais conserv� de l'h�ritage
void Ombre::ActionOnIntersect(SceneManager& sceneManager, int iDpickUp) {
	sceneManager.MettreJoueurAbri();
}
*/