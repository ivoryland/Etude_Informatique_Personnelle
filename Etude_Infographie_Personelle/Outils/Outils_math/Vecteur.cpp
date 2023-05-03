#include "Vecteur2D.h"
#include "../../Visiteur/Visiteur.h"

const void Vecteur2D::accepte(const Visiteur& visiteur) {
	visiteur.visite(*this);
}