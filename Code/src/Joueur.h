#pragma once

#include "Dynamic.h"
#include "Unite.h"

class Joueur : public Unite	//lien temporaire pour pouvoir faire marcher pickup
{
public:
	Joueur();
	void SetALAbri(bool abri);

private:
	bool aLAbri = false;
};

