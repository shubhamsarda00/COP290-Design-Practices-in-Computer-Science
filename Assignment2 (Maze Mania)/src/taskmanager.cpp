/*
 * taskmanager.cpp
 *
 *  Created on: 15-Apr-2022
 *      Author: shubham
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "taskmanager.h"

using namespace std;

TaskManager::TaskManager(){
	this->taskTimes.insert({1,10*60*1000});
	this->taskTimes.insert({2,10*60*1000});
	this->taskTimes.insert({3,10*60*1000});
	this->taskTimes.insert({4,10*60*1000});
	this->taskTimes.insert({5,10*60*1000});
	this->taskTimes.insert({6,10*60*1000});
	this->taskTimes.insert({7,10*60*1000});
	this->taskTimes.insert({8,10*60*1000});
	this->taskTimes.insert({9,10*60*1000});
	this->taskTimes.insert({10,10*60*1000});
}
TaskManager::~TaskManager(){

}
void TaskManager::loadTasks(SDL_Renderer* sdlr){
	SDL_Surface *temp;
	for(int i=0;i<12;i++){

		string path="support/taskmanager/Slide"+to_string(i+1)+".PNG";
		temp=IMG_Load(path.c_str());
		if(!temp) {
			cout<<"Error while loading task manager surface!:"<<IMG_GetError()<<endl;
		}

		this->tasks.insert({i,SDL_CreateTextureFromSurface(sdlr,temp)});



	}
	string path="support/football_goal.jpg";
	temp=IMG_Load(path.c_str());
	if(!temp) {
		cout<<"Error while loading football surface!:"<<IMG_GetError()<<endl;
	}

	this->footballgoal=SDL_CreateTextureFromSurface(sdlr,temp);
	path="support/footy.jpg";
	temp=IMG_Load(path.c_str());
	SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0xFF, 0xFF, 0xFF));
	if(!temp) {
		cout<<"Error while loading football surface!:"<<IMG_GetError()<<endl;
	}

	this->football=SDL_CreateTextureFromSurface(sdlr,temp);
	SDL_FreeSurface(temp);

	this->currentTexture=this->tasks.at(0);
}
//void TaskManager::checkTasks(SDL_Renderer* sdlr,SDL_Event event){
//
//}
int TaskManager::getTask(){
	if(this->tasksCompleted.size()==this->totalTasks){
		return -1;
	}
	int k=0;
	while(true){
		k=rand()%this->totalTasks+1;
		if(count(this->tasksCompleted.begin(), this->tasksCompleted.end(),k)){
			continue;
		}
		else{
			break;
		}
	}
	return k;
}

