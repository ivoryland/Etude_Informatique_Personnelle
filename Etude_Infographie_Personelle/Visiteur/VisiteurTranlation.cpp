#include "VisiteurTranlation.h"

VisiteurTranlation::VisiteurTranlation(const Vecteur2D& vt): _variableTranslatoire(vt) {}

const void VisiteurTranlation::visite(Vecteur2D& p) const{
	p += _variableTranslatoire;
}
