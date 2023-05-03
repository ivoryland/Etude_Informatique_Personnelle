#pragma once
#include "EmballageForme.h"
#include "FormeNue.h"

class DisquePlein : public EmballageForme {
private:
	void bresenhamCerclePlein(ImageTableau& m, const Vecteur2D& centre, const int r, const unsigned long couleur) {
		float rayon2 = r * r;
		Vecteur2D coinBG, coinHD;

		Vecteur2D u(1, 1);
		Vecteur2D diagonal = rayon * u;
		coinBG = centre - diagonal;
		coinHD = centre + diagonal;

		int x, y;
		for (x = coinBG.x; x < coinHD.x; x++) {
			for (y = coinBG.y; y < coinHD.y; y++) {
				Vecteur2D p(x, y);
				if ((p - centre).norme2() <= rayon2)
					if (x >= 0 && x < 240
						&& y >= 0 && y < 400)
						m.setPixel(x, y, couleur);
			}
		}
	}
public:
	double rayon;
	Vecteur2D ancienCentre;
	DisquePlein(Forme& f, const double r, Vecteur2D& centre): rayon(r), ancienCentre(Vecteur2D()), EmballageForme(f) {
		this->addPositon(centre);
	}

	/**
	Méthode virtuelle pure
	Dessine la forme dans la matrice de pixel
	@param matrice2D | un pointeur sur le premier pixel de la matrice
	**/
	const void dessineForme(ImageTableau& matrice2D, const unsigned long couleur) override {
		ancienCentre = *this->getPosition()->at(0);
		bresenhamCerclePlein(matrice2D, *this->getPosition()->at(0), rayon, couleur);
		this->forme->dessineForme(matrice2D, couleur);
	}

	const void nettoyageAnciennePosition(ImageTableau& matrice2D) override {
		bresenhamCerclePlein(matrice2D, ancienCentre, rayon, FormeNue::COULEUR_DEFAUT);
		this->forme->nettoyageAnciennePosition(matrice2D);
	}
};
