#include <iostream>
#include "Outils/Outils_math/Vecteur2D.h"
#include "Outils/Outils_Image/IterateurImages.h"
#include "Outils/Outils_Image/OutilsCreationImage.h"
#include "Formes/FormeNue.h"
#include "Formes/Segment.h"
#include "Formes/DisqueCreux.h"
#include "Formes/DisquePlein.h"
#include "Formes/BSpline.h"
#include "Formes/PolygoneCreux.h"
#include "Formes/RectanglePlein.h"
#include "Formes//CollisionContour.h"

using namespace std;

int main() {
	const int HAUTEUR = 240;
	const int LARGEUR = 400;
	const int HAUTEURM1 = HAUTEUR - 1;
	const int LARGEURM1 = LARGEUR - 1;

	const int HAUTEUR2 = HAUTEUR / 2;
	const int LARGEUR2 = LARGEUR / 2;

	const unsigned long noirTransparent = 0x00000000;
	const unsigned long rouge = 0xFF0000FF;
	const unsigned long bleu = 0x0000FFFF;

	unsigned long matrice2D[HAUTEUR][LARGEUR];

	int i, j;
	for (i = 0; i < HAUTEUR; i++) {
		for (j = 0; j < LARGEUR; j++) {
			matrice2D[i][j] = noirTransparent;
		}
	}

	ImageTableau imageTableau((unsigned long*)matrice2D, HAUTEURM1, LARGEURM1, LARGEUR);

	vector<Forme*> forme;
	//TODO : vector<Vecteur2D*> c'est de la merde
	vector<Vecteur2D*> postitionSeg;
	postitionSeg.push_back(new Vecteur2D(0, LARGEUR2));
	postitionSeg.push_back(new Vecteur2D(130, 45));
	postitionSeg.push_back(new Vecteur2D(200, 45));
	postitionSeg.push_back(new Vecteur2D(220, LARGEUR2));

	Forme* forme1 = new CollisionContour(
						*(Forme*)new FormeNue(*new Vecteur2D(20,-10)), 1);
	//Forme* forme2 = new BSpline(*new PolygoneCreux(*forme1, 7, new Vecteur2D(0, LARGEUR2), new Vecteur2D(130, 45), 
	//										new Vecteur2D(200, 45), new Vecteur2D(220, LARGEUR2), 
	//										new Vecteur2D(200, 355), new Vecteur2D(130, 355),
	//										new Vecteur2D(0, LARGEUR2)), 0
	//);
	Forme* forme2 = new RenctanglePlein(*forme1, 2, new Vecteur2D(0, LARGEUR2), new Vecteur2D(130, 45));
	cout << "Forme : \n" << *forme2 << endl;

	string chemin = "C:\\Users\\rom98\\source\\repos\\Image"; // chemin relatif du dossier de sauvegarde :
	string nomFichierImage = chemin + "\\" + "segment";
	string finalName;

	double deltaT = 0.2;
	i = 0, j = 0;
	bool fin = true;
	while (i < 100) {
		forme2->dessineForme(imageTableau, rouge);
		finalName = nomFichierImage + to_string(i) + ".bmp";
		OutilsCreationImage::creeImage(finalName, matrice2D, HAUTEUR);
		forme2->update(deltaT);
		forme2->gestionCollisionContour(Vecteur2D(0, 0), Vecteur2D(HAUTEUR, LARGEUR));
		forme2->nettoyageAnciennePosition(imageTableau);
		i++;
	}

	return 0;
}