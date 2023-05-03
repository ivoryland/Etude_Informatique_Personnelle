#pragma once
#include "Visiteur.h"
#include "../Outils/Outils_math/Matrice.h"

/**
* VisiteurRotation implemente l'interface Visiteur
* classe qui permet la rotation d'une forme
*/
class VisiteurRotation : public Visiteur
{
private:
	Matrice rotation;
	Vecteur2D _centre;
public:

	/**
	* Constructeur de la classe VisiteurRotation
	* @param double (angle de rotation) et Vecteur& (le point invariant de la rotation)
	**/
	VisiteurRotation(const double& AR, const Vecteur2D& centre);

	const Vecteur2D rotationVecteur(const Vecteur2D& vec) const;

	const void visite(Vecteur2D& fc)const;
};

