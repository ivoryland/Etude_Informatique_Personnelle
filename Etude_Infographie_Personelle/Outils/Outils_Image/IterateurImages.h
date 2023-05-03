#pragma once

/**
	IterateurImage

	Classe ImageTableau, qui permet de se d�placer dans la matrice 2D
	On travail uniquement avec des pointeurs pour gagn� en temps d'execution
**/
class ImageTableau {
public:
	//Pointe sur le premier pixel
	unsigned long* t;
	//Correspond � la Hauteur - 1 du cadre
	unsigned long m;
	//Correspond � la Largeur - 1 du cadre
	unsigned long n;
	//Correspond � la Largeur du cadre
	unsigned long L;

	//---------------------------------Contruscteur----------------------------

	ImageTableau(unsigned long* t, const unsigned long m, const unsigned long n, const unsigned long L) : t(t), m(m), n(n), L(L) {}

	//---------------------------------Contruscteur----------------------------

	/**
	R�cup�re l'�l�ment a l'indice i et j dans la matrice 2D
	@param i | indice x ou ligne de la matrice
	@param j | indice y ou colonne de la matrice
	**/
	const unsigned long* getPixel(const unsigned long i, const unsigned long j) const{
		int L1 = L;
		int i1 = i;
		int j1 = j;
		const unsigned long* pixel = t + i1 * L1 + j1;
		return pixel;
	}

	/**
	Modifie l'�l�ment a l'indice i et j dans la matrice 2D avec la couleur pass�e en param�tre
	@param i | indice x ou ligne de la matrice
	@param j | indice y ou colonne de la matrice
	@param couleurRGBA | La couleur ajout� a la matrice 2D
	**/
	const void setPixel(const unsigned long i, const unsigned long j, const unsigned long couleurRGBA) {
		int L1 = L;
		int i1 = i;
		int j1 = j;
		unsigned long* pixel = t + i1 * L1 + j1;

		*pixel = couleurRGBA;
	}
};