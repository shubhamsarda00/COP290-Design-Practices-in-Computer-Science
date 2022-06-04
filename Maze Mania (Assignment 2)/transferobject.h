/*
 * transferobject.h
 *
 *  Created on: 16-Apr-2022
 *      Author: shubham
 */

#ifndef ASSIGNMENT2_TRANSFEROBJECT_H_
#define ASSIGNMENT2_TRANSFEROBJECT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string.h>
//#include <fstream>
#include <iostream>
using namespace std;
class TransferObject{
	public:
	string name="Player2";
	int score=0;
	int hp=100;
	int maxhp=100;
	int money=100;
	int gameOver=0;
	bool onBike=false;
	int connectionStrength=0;
	SDL_Rect dst={100,200,32,32};
	SDL_Rect src{32+118*3,502+350,58,105};
	TransferObject();
	~TransferObject();
};


#endif /* ASSIGNMENT2_TRANSFEROBJECT_H_ */
