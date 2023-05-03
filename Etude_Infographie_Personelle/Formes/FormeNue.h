#pragma once
#include "Forme.h"

class FormeNue : public Forme {
public:
	const static unsigned long COULEUR_DEFAUT = 0x00000000;
	vector<Vecteur2D*> position;
	Vecteur2D* vitesse;
	Vecteur2D* acceleration;
	unsigned long couleur;

	FormeNue(Vecteur2D& vit, Vecteur2D& acc = *new Vecteur2D()) : vitesse(&vit), acceleration(&acc), couleur(COULEUR_DEFAUT) {}

	~FormeNue() {
		delete vitesse;
		delete acceleration;
		size_t taille = position.size();
		for (size_t i = 0; i < taille; i++) {
			delete position.at(i);
		}
	}

	//--------------------------M�thodes Red�finies Importantes-------------------------

	/**
	Mise � jour �ventuelle du Vecteur2D d'acc�l�ration de la forme
	La nature du calcul du Vecteur2D acc�l�ration de la forme est d�fini dans les classes d�riv�es
	A ce niveau le Vecteur2D acc�l�ration est mis � 0
	@param forme | la liste de toutes les formes en mouvement
	**/
	inline Vecteur2D* gestionAcceleration(vector<Forme*>& formes) override {
		Vecteur2D* nVec = new Vecteur2D(0, 0);
		*this->getAcceleration() + *nVec;
		return this->getAcceleration();
	}

	/**
	M�tohde red�finie.
	Gestion de l'�ventuelle collision entre la forme et le cadre d�finie par coingBG et coinHD
	@param coinBG | le coin du vecteur2D en bas � gauche
	@param coinHD | le coin du vecteur2D en haut � droite
	**/
	const void gestionCollisionContour(const Vecteur2D& coinBG, const Vecteur2D& coinHD) override {}

	/**
	M�thode Virtuelle pure.
	Gestion de l'�ventuelle collision entre this et les formes
	@param vec | Les formes ayant une collision
	@param forme | notre forme qui v�rifie sa collision avec les autres formes
	**/
	const void gestionCollisionFormes(vector<Forme*>& fo) override {}


	/**
	M�thode virtuelle pure.
	V�rifie si la forme entre dans la hit box de notre forme this
	@param f | forme
	@param this | forme
	**/
	const void hitBox(Forme& f) override {}

	/**
	M�tohde red�finie.
	D�finie la zone � peindre de cette forme, c'est-�-dire un rectangle contenant
	tous les pixels de la forme
	@param min | vecteur du point en bas � gauche
	@param max | vecteur du point en haut � droite
	**/
	const void getBord(Vecteur2D& min, Vecteur2D& max) override {}

	/**
	M�thode virtuelle pure
	Dessine la forme dans la matrice de pixel
	@param matrice2D | un pointeur sur le premier pixel de la matrice
	**/
	const void dessineForme(ImageTableau& matrice2D, const unsigned long couleur) override {}

	/**
	M�tohde red�finie.
	D�crit le nombre de points (Vecteur2D) exacte pour d�crire la forme
	@return int | le nombre de Vecteurs pour la forme, ici 0
	**/
	const int NombrePoints()const override {
		return 0;
	}

	const void nettoyageAnciennePosition(ImageTableau& matrice2D) override {}

	//-------------------Getteur et Setteur-------------------------

	/**
	Retourne la couleur de la forme
	@return unsigned long | la couleur par d�faut d'une forme est noir transparent
	**/
	unsigned long getCouleur() override {
		return couleur;
	}

	/**
	Ajoute la couleur de la forme
	@param couleur | la couleur de la forme
	**/
	const void setCouleur(const unsigned long c) override {
		couleur = c;
	}

	vector<Vecteur2D*>* getPosition() override {
		return &position;
	}

	void addPositon(Vecteur2D& vec) override {
		position.push_back(&vec);
	}

	Vecteur2D* getVitesse() override {
		return vitesse;
	}

	void setVitesse(Vecteur2D& vec) override {
		vitesse = &vec;
	}

	Vecteur2D* getAcceleration() override {
		return acceleration;
	}

	void setAcceleration(Vecteur2D& vec) override {
		acceleration = &vec;
	}

	operator string()const override {
		string oss = "FormeNue : [";
		for (Vecteur2D* p : position) {
			oss += (string)*p;
		}
		return oss + "] | Vitesse : " + (string)*vitesse + " | Acceleration : " + (string)*acceleration + "\n";
	}

	friend ostream& operator<<(ostream& s, const FormeNue& f);
};

inline ostream& operator<<(ostream& s, const FormeNue& f) {
	return s << (string)f;
}