#pragma once
#include <vector>
#include "../Outils/Outils_math/Vecteur2D.h"

/**
* interface de class Visiteur
*/
class Visiteur
{
public:
	/**
	* Methode permetant la modification d'un pixel (Vecteur)
	* @param FormeComposee& (Forme qui est visitée)
	*/
	virtual const void visite(Vecteur2D& fc)const = 0;
};