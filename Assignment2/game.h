/*
 * game.h
 *
 *  Created on: 29-Mar-2022
 *      Author: shubham
 */

#ifndef ASSIGNMENT2_GAME_H_
#define ASSIGNMENT2_GAME_H_

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string.h>
//#include <fstream>
#include <iostream>
#include "player.h"
#include "maze.h"
#include "menu.h"
#include "gameobject.h"
#include "taskmanager.h"
//#include "transferobject.h"
class Game{
	public:
		TTF_Font* font;
		Player player1;
		int moneyInBank=0;
		//TransferObject TransferObject;
		bool playAgain=true;
		long long unsigned int bankClock;
		SDL_Texture* bank;
		TaskManager taskManager;
		long long unsigned int gameClock;
		map<string,Gameobject> gameObjects;
		bool lunchTime=false;
		bool lunchTaken=false;
		map<string,SDL_Texture*> landmarkNameTexture;
		map<string,SDL_Texture*> restaurantMenus;
		SDL_Texture* inspectorGadget;
		int gameObjectMotionTimer;
		int gameObjectMotionDirection;
		int mousex,mousey;
		SDL_Window* window=NULL;
		SDL_Renderer* sdlr=NULL;
		SDL_Event event;
		SDL_Point currentTarget;
		bool playing,fullscreen,playMusic;
		Maze maze;
		Menu menu;
		bool scrollMaze=false;
		SDL_TimerID tid;
		int highscore=0;
		//map<string,SDL_Rect> landmarkBoxes;
		map<string,long long unsigned int> timerFuncs;
		map<string,int> timerFuncsInterval;
		long long unsigned int startTime;
		Game();
		~Game();
		bool render();
		void startGame();
		void initialize();
		void updateFont(string path,int fontSize,TTF_Font* f);
		void write1(SDL_Renderer*sdlr,string text,SDL_Color colour,int x, int y);
		void reloadHighScore();
		void updateHighScore(int score);
		int getHighScore(){return this->highscore;};
		int getDistance(SDL_Point p1,SDL_Point p2);
		void loadGameObjects(SDL_Renderer* sdlr);
		void showGameObjects();
		void loadLandmarkNames(SDL_Renderer* sdlr);
		void showLandmarkName(string name);
		void showLandmarkNames();
		void loadLandmarkName(SDL_Renderer* sdlr,string name);
//		void loadCompletionBox(SDL_Renderer* sdlr);
		void showCompletionBox(string name);
		void temp();
		bool checkLandmarkIntersection(string landMark, SDL_Rect y);
		void updateGameObjects(SDL_Renderer* sdlr);
		void checkGameObjectIntersection(Player* p);
		void scrollGameObjects();
		void showTime();
		bool checkCollision(Player* player,int vx, int vy);
		bool checkIntersection(SDL_Rect* r1,SDL_Rect* r2);
		void startLunch();
		void stopLunch();
		void checkLunch();
		void checkYulu();
		void payYuluFee();
		void loadRestaurantMenus();
		void checkRestaurants();
		void checkInspectorGadget();
		void loadInspectorGadget();
		void checkTaskHelper();
		void showTaskTimer();
		void checkTaskProgress();
		void loadBank();
		void checkBank();
		void endGame();
		SDL_Rect absoluteToRelative(SDL_Rect r);
//		static Uint32 temp( Uint32 timeInterval, void* param );
	private:

};



#endif /* ASSIGNMENT2_GAME_H_ */
