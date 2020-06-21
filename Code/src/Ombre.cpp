#include "Ombre.h"
#include "Unite.h"
#include <iostream>
#include "SceneManager.h"

// Constructeur : version à override pour les enfants
Ombre::Ombre(int _x, int _y, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary) : Unite(_x, _y, 64, 32, textureName, textDictionnary) {
}

/* Pour les ombres, on considère que le joueur est à l'ombre si le point
 * situé à son centre sur l'axe x et à l'extremité haute sur y est dans
 * le triangle (pour le moment c'est le point (x+l/2 ; y+h)
 */
bool Ombre::intersect(Unite & _unite) {
	// On commence par enregistrer les coordonnées du point à tester (comme ce sont les mêmes x et y pour les 2 conditions autant les sauvegarder pour faire moins d'appels
	int xATester = _unite.getX() + _unite.getL()/2;
	int yATester = _unite.getY();
	// Puis on vérifie si le y est ok
	if ((getY() - getH() - marge <= yATester) & (yATester<= getY() + marge)) {
		// Alors on teste sur x
		if ((getX()-marge <= xATester) & (xATester <= getX() + getL() + marge)) {
			//std::cout<< "Joueur A l'abri" << std::endl;
			return true;
		}			
	}
	return false;
}

void Ombre::Update(SceneManager& sceneManager) {
	if (intersect(*sceneManager.getJoueur())) {
		sceneManager.MettreJoueurAbri();
	}
}
