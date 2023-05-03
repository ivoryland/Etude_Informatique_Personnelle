#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <time.h>
#include <stdlib.h>

const static double DEUXPI = M_PI * 2;

inline static void initRandom() {
	srand(time(NULL));
}

/**
	*
	* RESULTAT : un nombre aléatoire x tel que 0 <= x < 1
	*
	* suppose qu'un appel à srand a été fait au préalable
	*
	* */
inline static double random(){
	
	return rand() / (double)RAND_MAX;
}


//-------------------------------------------------------------------------------------------------

/**
	* génère une valeur aléatoire qui suit la loi normale centrée réduite
	*
	* Il faut faire un appel à srand() au préalable.
	*
	* Box Muler
	* */
inline static double randomGaussienneNormalisee()
{
	double u1 = random();            // valeur générée suivant la loi uniforme ?
	double u2 = random();            // valeur générée suivant la loi uniforme ?
	double r = sqrt(-2 * log(1 - u1));

	if (r == INFINITY || r == -INFINITY) return randomGaussienneNormalisee();

	double arg = cos(DEUXPI * u2);
	return r * arg;
}
