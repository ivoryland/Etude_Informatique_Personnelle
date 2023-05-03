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
	* RESULTAT : un nombre al�atoire x tel que 0 <= x < 1
	*
	* suppose qu'un appel � srand a �t� fait au pr�alable
	*
	* */
inline static double random(){
	
	return rand() / (double)RAND_MAX;
}


//-------------------------------------------------------------------------------------------------

/**
	* g�n�re une valeur al�atoire qui suit la loi normale centr�e r�duite
	*
	* Il faut faire un appel � srand() au pr�alable.
	*
	* Box Muler
	* */
inline static double randomGaussienneNormalisee()
{
	double u1 = random();            // valeur g�n�r�e suivant la loi uniforme ?
	double u2 = random();            // valeur g�n�r�e suivant la loi uniforme ?
	double r = sqrt(-2 * log(1 - u1));

	if (r == INFINITY || r == -INFINITY) return randomGaussienneNormalisee();

	double arg = cos(DEUXPI * u2);
	return r * arg;
}
