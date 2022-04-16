/*
 * menu.h
 *
 *  Created on: 02-Apr-2022
 *      Author: shubham
 */

#ifndef ASSIGNMENT2_MENU_H_
#define ASSIGNMENT2_MENU_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
//#include <math.h>
#include <vector>
#include <string.h>
//#include <fstream>
#include <iostream>
#include "music.h"
using namespace std;

#define MENU_WIDTH 800
#define MENU_HEIGHT 800

class Menu{

	public:
//	SDL_Window* window=NULL;
//	SDL_Renderer* sdlr=NULL;
//	SDL_Event event;
	SDL_Texture* currentTexture;
	int mousex,mousey,highscore;
	vector<SDL_Rect> buttons;
	SDL_Texture* texture;
	SDL_Texture* texture1;
	SDL_Texture* texture2;
	SDL_Texture* texture3;
	SDL_Texture* texture4;
	SDL_Texture* texture5;

	TTF_Font* font;
	Music music;
	string p1Name="";
	string p1Hostel="ARAVALI";
	bool isOpen,fullscreen,playMusic,isPlaying;
//	vector<string> options;
	Menu();
	~Menu();
	void initialize();
	void loadMenu(SDL_Renderer* sdlr);
	void toggleMusic();
	bool render(SDL_Event event,SDL_Window* window,SDL_Renderer* sdlr);
	void write(SDL_Renderer*sdlr,string text,SDL_Color colour,int x, int y);
	void playSoundEffect(string name,bool delay);
	void updateFont(string path,int fontSize);
	void reloadHighScore();
	void updateHighScore(int score);
	int getHighScore(){return this->highscore;};
	private:
};




#endif /* ASSIGNMENT2_MENU_H_ */
