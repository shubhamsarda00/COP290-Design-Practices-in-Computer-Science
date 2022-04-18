/*
 * main.cpp
 *
 *  Created on: 19-Mar-2022
 *      Author: shubham
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>
//#include <math.h>
//#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "game.h"

using namespace std;

int main(int argc, char **argv) {


	unsigned long long int startTime;
	unsigned int elapsedTime;
	const int loopTime=60/60;



	Game game;
//	string c=argv[1];
//
//	if(c.compare("c")==0){
//		game.isServer=false;
//		game.ip=argv[2];
//		cout<<"Client"<<endl;
//	}

	game.initialize();
//	if(argc>1){
//		game.player1.setName(argv[1]);
//	}
//	else{
//		game.player1.setName("Player 1");
//	}

	game.menu.loadMenu(game.sdlr);
	while(game.menu.isOpen){
		game.menu.render(game.event,game.window,game.sdlr);
	}
	if(game.playing && game.menu.isPlaying){
		game.startGame();
	}
	while(game.playing && game.menu.isPlaying){
		startTime=SDL_GetTicks();
		game.render();
		elapsedTime=SDL_GetTicks()-startTime;
		if(elapsedTime<loopTime){
			SDL_Delay(loopTime-elapsedTime);
		}
	}

	game.reloadHighScore();
	game.updateHighScore(0);
//	game.~Game();



	return 0;

}
