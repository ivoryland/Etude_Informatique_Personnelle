#pragma once
#include "EmballageForme.h"
#include "FormeNue.h"

class BSpline : public EmballageForme {
private:

	inline Vecteur2D* baryCentre2D(const Vecteur2D& sa, const Vecteur2D& sb, const double t) const {
		return new Vecteur2D(((1 - t) * sa) + (t * sb));
	}
	void M(ImageTableau& matrice2D, vector<Vecteur2D*> vec, const unsigned long couleur, const double t) {
		size_t taille = vec.size(), i;
		if (taille == 1) {
			Vecteur2D M = *vec.at(0);
			if(M.x >= 0 && M.x < 240
				&& M.y >= 0 && M.y < 400)
				matrice2D.setPixel(M.x, M.y, couleur);
		}
		else {
			vector<Vecteur2D*> barryCentre;
			for (i = 0; i < taille - 1; i++) {
				barryCentre.push_back(baryCentre2D(*vec.at(i), *vec.at(i + 1), t));
			}
			M(matrice2D, barryCentre, couleur, t);
			size_t del = barryCentre.size();
			for (size_t d = 0; d < del; d++)
				delete barryCentre.at(d);
		}
	}

	void bspline(ImageTableau& matrice2D, vector<Vecteur2D*> vec, const unsigned long couleur) {
		double t;
		for (t = 0; t <= 1; t += resolution) {
			M(matrice2D, vec, couleur, t);
		}
	}
public:

	vector<Vecteur2D*> anciennePosition;
	const double resolution = 0.001;

	BSpline(Forme& f, const int t, ...): EmballageForme(f){
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
		bspline(matrice2D, *this->getPosition(), couleur);
		this->forme->dessineForme(matrice2D, couleur);
	}

	const void nettoyageAnciennePosition(ImageTableau& matrice2D) override {
		bspline(matrice2D, anciennePosition, FormeNue::COULEUR_DEFAUT);
		size_t del = anciennePosition.size();
		vector<Vecteur2D*>::iterator it;
		for (size_t d = 0; d < del; d++) {
			it = anciennePosition.begin();
			anciennePosition.erase(it);
		}
		this->forme->nettoyageAnciennePosition(matrice2D);
	}
};
