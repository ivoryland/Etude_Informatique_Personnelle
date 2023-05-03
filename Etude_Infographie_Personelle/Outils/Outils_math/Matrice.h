#pragma once
#include "Vecteur2D.h"

class Matrice
{
public:
	Vecteur2D ligneHaut;
	Vecteur2D ligneBas;


	/**
	* Constructeur de la classe Matrice de vecteur, elle possede de variable ligneBas et ligneHaut,
	* chacun etant un Vecteur
	* @param Vecteur& lv, Vecteur&lb (deux vecteurs)
	**/
	Matrice(const Vecteur2D& lh = Vecteur2D(1,0), const Vecteur2D& lb = Vecteur2D(0,1)) : ligneHaut(lh), ligneBas(lb) {}


	/**
	* produit scalaire de la matrice avec un vecteur
	* @param Vecteur& v (la multiplieur sur la matrice, ligneHaut * v et ligneBas * v)
	* @return Vecteur (le produit scalaire)
	**/
	const Vecteur2D operator*(const Vecteur2D& v)const {
		return Vecteur2D(ligneHaut * v, ligneBas * v);
	}


	/**
	* affectuer une rotation de la matrice a partir d'un angle
	* @param double (l'angle de rotation)
	* @return Matrice (la matrice rotationnee)
	**/
	const static Matrice creerRotation(const double angleRadian) {
		double cosA = cos(angleRadian);
		double sinA = sin(angleRadian);
		return Matrice(Vecteur2D(cosA, -sinA),
			Vecteur2D(sinA, cosA));
	}
};