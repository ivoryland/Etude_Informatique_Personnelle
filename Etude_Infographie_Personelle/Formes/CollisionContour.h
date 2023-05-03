#pragma once
#include "EmballageForme.h"
class CollisionContour : public EmballageForme {
public:
	double rayonAction;
	CollisionContour(Forme& f, double rayon) : rayonAction(rayon), EmballageForme(f) {}

	/**
	M�tohde red�finie.
	Gestion de l'�ventuelle collision entre la forme et le cadre d�finie par coingBG et coinHD
	@param coinBG | le coin du vecteur2D en bas � gauche
	@param coinHD | le coin du vecteur2D en haut � droite
	**/
	const void gestionCollisionContour(const Vecteur2D& coinBG, const Vecteur2D& coinHD) override {
		for (Vecteur2D* vec : *this->getPosition()) {
			collisionDisqueContourAvecRebond(*vec, rayonAction, *this->getVitesse(), coinBG.x, coinBG.y, coinHD.x, coinHD.y);
		}
	}
};
