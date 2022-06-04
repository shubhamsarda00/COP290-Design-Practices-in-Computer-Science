/*
 * gameobject.h
 *
 *  Created on: 08-Apr-2022
 *      Author: shubham
 */


#ifndef ASSIGNMENT2_GAMEOBJECT_H_
#define ASSIGNMENT2_GAMEOBJECT_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
//#include <math.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>

using namespace std;

class Gameobject{
	public:
		SDL_Texture* icon=NULL;
		SDL_Rect src;
		vector<SDL_Rect> dsts;
		vector<int> indexDsts;
		string name;
		int count=1;
		string path;
		int vx=50;
		int vy=50;
		int position=0;
		bool green=true;
		long long unsigned int timer;
		int interval=1*1000;
		Gameobject();
		Gameobject(string name, string path,bool green);
		~Gameobject();
		void showBoundaryBox(SDL_Renderer* sdlr);
		void move();
		void loadIcon(SDL_Renderer* sdlr);
		void showIcon(SDL_Renderer* sdlr);
		void render(SDL_Renderer* sdlr);
	    void addDstRect(int x, int y, int w, int h);
	    void setSrcRect(int x, int y, int w, int h);
	private:


};



#endif /* ASSIGNMENT2_GAMEOBJECT_H_ */
