/*
 * OutilsCreationImage.cpp
 *
 *  Created on: 26 juil. 2020
 *      Author: Dom
 */

#include "OutilsCreationImage.h"

/*static*/ const unsigned long OutilsCreationImage::TAILLE_HEADER = 14;
/*static*/ const unsigned long OutilsCreationImage::TAILLE_DIB = 56; // correspond à BITMAPV3INFOHEADER
/*static*/ const unsigned long OutilsCreationImage::BI_BITFIELDS = 3; // méthode de compression : pas de compression car les pixels sont codés sur 32 bits

//--------------------------------------------------------------------------------------------------------

/**
 * Ecrit sur f l'entête DIB Header
 * écrit 56 octets en tout
 *
 * DONNEES :
 * largeurEnPixels : largeur de l'image, mesurée en pixels
 * hauteurEnPixels : hauteur de l'image, mesurée en pixels
 * tailleTableauPixels : taille du tableau de pixels, mesurée en octets
 * densiteHorizontale : mesurée en pixels/m
 * densiteVerticale : mesurée en pixels/m
 * */
/*static*/ void OutilsCreationImage::creeBMPDIBHeader(iostream & f,
							 const unsigned long largeurEnPixels,
							 const unsigned long hauteurEnPixels,
							 const unsigned long tailleTableauPixels,
							 const unsigned long densiteHorizontale,
							 const unsigned long densiteVerticale)
{
ecritLittleEndian(f,TAILLE_DIB);

ecritLittleEndian(f,largeurEnPixels);

ecritLittleEndian(f,hauteurEnPixels);

const unsigned short nombrePlansCouleur = 1;
ecritLittleEndian(f,nombrePlansCouleur);

const unsigned short profondeurPixel = 32; // 32 bits pour coder un pixel
ecritLittleEndian(f,profondeurPixel);

const unsigned long methodeCompression = BI_BITFIELDS; // 3; // correspond à BI_BITFIELDS,
											// pas de compression car profondeur = 32
ecritLittleEndian(f,methodeCompression);

ecritLittleEndian(f, tailleTableauPixels);

ecritLittleEndian(f,densiteHorizontale);
ecritLittleEndian(f,densiteVerticale);

const unsigned long vide = 0; // 4 octets contenant 0

ecritLittleEndian(f,vide);  // nombre de couleurs dans la palette
ecritLittleEndian(f,vide);	// toutes les couleurs sont importantes

//-------------- masques pour les champs  R G B A -------------------

// masques pour R G B A dans cet ordre qui est défini par BI_BITFILEDS

const int L = 4;
int m = L-1;
const unsigned long masquesRGBA[L] = { 0xFF000000,
									   0x00FF0000,
									   0x0000FF00,
									   0x000000FF};

const unsigned long * p;

int i;

for ( i = 0, p = masquesRGBA; i <= m; ++i, ++p) ecritLittleEndian(f,*p);

}

//------------------------------------------------------------------------------------------------------

/**
 * TACHE : écrit sur f le tableau de pixels
 *
 * DONNEES : pixels : la matrice de pixels
 * 			 nombreLignes : nombre de lignes de la matrice = hauteur de l'image mesurée en pixrels
 *           nombreColonnes : nombre de colonnes de la matric = largeur de l'image mesurée en pixels
 *
 * RESULTATS : f modifié
 *
 * CONVENTIONS :
 *
 * coin haut gauche = pixels[0]
 * coin haut droit  = pixels[nombreColonnes-1]
 * coin bas  gauche = pixels[nombreColonnes*(nombreLignes-1)]
 * coin bas  droit  = pixels[nombreColonnes*nombreLignes-1]
 *
 * NOTE : le tableau pixels est considéré comme bidimensionnel bien que stocké comme un tableau unidimensionnel.
 * en fait "pixels" est un pointeur vers le coin haut gauche de la matrice de pixels
 *
 * Attention !!! dans f on remplit de bas en haut et de gauche à droite
 * */
/*static*/ void OutilsCreationImage::creeTableauPixels1( iostream & f, const unsigned long pixels[],
							   const unsigned long nombreLignes, const unsigned long nombreColonnes)
{
unsigned long i;
const unsigned long * p;
for ( i = 0, p = pixels+(nombreLignes-1)*nombreColonnes; i < nombreLignes; ++i, p-=nombreColonnes) // on parcourt l'image de bas en haut
	{
	unsigned long j;
	const unsigned long * q;
	for ( j = 0, q = p; j < nombreColonnes; ++j, ++q)	// puis de la gauche vers la droite
		ecritLittleEndian(f,*q);
	}
}

//-------------------------------------------------------------------------------------------

/**
 * TACHE : écrit sur f le tableau de pixels
 *
 * DONNEES : pixels : la matrice de pixels
 * 			 nombreLignes : nombre de lignes de la matrice = hauteur de l'image mesurée en pixrels
 *           NOMBRE_COLONNES : nombre de colonnes de la matric = largeur de l'image mesurée en pixels
 *
 * RESULTATS : f modifié
 *
 * CONVENTIONS :
 *
 * coin haut gauche = pixels[0][0]
 * coin haut droit  = pixels[0][NOMBRE_COLONNES-1]
 * coin bas  gauche = pixels[nombreLignes-1][0]
 * coin bas  droit  = pixels[nombreLignes-1][NOMBRE_COLONNES-1]
 *
 * NOTE : le tableau pixels est  bidimensionnel.
 * en fait "pixels" est un pointeur vers le coin haut gauche de la matrice de pixels
 *
 * Attention !!! dans f on remplit de bas en haut et de gauche à droite
 * */
/*template <int NOMBRE_COLONNES>
static void OutilsCreationImage::creeTableauPixels( iostream & f, const unsigned long (*pixels)[NOMBRE_COLONNES],
							   const unsigned long nombreLignes)*/

