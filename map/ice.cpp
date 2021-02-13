#include "ice.h"
#include <iostream>

Ice::Ice(){
	this->id = 4;
	this->fly = true;
	this->drive = true;
	this->armor = 999;
	this->source = "image/plansza/plansza_lod.tga";
	if(!loadBitmap()){
		exit(0);
	}
	this->armorUp=0;
	this->levelUp=0;
	this->speedUp=0;
	this->tankUp=0;
}
