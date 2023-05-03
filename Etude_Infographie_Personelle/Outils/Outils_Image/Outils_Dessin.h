#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
//#include "../../Forme/Disque.h"
//#include "../../Forme/Quartique_Piriforme.h"
#include "../Outils_math/Vecteur2D.h"

/**
Facteur mélange tel que: 0 <= facteur_melange <= 1
Pour facteur_melange == 0 Pixel derrier
{
	resultat = couleur1
}
Pour facteur_melange == 1 Pixel devant
{
	resultat = couleur2
}
*/
inline const unsigned long melange(const unsigned long couleurDevant, const unsigned long couleurArriere, const float facteur_melange = 0.5) {
	const double DCC = 255.;
	if (facteur_melange >= 1) {
		return couleurDevant;
	}
	else if (facteur_melange <= 0) {
		return couleurArriere;
	}

	double rgba1[4];
	double rgba2[4];
	unsigned long rgba[4];
	int i, j;
	double complemantaire_melange = (1.0 - facteur_melange);
	for (i = 0, j = 0; j <= 3; i += 8, j++) {
		rgba1[j] = ((couleurDevant >> i) & 0xFF) / DCC;
		rgba2[j] = ((couleurArriere >> i) & 0xFF) / DCC;
		rgba[j] = (rgba1[j] * complemantaire_melange + rgba2[j] * facteur_melange) * DCC;
	}
	return (rgba[3] << 24) | (rgba[2] << 16) | (rgba[1] << 8) | rgba[0];
}

inline const unsigned long prioriteAlphaDevant(const unsigned long couleurDevant, const unsigned long couleurArriere) {
	const double DCC = 255.;
	double aDevant = (couleurDevant & 0xFF) / DCC;

	return melange(couleurDevant, couleurArriere, aDevant);
}

inline const unsigned long prioriteAlphaArriere(const unsigned long couleurDevant, const unsigned long couleurArriere) {
	const double DCC = 255.;
	double aArriere = (couleurArriere & 0xFF) / DCC;

	return melange(couleurDevant, couleurArriere, aArriere);
}

/*
* Objectif: modifier la couleur RGBA de la variable couleur en fonction de la nuance (la variable) RGBA
*/
inline const unsigned long degrader_Couleur(const unsigned long RGBA,const unsigned long couleur, const float facteur_melange = 0.5) {
	return melange(RGBA, couleur, facteur_melange);
}

/*
template<int NOMBRE_LIGNE, int NOMBRE_COLONNES>
const bool dessineForme(Forme& forme, unsigned long(*mp)[NOMBRE_LIGNE][NOMBRE_COLONNES], const float fondu) {
	Vecteur coinBG, coinHD;
	forme.getBord(coinBG, coinHD);

	coinBG.arroundi();
	coinHD.arroundi();

	int i, j;

	for (i = (int)coinBG.x; i <= coinHD.x; i++) {
		for (j = (int)coinBG.y; j <= coinHD.y; j++) {
			Vecteur p(i, j);
			if (forme.pixelAppartientForme(p)) {
				if (i >= 0 && i < NOMBRE_LIGNE && j >= 0 && j < NOMBRE_COLONNES) {
					(*mp)[i][j] = melange((*mp)[i][j], forme.getCouleur(), fondu);
				}
			}
		}

		if (i % 3 == 0) {
			forme.degradeCouleur(0xFFFF00FF, 0.95);
		}
	}
	return true;
}

template<int NOMBRE_LIGNE, int NOMBRE_COLONNES>
void capture_Pixel_Quartique_Piriforme(Quartique_Piriforme& qf, 
	unsigned long(*mp)[NOMBRE_LIGNE][NOMBRE_COLONNES], 
	unsigned long(*res)[NOMBRE_LIGNE][NOMBRE_COLONNES],
	const int dx, const int dy, const float fondu)
	{
	double _variableHomotetique = 0.5;
	Vecteur _centre(120, 240);
	Vecteur modifier(0, 0);
	Vecteur sommetQF = qf.getSommet();
	int px = 0, py = 0, symmetric_pyD, symmetric_pyG, x = 0, j = 0;
	double a = qf._a, b = qf._b, y = 0;

	for (x = 0; x < 2 * a; x++) {
		//l'équation utilisé
		y = b * sqrt(static_cast<double>(x) * static_cast<double>(x) * (2 * a - static_cast<double>(x))) / a;

		px = static_cast<int>(x + sommetQF.x);

		symmetric_pyD = static_cast<int>(sommetQF.y + y - 1);
		symmetric_pyG = static_cast<int>(sommetQF.y - y + 1);
		for (py = symmetric_pyG; py < symmetric_pyD; py++) {
			if (px >= 0 && px < NOMBRE_LIGNE && py >= 0 && py < NOMBRE_COLONNES ){


				//HOMOTETHIE
				modifier = Vecteur(px, py);
				modifier = ((modifier * _variableHomotetique) + (1 - _variableHomotetique) * _centre);
				modifier.arroundi();

				(*res)[static_cast<int>(modifier.x)][static_cast<int>(modifier.y)] = 
					prioritaAlpha((*mp)[px][py], (*mp)[static_cast<int>(modifier.x)][static_cast<int>(modifier.y)]);
			}
		}
	}
}*/
