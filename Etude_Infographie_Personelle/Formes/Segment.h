#pragma once
#include "EmballageForme.h"
class Segment : public EmballageForme {
private:
	Vecteur2D ancienDepart, ancienneFin;

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
		if(x >= 0 && x < 240
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

public:
	Segment(Forme& f, Vecteur2D& a, Vecteur2D& b) : ancienDepart(Vecteur2D()), ancienneFin(Vecteur2D()), EmballageForme(f) {
		this->addPositon(a);
		this->addPositon(b);
	}

	/**
	Métohde redéfinie.
	Définie la zone à peindre du segment, c'est-à-dire un rectangle contenant
	tous les pixels du segment
	@param min | vecteur du point en bas à gauche
	@param max | vecteur du point en haut à droite
	**/
	const void getBord(Vecteur2D& min, Vecteur2D& max) override {
		Vecteur2D depart = *EmballageForme::getPosition()->at(0), arrivee = *EmballageForme::getPosition()->at(1);
		min = depart < arrivee;
		max = depart > arrivee;
	}

	/**
	Méthode virtuelle pure.
	Vérifie si la forme entre dans la hit box de notre forme this
	@param f | forme
	@param this | forme
	**/
	const void hitBox(Forme& f) override {
		/*
		Vecteur2D soustractionVectorielle = *this->getPosition()->at(1) - *this->getPosition()->at(0);
		soustractionVectorielle.arroundi();
		Vecteur2D vecteurDirecteur = Vecteur2D(soustractionVectorielle.y, -soustractionVectorielle.x);
		double _c = -vecteurDirecteur * *this->getPosition()->at(1);
		int test;
		for (Vecteur2D* vec : *f.getPosition()) {
			test = vecteurDirecteur * (*vec) + _c;
			if (test <= 1 && test >= -1) {
				Vecteur2D vitesse = *f.getVitesse();
				f.setVitesse(*new Vecteur2D(-vitesse.x, -vitesse.y));
			}
		}*/
	}

	/**
	Méthode virtuelle pure
	Dessine la forme dans la matrice de pixel
	@param matrice2D | un pointeur sur le premier pixel de la matrice
	**/
	const void dessineForme(ImageTableau& matrice2D, const unsigned long couleur) override {
		ancienDepart = *this->getPosition()->at(0);
		ancienneFin = *this->getPosition()->at(1);
		bresenhamSegmentGeneral(matrice2D, *this->getPosition()->at(0), *this->getPosition()->at(1), couleur);
		this->forme->dessineForme(matrice2D, couleur);
	}

	const void nettoyageAnciennePosition(ImageTableau& matrice2D) override {
		bresenhamSegmentGeneral(matrice2D, ancienDepart, ancienneFin, FormeNue::COULEUR_DEFAUT);
		this->forme->nettoyageAnciennePosition(matrice2D);
	}

	/**
	Métohde redéfinie.
	Décrit le nombre de points (Vecteur2D) exacte pour décrire la forme
	@return int | le nombre de Vecteurs pour la forme, ici 2
	**/
	const int NombrePoints()const {
		return 2;
	}

	operator string()const override {
		string oss = "Segment : [ nbPoints : " + to_string(this->NombrePoints()) + " | ";
		for (Vecteur2D* p : *this->forme->getPosition()) {
			oss += (string)*p;
		}
		return oss + "] | Vitesse : " + (string)*this->forme->getVitesse() + " | Acceleration : " + (string)*this->forme->getAcceleration() + "\n";
	}

	friend ostream& operator<<(ostream& s, const Segment& f);
};

inline ostream& operator<<(ostream& s, const Segment& f) {
	return s << (string)f;
}