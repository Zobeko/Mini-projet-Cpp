#include "Ombre.h"
#include "SceneManager.h"

// Constructeur
Ombre::Ombre(int _x, int _y, std::string textureName, std::map<std::string, sf::Texture>& textDictionnary) : Unite(_x, _y, 64, 32, textureName, textDictionnary) {
}

/* Pour les ombres, on consid�re que le joueur est � l'ombre si le point
 * situ� � son centre sur l'axe x et � l'extremit� haute sur y est dans
 * le rectangle (c'est le point (x+l/2 ; y) )
 */
bool Ombre::intersect(Unite & _unite) {
	// On commence par enregistrer les coordonn�es du point � tester (comme ce sont les m�mes x et y pour les 2 conditions autant les sauvegarder pour faire moins d'appels
	int xATester = _unite.getX() + _unite.getL()/2;
	int yATester = _unite.getY();
	// Puis on v�rifie si le y est ok
	if ((getY() - getH() - marge <= yATester) & (yATester<= getY() + marge)) {
		// Alors on teste sur x
		if ((getX()-marge <= xATester) & (xATester <= getX() + getL() + marge)) {
			return true;
		}			
	}
	return false;
}

// Regarde si le joueur est "dans l'ombre" et si oui le marque "� l'abri" (de m�duse)
void Ombre::Update(SceneManager& sceneManager) {
	if (intersect(*sceneManager.getJoueur())) {
		sceneManager.MettreJoueurAbri();
	}
}
