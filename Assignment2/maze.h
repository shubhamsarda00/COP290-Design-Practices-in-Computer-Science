/*
 * maze.h
 *
 *  Created on: 02-Apr-2022
 *      Author: shubham
 */

#ifndef ASSIGNMENT2_MAZE_H_
#define ASSIGNMENT2_MAZE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string.h>
//#include <fstream>
#include <iostream>
#include <map>
#include "tile.h"
using namespace std;

class Maze {
	public:
	string mapfile="support/map_final.txt";
	int background[210][400];
	map<int,Tile> tiles;
//	map<string,SDL_Point> hotSpots;
	map<string,int> tidMap;
//	map<string,int> terrainLandmarks;
//	map<string,int> roadLandmarks;
//	map<string,int> buildingLandmarks;
//	map<string,int> waterLandmarks;
//	map<string,int> grassLandmarks;
	map<string, SDL_Rect> landmarks;
	map<string, SDL_Rect> landmarkBoxes;
	Maze();
	Maze(string mapfile);
	~Maze();
	void checkLandmark(int r, int c);
	void readMaze();
	void addTile(Tile tile);
//	int** getMaze();
	void render(SDL_Renderer* sdlr);
	void scroll(int vx,int vy);
	SDL_Rect getLandmarkDest(string name);
	private:

};



#endif /* ASSIGNMENT2_MAZE_H_ */
