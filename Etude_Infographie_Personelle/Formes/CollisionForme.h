#pragma once
#include "EmballageForme.h"
class CollisionForme : public EmballageForme {
public:
	CollisionForme(Forme& f) : EmballageForme(f){}

	/**
	M�thode Virtuelle pure.
	Gestion de l'�ventuelle collision entre this et les formes
	@param vec | Les formes ayant une collision
	@param forme | notre forme qui v�rifie sa collision avec les autres formes
	**/
	const void gestionCollisionFormes(vector<Forme*> fo) {

	}
};