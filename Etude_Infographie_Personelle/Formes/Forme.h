#pragma once
#include <vector>
#include "../Outils/Outils_math/Vecteur2D.h"
#include "../Outils/Outils_math/CinematiqueVectorielle2D.h"
#include "../Outils/Outils_Image/IterateurImages.h"

/**
Classe Forme.h
**/
class Forme {

public:

	virtual ~Forme(){}
	//--------------------Méthodes par Défauts--------------------------------
	/**
	Mise à jour de la position et de la vitesse de la forme
	Modifie le Vecteur2D position et vitesse
	Le Vecteur2D d'accélération n'est pas touché
	**/
	void update(const double deltaT) {
		for (Vecteur2D* pos : *this->getPosition()) {
			mouvementUniformeAccelere(*pos, *this->getVitesse(), *this->getAcceleration(), deltaT);
		}
	}

	//--------------------Méthodes Vituelles pure--------------------------------

	/**
	Métohde Virtuelle pure. 
	Mise à jour éventuelle du Vecteur2D d'accélération de la forme
	La nature du calcul du Vecteur2D accélération de la forme est défini dans les classes dérivées
	A ce niveau le Vecteur2D accélération est mis à 0
	@param forme | la liste de toutes les formes en mouvement
	**/
	virtual inline Vecteur2D* gestionAcceleration(vector<Forme*>& formes) = 0;

	/**
	Métohde Virtuelle pure. 
	Gestion de l'éventuelle collision entre la forme et le cadre définie par coingBG et coinHD
	@param coinBG | le coin du vecteur2D en bas à gauche
	@param coinHD | le coin du vecteur2D en haut à droite
	**/
	virtual const void gestionCollisionContour(const Vecteur2D& coinBG, const Vecteur2D& coinHD) = 0;

	/**
	Méthode Virtuelle pure. 
	Gestion de l'éventuelle collision entre this et les formes
	@param vec | Les formes ayant une collision
	@param forme | notre forme qui vérifie sa collision avec les autres formes
	**/
	virtual const void gestionCollisionFormes(vector<Forme*>& fo) = 0;

	/**
	Méthode virtuelle pure. 
	Vérifie si la forme entre dans la hit box de notre forme this
	@param f | forme
	@param this | forme
	**/
	virtual const void hitBox(Forme& f) = 0;

	/**
	Métohde Virtuelle pure. 
	Définie la zone à peindre de cette forme, c'est-à-dire un rectangle contenant
	tous les pixels de la forme
	@param min | vecteur du point en bas à gauche
	@param max | vecteur du point en haut à droite
	**/
	virtual const void getBord(Vecteur2D& min, Vecteur2D& max) = 0;

	/**
	Méthode virtuelle pure
	Dessine la forme dans la matrice de pixel
	@param matrice2D | un pointeur sur le premier pixel de la matrice
	**/
	virtual const void dessineForme(ImageTableau& matrice2D, const unsigned long couleur) = 0;

	/**
	Métohde Virtuelle pure.
	Décrit le nombre de points (Vecteur2D) exacte pour décrire la forme
	@return int | le nombre de Vecteurs pour la forme
	**/
	virtual const int NombrePoints()const = 0;

	virtual const void nettoyageAnciennePosition(ImageTableau& matrice2D) = 0;

	//--------------------------Getteur et Setteur--------------------------

	virtual unsigned long getCouleur() = 0;
	
	virtual const void setCouleur(const unsigned long couleur) = 0;

	virtual vector<Vecteur2D*>* getPosition() = 0;

	virtual void addPositon(Vecteur2D& vec) = 0;

	virtual Vecteur2D* getVitesse() = 0;

	virtual void setVitesse(Vecteur2D& vec) = 0;

	virtual Vecteur2D* getAcceleration() = 0;

	virtual void setAcceleration(Vecteur2D& vec) = 0;

	/**
	* Decrit la Forme dans son integralitée (methode virtual pure, a implementer dans une classe Fille)
	* @return string qui est la description d'une forme
	**/
	virtual operator string()const = 0;

	/**
	* Decrit la forme au niveau initiale de l'heritage
	* @return ostream& qui est le flux d'une forme
	**/
	friend ostream& operator<<(ostream& s, const Forme& f);
};

inline ostream& operator<<(ostream& s, const Forme& f) {
	return s << (string)f;
}