#pragma once
#include "Visiteur.h"

/**
* VisiteurTranslation implemente l'interface Visiteur
* classe qui permet la translation d'une forme dans un plan orthonormé
*/
class VisiteurTranlation : public Visiteur
{
private:
	Vecteur2D _variableTranslatoire;
public:
	VisiteurTranlation(const Vecteur2D& vt);

	const void visite(Vecteur2D& t)const;

};

