/*
 * tile.h
 *
 *  Created on: 02-Apr-2022
 *      Author: shubham
 */

#ifndef ASSIGNMENT2_TILE_H_
#define ASSIGNMENT2_TILE_H_


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <vector>
#include <string.h>
//#include <fstream>
#include <iostream>
//#include <map>
//#include "tile.h"
using namespace std;

class Tile {
	public:
	bool isSolid=true;
	string file;
	int id;
	SDL_Rect src;
	vector<SDL_Rect> dsts;
	Tile();
	Tile(int id);
	Tile(int id, int x, int y, int w, int h, bool isSolid,string file);
	void setSolid(bool isSolid);
	void setFile(string file);
	void loadTile(SDL_Renderer* sdlr);
	void setSrc(int x, int y, int w, int h);
	int addDst(int x, int y,int w, int h);
	vector<SDL_Rect> getDsts(){return this->dsts;};
	void drawTile(SDL_Renderer* sdlr,SDL_Rect* dst);
	int getId();
	SDL_Texture* getTexture();
	~Tile();
	private:
	SDL_Texture* texture=NULL;
};

#endif /* ASSIGNMENT2_TILE_H_ */
