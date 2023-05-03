#include "VisiteurRotation.h"

VisiteurRotation::VisiteurRotation(const double& AR, const Vecteur2D& centre): _centre(centre) {
	rotation = Matrice::creerRotation(AR);
}

const Vecteur2D VisiteurRotation::rotationVecteur(const Vecteur2D& vec) const{
	return rotation*(vec-_centre) + _centre;
}

const void VisiteurRotation::visite(Vecteur2D& fc) const {
	fc = rotationVecteur(fc);
}
