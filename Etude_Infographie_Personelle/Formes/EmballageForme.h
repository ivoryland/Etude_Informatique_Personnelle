#pragma once
#include <cstdarg>
#include "Forme.h"

class EmballageForme : public Forme {
protected:
	Forme* forme;

public:
	//--------------------------Constructeur---------------------------------
	EmballageForme(Forme& f):forme(&f){}

	virtual ~EmballageForme() { delete forme; }

	//--------------------------M�thodes Red�finies Importantes-------------------------

	/**
	Mise � jour �ventuelle du Vecteur2D d'acc�l�ration de la forme
	La nature du calcul du Vecteur2D acc�l�ration de la forme est d�fini dans les classes d�riv�es
	A ce niveau le Vecteur2D acc�l�ration est mis � 0
	@param forme | la liste de toutes les formes en mouvement
	**/
	inline Vecteur2D* gestionAcceleration(vector<Forme*>& formes) override {
		*this->getAcceleration() + *forme->gestionAcceleration(formes);
		return this->forme->gestionAcceleration(formes);
	}

	/**
	M�tohde red�finie.
	Gestion de l'�ventuelle collision entre la forme et le cadre d�finie par coingBG et coinHD
	@param coinBG | le coin du vecteur2D en bas � gauche
	@param coinHD | le coin du vecteur2D en haut � droite
	**/
	const void gestionCollisionContour(const Vecteur2D& coinBG, const Vecteur2D& coinHD) override {
		this->forme->gestionCollisionContour(coinBG, coinHD);
	}

	/**
	M�thode Virtuelle pure.
	Gestion de l'�ventuelle collision entre this et les formes
	@param vec | Les formes ayant une collision
	@param forme | notre forme qui v�rifie sa collision avec les autres formes
	**/
	const void gestionCollisionFormes(vector<Forme*>& fo) override {
		this->forme->gestionCollisionFormes(fo);
	}

	/**
	M�thode virtuelle pure.
	V�rifie si la forme entre dans la hit box de notre forme this
	@param f | forme
	@param this | forme
	**/
	const void hitBox(Forme& f) override {
		this->forme->hitBox(f);
	}

	/**
	M�tohde red�finie.
	D�finie la zone � peindre de cette forme, c'est-�-dire un rectangle contenant
	tous les pixels de la forme
	@param min | vecteur du point en bas � gauche
	@param max | vecteur du point en haut � droite
	**/
	const void getBord(Vecteur2D& min, Vecteur2D& max) override {
		this->forme->getBord(min, max);
	}
	
	/**
	M�thode red�finie. 
	Dessine la forme dans la matrice de pixel
	@param matrice2D | un pointeur sur le premier pixel de la matrice
	**/
	const void dessineForme(ImageTableau& matrice2D, const unsigned long couleur) override {
		this->forme->dessineForme(matrice2D, couleur);
	}

	/**
	M�tohde red�finie.
	D�crit le nombre de points (Vecteur2D) exacte pour d�crire la forme
	@return int | le nombre de Vecteurs pour la forme, ici on ne sait pas
	**/
	const int NombrePoints()const override{
		return this->forme->NombrePoints();
	}

	const void nettoyageAnciennePosition(ImageTableau& matrice2D) override {
		this->forme->nettoyageAnciennePosition(matrice2D);
	}

	//------------------------Getteurs et Setteurs--------------------------------
	/**
	Retourne la couleur de la forme
	@return unsigned long | la couleur par d�faut d'une forme est noir transparent
	**/
	unsigned long getCouleur() override {
		return this->forme->getCouleur();
	}
	/**
	Ajoute la couleur de la forme
	@param couleur | la couleur de la forme
	**/
	const void setCouleur(const unsigned long c) override {
		this->forme->setCouleur(c);
	}

	vector<Vecteur2D*>* getPosition() override {
		return this->forme->getPosition();
	}

	void addPositon(Vecteur2D& vec) override {
		this->forme->addPositon(vec);
	}

	Vecteur2D* getVitesse() override {
		return this->forme->getVitesse();
	}

	void setVitesse(Vecteur2D& vec) override {
		*(this->forme->getVitesse()) = vec;
	}

	Vecteur2D* getAcceleration() override {
		return this->forme->getAcceleration();
	}

	void setAcceleration(Vecteur2D& vec) override {
		*(this->forme->getAcceleration()) = vec;
	}

	operator string()const override {
		return (string)*this->forme;
	}
	friend ostream& operator<<(ostream& s, const EmballageForme& f);
};

inline ostream& operator<<(ostream& s, const EmballageForme& f) {
	return s << (string)f;
}