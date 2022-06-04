/*
 * music.h
 *
 *  Created on: 03-Apr-2022
 *      Author: shubham
 */

#ifndef ASSIGNMENT2_MUSIC_H_
#define ASSIGNMENT2_MUSIC_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
//#include <math.h>
#include <vector>
#include <string.h>
#include <map>
//#include <fstream>
#include <iostream>
#include "music.h"
using namespace std;

class Music{
	public:
//	Mix_Chunk* chime=NULL;
//	Mix_Chunk* prof=NULL;
//	Mix_Chunk* dog=NULL;
//	Mix_Chunk* game_start=NULL;
	map<string,Mix_Chunk*> audio_sounds;
//	Mix_Chunk* eventCompletion=NULL;
	Mix_Music* menuAudio=NULL;
	Mix_Music* gameAudio=NULL;
	bool isPlaying=true;
	void toggle(){this->isPlaying=!this->isPlaying;};
	Music();
	~Music();
	void loadMusic();
	void resumeMusic();
	void startMenuMusic();
	void pauseMusic();
	void menuToGame();
//	void playSoundEffect(string name);
	private:

};




#endif /* ASSIGNMENT2_MUSIC_H_ */
