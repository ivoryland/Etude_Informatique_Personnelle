#pragma once
#include "EmballageForme.h"
#include "FormeNue.h"

class DisqueCreux : public EmballageForme {
private:
	void dessineCercleComplet(ImageTableau& m, const int x, const int y, const Vecteur2D& pos, const unsigned long couleur) {
		int x1, y1;
		int x2, y2;
		int x3, y3;
		int x4, y4;
		int x5, y5;
		int x6, y6;
		int x7, y7;
		int x8, y8;
		x1 = pos.x + x, y1 = pos.y + y;
		if (x1 >= 0 && x1 < 240
			&& y1 >= 0 && y1 < 400) 
			m.setPixel(x1, y1, couleur);
			
		x2 = pos.x + x, y2 = pos.y - y;
		if (x2 >= 0 && x2 < 240
			&& y2 >= 0 && y2 < 400)
			m.setPixel(x2, y2, couleur);

		x3 = pos.x - x, y3 = pos.y + y;
		if (x3 >= 0 && x3 < 240
			&& y3 >= 0 && y3 < 400)
			m.setPixel(x3, y3, couleur);

		x4 = pos.x - x, y4 = pos.y - y;
		if (x4 >= 0 && x4 < 240
			&& y4 >= 0 && y4 < 400)
			m.setPixel(x4, y4, couleur);

		x5 = pos.x + y, y5 = pos.y + x;
		if (x5 >= 0 && x5 < 240
			&& y5 >= 0 && y5 < 400)
			m.setPixel(x5, y5, couleur);

		x6 = pos.x + y, y6 = pos.y - x;
		if (x6 >= 0 && x6 < 240
			&& y6 >= 0 && y6 < 400)
			m.setPixel(x6, y6, couleur);

		x7 = pos.x - y, y7 = pos.y + x;
		if (x7 >= 0 && x7 < 240
			&& y7 >= 0 && y7 < 400)
			m.setPixel(x7, y7, couleur);

		x8 = pos.x - y, y8 = pos.y - x;
		if (x8 >= 0 && x8 < 240
			&& y8 >= 0 && y8 < 400)
			m.setPixel(x8, y8, couleur);
	}
	void bresenhamCercleCreux(ImageTableau& m, const Vecteur2D& centre, const int rayon, const unsigned long couleur) {
		Vecteur2D pos = centre;
		int x = 0, y = rayon, d = 1 - rayon;
		dessineCercleComplet(m, x, y, pos, couleur);
		while (y > x) {
			if (d < 0)
				d += 2 * x + 3;
			else {
				d += 2 * (x - y) + 5;
				y--;
			}
			x++;
			dessineCercleComplet(m, x, y, pos, couleur);
		}
	}
public:
	int rayon;
	Vecteur2D ancienCentre;

	DisqueCreux(Forme& f, const int r, Vecteur2D& centre) : rayon(r), ancienCentre(Vecteur2D()), EmballageForme(f) {
		this->addPositon(centre);
	}

	/**
	Méthode virtuelle pure
	Dessine la forme dans la matrice de pixel
	@param matrice2D | un pointeur sur le premier pixel de la matrice
	**/
	const void dessineForme(ImageTableau& matrice2D, const unsigned long couleur) override {
		ancienCentre = *this->getPosition()->at(0);
		bresenhamCercleCreux(matrice2D, *this->getPosition()->at(0), rayon, couleur);
		this->forme->dessineForme(matrice2D, couleur);
	}

	const void nettoyageAnciennePosition(ImageTableau& matrice2D) override {
		bresenhamCercleCreux(matrice2D, ancienCentre, rayon, FormeNue::COULEUR_DEFAUT);
		this->forme->nettoyageAnciennePosition(matrice2D);
	}
};