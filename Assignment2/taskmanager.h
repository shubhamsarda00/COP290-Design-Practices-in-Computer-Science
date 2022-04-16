/*
 * taskmanager.h
 *
 *  Created on: 15-Apr-2022
 *      Author: shubham
 */

#ifndef ASSIGNMENT2_TASKMANAGER_H_
#define ASSIGNMENT2_TASKMANAGER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string.h>
//#include <fstream>
#include <iostream>
#include <map>
using namespace std;
class TaskManager {
	public:
	int taskProgress=0;
	string hostel;
	int totalTasks=1;
	SDL_Texture* football=NULL;
	SDL_Texture* footballgoal=NULL;
	vector<int> tasksCompleted;
	map<int,SDL_Texture*> tasks;
	SDL_Texture* currentTexture;
	bool taskOngoing=false;
	long long unsigned int taskTimer=0;
	map<int,int> taskTimes;
	int currentTask;
	TaskManager();
	~TaskManager();
	void loadTasks(SDL_Renderer* sdlr);
	//void checkTasks(SDL_Renderer* sdlr,SDL_Event event);
	int getTask();
};


#endif /* ASSIGNMENT2_TASKMANAGER_H_ */
