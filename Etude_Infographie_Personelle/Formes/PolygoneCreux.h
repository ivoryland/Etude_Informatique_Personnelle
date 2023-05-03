#pragma once
#include "EmballageForme.h"

class PolygoneCreux : public EmballageForme {
private:
	void bresenhamSegmentGeneral(ImageTableau& m, const Vecteur2D& depart, const Vecteur2D& fin, const unsigned long couleur) {
		unsigned long rouge = 0xFF0000FF;
		int dx, dy, i, xinc, yinc, cumul, x, y;
		x = static_cast<int>(depart.x);
		y = static_cast<int>(depart.y);
		dx = static_cast<int>(fin.x) - x;
		dy = static_cast<int>(fin.y) - y;
		xinc = (dx > 0) ? 1 : -1;
		yinc = (dy > 0) ? 1 : -1;
		dx = abs(dx);
		dy = abs(dy);
		if (x >= 0 && x < 240
			&& y >= 0 && y < 400)
			m.setPixel(x, y, couleur);
		if (dx > dy) {
			cumul = dx / 2;
			for (i = 1; i <= dx; i++, x += xinc, cumul += dy) {
				if (cumul >= dx) {
					cumul -= dx;
					y += yinc;
				}
				if (x >= 0 && x < 240
					&& y >= 0 && y < 400)
					m.setPixel(x, y, couleur);
			}
		}
		else {
			cumul = dy / 2;
			for (i = 1; i <= dy; i++, y += yinc, cumul += dx) {
				if (cumul >= dy) {
					cumul -= dy;
					x += xinc;
				}
				if (x >= 0 && x < 240
					&& y >= 0 && y < 400)
					m.setPixel(x, y, couleur);
			}
		}
	}
	void polygoneGeneralCreux(ImageTableau& m, vector<Vecteur2D*> vec, const unsigned long couleur) {
		size_t taille = vec.size(), i;
		for (i = 1; i < taille; ++i) {
			bresenhamSegmentGeneral(m, *vec.at(i - 1), *vec.at(i), couleur);
		}
		bresenhamSegmentGeneral(m, *vec.at(taille-1), *vec.at(0), couleur);
	}
public:
	vector<Vecteur2D*> anciennePosition;

	PolygoneCreux(Forme& f, const int t, ...) : EmballageForme(f) {
		va_list args;
		va_start(args, t);
		for (int i = 0; i < t; i++) {
			Vecteur2D* v = va_arg(args, Vecteur2D*);
			this->addPositon(*v);
		}
		va_end(args);
	}

	/**
	Méthode virtuelle pure
	Dessine la forme dans la matrice de pixel
	@param matrice2D | un pointeur sur le premier pixel de la matrice
	**/
	const void dessineForme(ImageTableau& matrice2D, const unsigned long couleur) override {
		for (Vecteur2D* vec : *this->getPosition())
			anciennePosition.push_back(vec->clone());
		polygoneGeneralCreux(matrice2D, *this->getPosition(), couleur);
		this->forme->dessineForme(matrice2D, couleur);
	}

	const void nettoyageAnciennePosition(ImageTableau& matrice2D) override {
		polygoneGeneralCreux(matrice2D, anciennePosition, FormeNue::COULEUR_DEFAUT);
		size_t del = anciennePosition.size();
		vector<Vecteur2D*>::iterator it;
		for (size_t d = 0; d < del; d++) {
			it = anciennePosition.begin();
			anciennePosition.erase(it);
		}
		this->forme->nettoyageAnciennePosition(matrice2D);
	}
};