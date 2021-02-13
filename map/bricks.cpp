#include "bricks.h"
#include <iostream>

Bricks::Bricks(){
	this->id = 1;
	this->fly = false;
	this->drive = false;
	this->armor = 2;
	this->source = "image/plansza/plansza_cegla.tga";
	if(!loadBitmap()){
		exit(0);
	this->armorUp=0;
	this->levelUp=0;
	this->speedUp=0;
	this->tankUp=0;
	}
}
