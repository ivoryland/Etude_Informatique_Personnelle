#pragma once

/**
	IterateurImage

	Classe ImageTableau, qui permet de se déplacer dans la matrice 2D
	On travail uniquement avec des pointeurs pour gagné en temps d'execution
**/
class ImageTableau {
public:
	//Pointe sur le premier pixel
	unsigned long* t;
	//Correspond à la Hauteur - 1 du cadre
	unsigned long m;
	//Correspond à la Largeur - 1 du cadre
	unsigned long n;
	//Correspond à la Largeur du cadre
	unsigned long L;

	//---------------------------------Contruscteur----------------------------

	ImageTableau(unsigned long* t, const unsigned long m, const unsigned long n, const unsigned long L) : t(t), m(m), n(n), L(L) {}

	//---------------------------------Contruscteur----------------------------

	/**
	Récupère l'élément a l'indice i et j dans la matrice 2D
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
	Modifie l'élément a l'indice i et j dans la matrice 2D avec la couleur passée en paramètre
	@param i | indice x ou ligne de la matrice
	@param j | indice y ou colonne de la matrice
	@param couleurRGBA | La couleur ajouté a la matrice 2D
	**/
	const void setPixel(const unsigned long i, const unsigned long j, const unsigned long couleurRGBA) {
		int L1 = L;
		int i1 = i;
		int j1 = j;
		unsigned long* pixel = t + i1 * L1 + j1;

		*pixel = couleurRGBA;
	}
};