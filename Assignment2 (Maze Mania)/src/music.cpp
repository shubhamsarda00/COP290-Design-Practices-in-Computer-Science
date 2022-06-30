/*
 * music.cpp
 *
 *  Created on: 03-Apr-2022
 *      Author: shubham
 */

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

Music::Music(){

	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
		{
			printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		}
}
Music::~Music(){
	for (auto i=this->audio_sounds.begin();i!=this->audio_sounds.end();i++){
			 Mix_FreeChunk(i->second);
		 }

//    Mix_FreeChunk(this->chime);
//    Mix_FreeChunk(this->eventCompletion);
//    this->chime = NULL;
//    this->eventCompletion= NULL;
    Mix_FreeMusic(gameAudio);
    Mix_FreeMusic(menuAudio);
    this->gameAudio= NULL;
    this->menuAudio=NULL;
	Mix_Quit();
}
void Music::loadMusic(){
	this->audio_sounds.insert({"chime",Mix_LoadWAV( "support/music/chime.wav")});
	this->audio_sounds.insert({"buzzer",Mix_LoadWAV( "support/music/buzzer.wav")});
	this->audio_sounds.insert({"eventCompletion",Mix_LoadWAV( "support/music/eventcomplete.wav")});
	this->audio_sounds.insert({"dog",Mix_LoadWAV( "support/music/dog_barking.wav" )});
	this->audio_sounds.insert({"prof",Mix_LoadWAV( "support/music/angry_prof.wav" )});
	this->audio_sounds.insert({"game_over",Mix_LoadWAV( "support/music/game_over.wav" )});
	this->audio_sounds.insert({"game_start",Mix_LoadWAV( "support/music/game_start.wav" )});
	//this->audio_sounds.insert({"whistle",Mix_LoadWAV( "support/music/whistle.wav" )});

	this->gameAudio=Mix_LoadMUS("support/music/Linkin_Park_-_Papercut_(Instrumental).mp3");
	if(this->gameAudio==NULL){
		cout<<"Music not loaded: "<<Mix_GetError()<<endl;	}
	this->menuAudio=Mix_LoadMUS("support/music/Green_Day_-_Boulevard_Of_Broken_Dreams.mp3");
	if(this->menuAudio==NULL){
		cout<<"Music not loaded: "<<Mix_GetError()<<endl;
	}
//	cout<<"LOADED"<<endl;
}
void Music::startMenuMusic(){
	Mix_PlayMusic(menuAudio,-1);
}
void Music::resumeMusic(){
	Mix_ResumeMusic();
}
void Music::pauseMusic(){
	Mix_PauseMusic();
}
void Music::menuToGame(){
	Mix_HaltMusic();
	Mix_PlayMusic(gameAudio, -1);
}



