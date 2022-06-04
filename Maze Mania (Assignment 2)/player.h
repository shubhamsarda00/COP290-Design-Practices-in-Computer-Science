/*
 * player.h
 *
 *  Created on: 29-Mar-2022
 *      Author: shubham
 */

#ifndef ASSIGNMENT2_PLAYER_H_
#define ASSIGNMENT2_PLAYER_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string.h>
//#include <fstream>
#include <iostream>
#include <map>
using namespace std;
class Player {
	public:
	string name;
	int speed=20;
	int hp=100;
	int money=100;
	int score=0;
	bool atStart=true;
	bool isMoving=false;
	int moveCounter=0;
	bool outOfBounds=false;
	string hostel;
	bool onBike=false;
	bool shield=false;
	bool runningShoes=false;
	SDL_Texture* playerPointer=NULL;
	int scoreMultiplier=1;
	long long unsigned int shieldTimer=0;
	struct animation{
			int x,y,r,step,w,h,length,speed_reduction_factor;
		};
	animation presentAnimation;
	map<string,animation> animations;
	int maxhp=100;
	SDL_Rect absoluteDst;
	//SDL_Rect prevAbsoluteDst;
	SDL_Rect dst;
	SDL_Rect src;
	SDL_Texture* avatar=NULL;
	SDL_Texture* bikeTexture=NULL;
	SDL_Texture* currentTexture=NULL;
		Player();
		Player(string name);
		~Player();
		void setName(string name);
		void addAnimation(string animationName,int x,int y,int r,int step,int w,int h,int length,int speed_reduction_factor);
		void setAnimation(string name);
//		void endAnimation();
		void bufferAnimation();
//		void idleLeft();
//		void idleRight();
//		void idleUp();
//		void idleDown();
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void stopLeft();
		void stopRight();
		void stopUp();
		void stopDown();
		void render(SDL_Renderer* sdlr);
		void showPlayer(SDL_Renderer* sdlr);
		void setSrcRect(int x, int y, int w, int h);
		void setDstRect(int x, int y, int w, int h);
		void loadAvatar(SDL_Renderer* sdlr, string img_path);
		SDL_Point getCoordinates();
		SDL_Texture* getAvatar();
		void toggleTexture();
	private:




};





#endif /* ASSIGNMENT2_PLAYER_H_ */
