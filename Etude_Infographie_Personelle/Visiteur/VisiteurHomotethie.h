#pragma once
#include "Visiteur.h"
#include <math.h>

/**
* VisiteurRotation implemente l'interface Visiteur
* classe qui permet l'homotethie d'une forme
*/
class VisiteurHomotethie : public Visiteur
{
private:
	double _variableHomotetique; 
	Vecteur2D _centre;
public:

	/**
	Constructeur de la classe VisiteurHomotethie qui effectue une homotethie selon un rapport homotetique 
	et un point invariant
	**/
	VisiteurHomotethie(const double vh, const Vecteur2D& centre);

	const Vecteur2D homotetiqueVecteur(const Vecteur2D& v)const;

	const void visite(Vecteur2D& fc)const;
};