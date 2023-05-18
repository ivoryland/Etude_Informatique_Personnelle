#pragma once

namespace gui_ite {
	/**
		IterateurImage g�n�rique pour tableau 2D

		Classe ImageTableau, qui permet de se d�placer dans la matrice 2D
		On travail uniquement avec des pointeurs pour gagn� en temps d'execution
		TEST : OK
	**/
	template<class T>
	class ImageTableau {
	public:
		//Pointe sur le premier pixel
		T* t;
		//Correspond � la Hauteur - 1 du cadre
		T m;
		//Correspond � la Largeur - 1 du cadre
		T n;
		//Correspond � la Largeur du cadre
		T L;

		//---------------------------------Contruscteur----------------------------
		ImageTableau() : t(nullptr), m(0), n(0), L(0){}
		ImageTableau(T* t, const T m, const T n, const T L) : t(t), m(m), n(n), L(L) {}

		//---------------------------------Contruscteur----------------------------

		/**
		R�cup�re l'�l�ment a l'indice i et j dans la matrice 2D
		@param i | indice x ou ligne de la matrice
		@param j | indice y ou colonne de la matrice
		**/
		const T* getPixel(const T i, const T j) const {
			T L1 = L;
			T i1 = i;
			T j1 = j;

			const T* pixel = t + i1 * L1 + j1;
			return pixel;
		}

		/**
		Modifie l'�l�ment a l'indice i et j dans la matrice 2D avec la couleur pass�e en param�tre
		@param i | indice x ou ligne de la matrice
		@param j | indice y ou colonne de la matrice
		@param couleurRGBA | La couleur ajout� a la matrice 2D
		**/
		const void setPixel(const T i, const T j, const T couleurRGBA) {
			T L1 = L;
			T i1 = i;
			T j1 = j;
			T* pixel = t + i1 * L1 + j1;

			*pixel = couleurRGBA;
		}
	};
}