/*
 * OutilsCreationImage.h
 *
 *  Created on: 26 juil. 2020
 *      Author: Dom
 */

#ifndef OUTILSCREATIONIMAGE_H_
#define OUTILSCREATIONIMAGE_H_

#include <iostream>
#include <fstream>

using namespace std;

/**
 *
 * Crée au format BMP  des images où chaque pixel est codé sur 4 octets RGBA
 *
 * les nombres entiers sont tous non signés et inscrits dans l'ordre little endian
 *
 * */
class OutilsCreationImage
{
public:
static const unsigned long TAILLE_HEADER; // en octets = 14;
static const unsigned long TAILLE_DIB; // en octets = 56; //  correspond à BITMAPV3INFOHEADER
static const unsigned long BI_BITFIELDS; // = 3; // méthode de compression : pas de compression car les pixels sont codés sur 32 bits

//-------------------------------------------------------------------------------------------

/**
 * HYPOTHESES :
 * on suppose que f est ouvert en mode binaire en écriture
 * on suppose que T = unsigned short ou T = unsigned long
 * TACHE : écrit x en little endian sur f
 * DONNEES : f, x
 * RESULTATS : f modifié
 * */
template <class T>
static void ecritLittleEndian( iostream & f, const T & x, const int nombreOctets = sizeof(T))
{
const char * s = (const char *)&x;
f.write(s, nombreOctets);
}

//-------------------------------------------------------------------------------------------

/**
 * HYPOTHESES :
 * on suppose que f est ouvert en mode binaire en lecture
 * on suppose que T = unsigned short ou T = unsigned long
 * TACHE : lit un élément x de type T en little endian sur f
 * DONNEES : f
 * RESULTATS : f modifié et x par return
 * */
template <class T>
static T litLittleEndian( iostream & f,  const int nombreOctets = sizeof(T))
{
T x;
f.read((char *)&x, nombreOctets);
return x;
}

//-------------------------------------------------------------------------------------------

/**
 * Ecrit sur f l'entête Bitmap file header
 * On suppose que f est ouvert en écriture en mode binaire
 *
 * écrit 14 octets en tout sur f
 *
 * prend l'entête DIB BITMAPV3INFOHEADER (pour disposer du canal alpha (= opacité))
 *
 * DONNEES : tailleFichierCompletNombreOctets : mesuré en octets
 * */
static void creeBMPFileHeader(iostream & f, const unsigned long tailleFichierCompletNombreOctets)
{
const char * nom = "BM";
f.write(nom,2); // écrit sur f les 2 caractères du mot "BM"

ecritLittleEndian(f,tailleFichierCompletNombreOctets);
// écrit en mode little endian les 4 octets du nombre tailleFichierCompletNombreOctets

const unsigned long vide = 0;
ecritLittleEndian(f,vide); // écrit 0 sur 4 octets consécutifs

unsigned long offsetTableauPixel = TAILLE_HEADER + TAILLE_DIB; //0x46; // = 70 = 14 + 56 (décimal) car on prend l'entête DIB BITMAPV3INFOHEADER
										//adresse où commmence le tableau de pixels (comptée à partir du début du fichier), (multiple de 4 ?)

ecritLittleEndian(f,offsetTableauPixel);
// écrit en mode little endian offsetTableauPixel sur 4 octets consécutifs
}

//-------------------------------------------------------------------------------------------

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
static void creeBMPDIBHeader(iostream & f,
							 const unsigned long largeurEnPixels,
							 const unsigned long hauteurEnPixels,
							 const unsigned long tailleTableauPixels,
							 const unsigned long densiteHorizontale = 100,
							 const unsigned long densiteVerticale = 100);

//-------------------------------------------------------------------------------------------

/**
 * HYPOTHESES : On suppose que f est ouvert en écriture en mode binaire
 *
 * TACHE : crée sur f le début du fichier au format BMP contenant une image. crée donc sur f le BMP HEADER puis le DIB HEADER.
 *
 * DONNEES :
 *            nombreColonnes : nombre de colonnes du tableau de pixels = largeur de l'image mesurée en pixels
 *            nombreLignes : nombre de lignes du tableau de pixels = hauteur de l'image mesurée en pixels
 *			  densiteHorizontale
 *			  densiteVerticale
 * densiteHorizontale  mesurée en pixels/m  si densiteHorizontale = densiteVerticale = 100 <===> largeur pixel = hauteur pixel = 1 cm
 *
 * RESULTATS : f partiellement rempli au format BMP : uniquement les 2 headers BMP et DIB ont été inscrits.
 * Le curseur de f est positionné en fin de fichier donc prêt à remplir le tableau bidimensionnel de pixels
 *
 * OPTIONS FIXEES :
 *
 * le DIB choisi est BITMAPV3INFOHEADER
 *
 * et la méthode de compression est BI_BITFIELDS
 * la profondeur des pixels est 32 bits = 4 octets RGBA avec 1 octet par canal
 *
 * */
inline static void creeBMPFileHeaderEtBMPDIBHeader( iostream & f,
		               const unsigned long nombreColonnes, const unsigned long nombreLignes,
		               const unsigned long densiteHorizontale = 100, const unsigned long densiteVerticale = 100)
{
unsigned long tailleTableauOctets = nombreLignes*nombreColonnes*sizeof(long);
unsigned long tailleTotaleFichierOctets = TAILLE_HEADER + TAILLE_DIB + tailleTableauOctets; // en octets

creeBMPFileHeader( f, tailleTotaleFichierOctets);

creeBMPDIBHeader( f, nombreColonnes, nombreLignes, tailleTableauOctets, densiteHorizontale, densiteVerticale);
}

//-------------------------------------------------------------------------------------------

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
static void creeTableauPixels1( iostream & f, const unsigned long pixels[],
							   const unsigned long nombreLignes, const unsigned long nombreColonnes);

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
template <int NOMBRE_COLONNES>
static void creeTableauPixels( iostream & f, const unsigned long (*pixels)[NOMBRE_COLONNES],
							   const unsigned long nombreLignes)
{
unsigned long i;
const unsigned long (* p)[NOMBRE_COLONNES];
for ( i = 0, p = pixels + nombreLignes-1; i < nombreLignes; ++i, --p) // on parcourt l'image de bas en haut
	{
	unsigned long j;
	const unsigned long * q;
	for ( j = 0, q = (const unsigned long *)p; j < NOMBRE_COLONNES; ++j, ++q)	// puis de la gauche vers la droite
		ecritLittleEndian(f,*q);
	}
}

//-------------------------------------------------------------------------------------------

/**
 * HYPOTHESES : On suppose que f est ouvert en écriture en mode binaire
 *
 * TACHE : crée f le fichier au format BMP contenant l'image définie par le tableau de pixels "pixels"
 *
 * DONNEES : pixels : le tableau bidimensionnel de pixels représentant l'image
 *           nombreLignes : nombre de lignes du tableau pixels = hauteur de l'image mesurée en pixels
 *           nombreColonnes : nombre de colonnes du tableau pixels = largeur de l'image mesurée en pixels
 *			 densiteHorizontale
 *			 densiteVerticale
 * densiteHorizontale  mesurée en pixels/m  si denstitéHorizontale = densiteVerticale = 100 <===> largeur pixel = hauteur pixel = 1 cm
 *
 * RESULTATS : f rempli au format BMP
 *
 * OPTIONS FIXEES :
 *
 * le DIB choisi est BITMAPV3INFOHEADER
 *
 * et la méthode de compression est BI_BITFIELDS
 * la profondeur des pixels est 32 bits = 4 octets RGBA avec 1 octet par canal
 *
 * NOTE : le tableau pixels est considéré comme bidimensionnel bien que stocké comme un tableau unidimensionnel.
 * en fait "pixels" est un pointeur vers le coin haut gauche de la matrice de pixels
 * */
static void creeImage1( iostream & f, const unsigned long pixels[],
		               const unsigned long nombreLignes, const unsigned long nombreColonnes,
		               const unsigned long densiteHorizontale = 100, const unsigned long densiteVerticale = 100)
{
creeBMPFileHeaderEtBMPDIBHeader( f, nombreColonnes, nombreLignes, densiteHorizontale, densiteVerticale);
creeTableauPixels1( f, pixels, nombreLignes, nombreColonnes);
}

//-------------------------------------------------------------------------------------------

/**
 * HYPOTHESES : On suppose que f est ouvert en écriture en mode binaire
 *
 * TACHE : crée f le fichier au format BMP contenant l'image définie par le tableau de pixels "pixels"
 *
 * DONNEES : pixels : le tableau bidimensionnel de pixels représentant l'image
 *           nombreLignes : nombre de lignes du tableau pixels = hauteur de l'image mesurée en pixels
 *           NOMBRE_COLONNES : nombre de colonnes du tableau pixels = largeur de l'image mesurée en pixels
 *			 densiteHorizontale
 *			 densiteVerticale
 * densiteHorizontale  mesurée en pixels/m  si denstitéHorizontale = densiteVerticale = 100 <===> largeur pixel = hauteur pixel = 1 cm
 *
 * RESULTATS : f rempli au format BMP
 *
 * OPTIONS FIXEES :
 *
 * le DIB choisi est BITMAPV3INFOHEADER
 *
 * et la méthode de compression est BI_BITFIELDS
 * la profondeur des pixels est 32 bits = 4 octets RGBA avec 1 octet par canal
 *
 * NOTE : le tableau pixels est bidimensionnel.
 * en fait "pixels" est un pointeur vers le coin haut gauche de la matrice de pixels
 * */
template <int NOMBRE_COLONNES>
static void creeImage( iostream & f, const unsigned long (*pixels)[NOMBRE_COLONNES],
		               const unsigned long nombreLignes,
		               const unsigned long densiteHorizontale = 100, const unsigned long densiteVerticale = 100)
{
creeBMPFileHeaderEtBMPDIBHeader( f, NOMBRE_COLONNES, nombreLignes, densiteHorizontale, densiteVerticale);
creeTableauPixels( f, pixels, nombreLignes);
}

/*
{
unsigned long tailleTableau = nombreLignes*NOMBRE_COLONNES*sizeof(long);
unsigned long tailleTotaleFichier = TAILLE_HEADER + TAILLE_DIB + tailleTableau; // en octets
creeBMPFileHeader( f, tailleTotaleFichier);

creeBMPDIBHeader( f, NOMBRE_COLONNES, nombreLignes, tailleTableau, densiteHorizontale, densiteVerticale);
creeTableauPixels( f, pixels, nombreLignes);
}
*/


//-------------------------------------------------------------------------------------------

/**
 * HYPOTHESES : On suppose que nomFichierImage a une extension .bmp
 *
 * TACHE : crée  le fichier au format BMP contenant l'image définie par le tableau de pixels "pixels"
 *
 * DONNEES :
 * 			 nomFichierImage : nom du fichier disque qui va contenir la sauvegarde de l'image. doit avoir l'extension .bmp
 * 			 pixels : le tableau bidimensionnel de pixels représentant l'image
 *           nombreLignes : nombre de lignes du tableau pixels = hauteur de l'image mesurée en pixels
 *           NOMBRE_COLONNES : nombre de colonnes du tableau pixels = largeur de l'image mesurée en pixels
 *			 densiteHorizontale
 *			 densiteVerticale
 * densiteHorizontale  mesurée en pixels/m  si denstitéHorizontale = densiteVerticale = 100 <===> largeur pixel = hauteur pixel = 1 cm
 *
 * RESULTATS : le fichier de nom nomFichierImage rempli au format BMP
 *
 * OPTIONS FIXEES :
 *
 * le DIB choisi est BITMAPV3INFOHEADER
 *
 * et la méthode de compression est BI_BITFIELDS
 * la profondeur des pixels est 32 bits = 4 octets RGBA avec 1 octet par canal
 *
 * NOTE : le tableau pixels est bidimensionnel.
 * en fait "pixels" est un pointeur vers le coin haut gauche de la matrice de pixels
 * */
template <int NOMBRE_COLONNES>
static void creeImage( const string & nomFichierImage, const unsigned long (*pixels)[NOMBRE_COLONNES],
		               const unsigned long nombreLignes,
		               const unsigned long densiteHorizontale = 100, const unsigned long densiteVerticale = 100)
{
fstream f(nomFichierImage,ios::out|ios::binary); // ouverture en lecture et écriture seule et en mode binaire

OutilsCreationImage::creeImage( f, pixels, nombreLignes, densiteHorizontale, densiteVerticale);		// sauve l'image sur le fichier f

f.close();
}


};

#endif /* OUTILSCREATIONIMAGE_H_ */
