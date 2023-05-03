#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

class Visiteur;

using namespace std;

class Vecteur2D
{
public:
	/**
	* representation d'un point orthonorme (x, y) dans un plan 2D
	**/
	double x, y;

	//-----------------------Constructeur---------------------------------------

	/**
	* Constructeur par defaut de la classe Vecteur 
	* @param double& x, double y (deux coordonnées dans un plans 2D)
	**/
	inline Vecteur2D(const double& x = 0, const double& y = 0);
	//inline Vecteur(const string& s, const string& delimeter);

	//-----------------------Methode Operator-----------------------------------


	/**
	* Additionne les x et y distinctement des deux vecteurs differents (this et en parametre)
	* @param this, Vecteur& (deux vecteurs representant deux points orthonormes (x, y) dans l'espace monde)
	* @return Vecteur (la somme des deux points)
	**/
	inline const Vecteur2D operator + (const Vecteur2D& v) const;

	/**
	* soustraction d'un vecteur par un autre vecteur
	* @param this, Vecteur
	* @return Vecteur (la soutraction des deux vecteurs)
	**/
	inline const Vecteur2D operator - (const Vecteur2D& vec) const;



	/**
	* Multiplie les x et y par la valeur passee en paramatre
	* @param double, this (vecteur representant deux points orthonormes (x, y) dans l'espace monde)
	* @return Vecteur (le produit de this par a)
	**/
	inline const Vecteur2D operator * (const double a) const;


	/**
	cherche le plus petit x et y parmis deux vecteurs
	@param Vecteur& v, this (deux vecteurs en comparaison)
	@return Vecteur (le plus petit parmi les deux)
	**/
	inline const Vecteur2D operator < (const Vecteur2D& v)const;

	/**
	cherche le plus petit x et y < double
	@param Vecteur& v, this (deux vecteurs en comparaison)
	@return Vecteur (le plus petit parmi les deux)
	**/
	inline const Vecteur2D operator < (const double v)const;

	/**
	cherche le plus petit x et y < double
	@param Vecteur& v, this (deux vecteurs en comparaison)
	@return Vecteur (le plus petit parmi les deux)
	**/
	inline const Vecteur2D operator > (const double v)const;

	/**
	cherche le plus grand x et y parmis deux vecteurs
	@param Vecteur& v, this (deux vecteurs en comparaison)
	@return Vecteur (le plus grand parmi les deux)
	**/
	inline const Vecteur2D operator > (const Vecteur2D& v)const;

	/**
	* produit scalaire du vecteur this et celui donné en @param
	* @param Vecteur& (represent un point orthonorme (x, y) dans l'espace monde)
	* @return double (le sclalaire des deux vecteurs)
	**/
	inline const double operator * (const Vecteur2D& v) const;


	/**
	* Addition et affectation a this du vecteur passe en parametre
	* @param this et Vecteur& (deux vecteurs representant deux points orthonormes (x, y) dans l'espace monde)
	* @return Vecteur (this += Vecteur&)
	**/
	inline Vecteur2D operator +=(const Vecteur2D& vec);


	/**
	* divisione d'un vecteur par une valeur (double)
	* @param this, double (double etant le diviseur)
	* @return Vecteur
	**/
	inline const Vecteur2D operator /(const double a) const;


	/**
	* - unaire (c'est-à-dire opposé d'un vecteur)
	**/
	inline const Vecteur2D operator - () const;

	/**
	* 
	**/
	inline const bool operator== (const Vecteur2D& vec) const;


	/**
	* decrit le vecteur (x, y)
	* @return string (description du vecteur)
	**/
	inline operator string() const;


	//-----------------------Methode Standard-----------------------------------


	/**
	* methode clone standard a partir de la classe existante (!!!!! Attention operation couteuse !!!!!) 
	* A utiliser uniquement si on veut deux vecteurs distints et avec une adresse differente
	* @return new Vecteur*
	**/
	inline Vecteur2D* clone()const { return new Vecteur2D(*this); }


	//-----------------------Methode de classe-----------------------------------


	/**
	* calcule le determinant de deux vecteurs
	* @param this, Vecteur& (deux vecteurs representant deux points orthonormes (x, y) dans l'espace monde)
	* @return double (determinant de deux vecteurs)
	**/
	const double determinant(const Vecteur2D& vec) const;

	/**
	* Arrondi x et y 
	*/
	inline const void arroundi();

	/**
	* La norme carrée du vecteur
	* @return double -> (x*x) + (y*y)
	*/
	inline const double norme2()const;
	/*
	fournit une base orthornormée directe associée à this
	vecteurUnitaire est un vecteur unitaire colineaire et de meme sens que this
	et base est tel que base soit le résultat de la rotation d'angle de +PI/2 par rapport à vecteurUnitaire
	**/
	inline Vecteur2D base();

	/**
	Rotation d'un quart de tour (+ PI/2)
	**/
	inline Vecteur2D rotationQuartDeTour();

	/**
	* Permet la visite et la modification de variable dans la classe a l'aide d'un visiteur
	* @params le visiteur qui modifie la classe en fonction de sa propriété
	*/
	const void accepte(const Visiteur& visiteur);

	/**
	* permet l'ecriture dans le flux d'un vecteur
	* @param Vecteur&
	* @return ostream& (flux d'ecriture)
	**/
	friend ostream& operator<<(ostream& s, const Vecteur2D& v);
}; // classe Vecteur2D.h


inline const Vecteur2D operator *(const double& a, const Vecteur2D& u) { return u * a; }

//------------ implémentation des fonctions inline ----------------------

inline Vecteur2D::Vecteur2D(const double& x, const double& y) : x(x), y(y) {}

template <class T>
inline const T operator - (const T& u, const T& v) {
	return u + -v;
}

inline const Vecteur2D Vecteur2D::operator+(const Vecteur2D& v) const {
	return Vecteur2D(x + v.x, y + v.y);
}

inline const Vecteur2D Vecteur2D::operator * (const double a) const {
	return Vecteur2D(x * a, y * a);
}

inline const Vecteur2D Vecteur2D::operator<(const Vecteur2D& v) const {
	return Vecteur2D(x < v.x ? x : v.x,  y < v.y ? y : v.y);
}

inline const Vecteur2D Vecteur2D::operator>(const Vecteur2D& v) const {
	return Vecteur2D(x > v.x ? x : v.x, y > v.y ? y : v.y);
}

inline const Vecteur2D Vecteur2D::operator<(const double v) const {
	return Vecteur2D(x < v ? x : v, y < v ? y : v);
}

inline const Vecteur2D Vecteur2D::operator>(const double v) const {
	return Vecteur2D(x > v ? x : v, y > v ? y : v);
}

inline const double Vecteur2D::operator*(const Vecteur2D& v) const {
	return x * v.x + y * v.y;
}

inline Vecteur2D Vecteur2D::operator+=(const Vecteur2D& vec) {
	return Vecteur2D(x += vec.x, y += vec.y);
}

inline const Vecteur2D Vecteur2D::operator / (const double a) const{
	return Vecteur2D(x / a, y / a);
}

inline const Vecteur2D Vecteur2D::operator - () const {
	return Vecteur2D(-x, -y);
}

inline const Vecteur2D Vecteur2D::operator-(const Vecteur2D& vec) const {
	return Vecteur2D(x - vec.x, y - vec.y);
}

inline const bool Vecteur2D::operator==(const Vecteur2D& vec) const{
	int _x = round(x), _y = round(y);
	int _vx = round(vec.x), _vy = round(vec.y);
	return (_x == _vx) && (_y == _vy);
}

inline Vecteur2D::operator string() const {
	ostringstream oss;
	oss << "Vecteur[" << x << ":" << y << "]";
	return oss.str();
}

inline const double Vecteur2D::determinant(const Vecteur2D& vec) const {
	return ((x * vec.y) - (y * vec.x));
}

inline const void Vecteur2D::arroundi() {
	x = round(x);
	y = round(y);
}

inline const double Vecteur2D::norme2() const {
	return (x*x) + (y*y);
}

inline Vecteur2D Vecteur2D::base()
{
	double d = sqrt(this->norme2());
	Vecteur2D vecteurUnitaire = *this * (1 / d);
	return vecteurUnitaire.rotationQuartDeTour();
}

inline Vecteur2D Vecteur2D::rotationQuartDeTour() {
	return Vecteur2D(-y, x);
}


inline ostream& operator << (ostream& os, const Vecteur2D& u) {
	os << (string)u;
	return os;
}