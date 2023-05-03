#include "VisiteurHomotethie.h"

VisiteurHomotethie::VisiteurHomotethie(const double vh, const Vecteur2D& centre): _variableHomotetique(vh), _centre(centre) {}

const Vecteur2D VisiteurHomotethie::homotetiqueVecteur(const Vecteur2D& v) const{
	return ((v*_variableHomotetique) + (1 - _variableHomotetique) * _centre);
}

const void VisiteurHomotethie::visite(Vecteur2D& fc) const {
	fc = homotetiqueVecteur(fc);
}
