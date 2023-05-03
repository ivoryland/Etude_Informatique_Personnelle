#pragma once
#include "EmballageForme.h"
#include "FormeNue.h"

class RenctanglePlein : public EmballageForme {
private:
	void recangleGeneralPlein(ImageTableau& m, vector<Vecteur2D*> vec, const unsigned long couleur) {
		Vecteur2D coinBG, coinHD;
		this->getBord(coinBG, coinHD);
		int x, y;
		for (x = coinBG.x; x < coinHD.x; x++) {
			for (y = coinBG.y; y < coinHD.y; y++) {
				if (x >= 0 && x < 240
					&& y >= 0 && y < 400)
					m.setPixel(x, y, couleur);
			}
		}
	}
public:
	vector<Vecteur2D*> anciennePosition;

	RenctanglePlein(Forme& f,const int t, ...) : EmballageForme(f) {
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
		recangleGeneralPlein(matrice2D, *this->getPosition(), couleur);
		this->forme->dessineForme(matrice2D, couleur);
	}

	const void nettoyageAnciennePosition(ImageTableau& matrice2D) override {
		recangleGeneralPlein(matrice2D, anciennePosition, FormeNue::COULEUR_DEFAUT);
		size_t del = anciennePosition.size();
		vector<Vecteur2D*>::iterator it;
		for (size_t d = 0; d < del; d++) {
			it = anciennePosition.begin();
			anciennePosition.erase(it);
		}
		this->forme->nettoyageAnciennePosition(matrice2D);
	}

	/**
	Métohde redéfinie.
	Définie la zone à peindre du segment, c'est-à-dire un rectangle contenant
	tous les pixels du segment
	@param min | vecteur du point en bas à gauche
	@param max | vecteur du point en haut à droite
	**/
	const void getBord(Vecteur2D& min, Vecteur2D& max) override {
		size_t i, taille = this->getPosition()->size();
		for (i = 1; i < taille; ++i) {
			min = *this->getPosition()->at(i - 1) < *this->getPosition()->at(i);
			max = *this->getPosition()->at(i - 1) > *this->getPosition()->at(i);
		}
	}
};