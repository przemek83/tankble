#include "water.h"
#include "../config.h"

Water::Water(){
	this->id = 2;
	this->fly = true;
	this->drive = false;
	this->armor = 0;
	this->source = "image/plansza/plansza_woda.tga";
	if(!loadBitmap()){
		cout << "Bricks Error" << "\n";
		exit(0);
	this->armorUp=0;
	this->levelUp=0;
	this->speedUp=0;
	this->tankUp=0;
	}
}
