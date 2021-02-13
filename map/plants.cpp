#include "plants.h"
#include <iostream>


Plants::Plants(){
	this->id = 3;
	this->fly = true;
	this->drive = true;
	this->armor = 999;
	this->source = "image/plansza/plansza_zielsko.tga";
	if(!loadBitmap()){
		exit(0);
	}
	this->armorUp=0;
	this->levelUp=0;
	this->speedUp=0;
	this->tankUp=0;
}
