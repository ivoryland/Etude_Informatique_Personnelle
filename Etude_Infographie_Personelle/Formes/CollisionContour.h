#pragma once
#include "EmballageForme.h"
class CollisionContour : public EmballageForme {
public:
	double rayonAction;
	CollisionContour(Forme& f, double rayon) : rayonAction(rayon), EmballageForme(f) {}

	/**
	Métohde redéfinie.
	Gestion de l'éventuelle collision entre la forme et le cadre définie par coingBG et coinHD
	@param coinBG | le coin du vecteur2D en bas à gauche
	@param coinHD | le coin du vecteur2D en haut à droite
	**/
	const void gestionCollisionContour(const Vecteur2D& coinBG, const Vecteur2D& coinHD) override {
		for (Vecteur2D* vec : *this->getPosition()) {
			collisionDisqueContourAvecRebond(*vec, rayonAction, *this->getVitesse(), coinBG.x, coinBG.y, coinHD.x, coinHD.y);
		}
	}
};
