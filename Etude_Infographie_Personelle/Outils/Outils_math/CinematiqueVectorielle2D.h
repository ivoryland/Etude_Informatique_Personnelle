#pragma once
#include "Vecteur2D.h"

inline static void mouvementRectiligneUniforme(Vecteur2D& position, const Vecteur2D& vitesse, const double deltaT) {
	position += (vitesse * deltaT);
}

inline static void mouvementUniformeAccelere(Vecteur2D& position, Vecteur2D& vitesse, Vecteur2D& acceleration, const double deltaT) {
	mouvementRectiligneUniforme(position, vitesse, deltaT);
	position += (acceleration * 0.5 * deltaT * deltaT);
	mouvementRectiligneUniforme(vitesse, acceleration, deltaT);
}

inline static bool collisionDisqueSegmentAvecRebond(const Vecteur2D& position, const double rayon, Vecteur2D& vitesse, const Vecteur2D& P0, const Vecteur2D P1) {
	Vecteur2D P1P0 = P1 - P0;
	Vecteur2D N = P1P0.base();

	double distanceSignee = (position - P0) * N;

	if (distanceSignee >= rayon)
		return false;

	double vN = vitesse * N;

	if (vN >= 0)
		return false;

	Vecteur2D delta = N * (-2 * vN);
	vitesse += delta;
	return true;
}

inline static bool collisionDisqueContourAvecRebond(const Vecteur2D& position, const double rayon, Vecteur2D& vitesse,
	const double abscisse, const double ordonne, const double largeur, const double hauteur) {

	Vecteur2D min(abscisse, ordonne);
	Vecteur2D diagonal(largeur, hauteur);
	Vecteur2D max(min.x + diagonal.x, min.y + diagonal.y);

	Vecteur2D coins[5];

	coins[0] = min;
	coins[1] = Vecteur2D(max.x, min.y);
	coins[2] = max;
	coins[3] = Vecteur2D(min.x, max.y);
	coins[4] = coins[0];

	size_t i;
	for (i = 1; i < 5; ++i) {
		if (collisionDisqueSegmentAvecRebond(position, rayon, vitesse, coins[i - 1], coins[i]))
			return true;
	}
	return false;
}