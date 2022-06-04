/*
 * tile.cpp
 *
 *  Created on: 02-Apr-2022
 *      Author: shubham
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string.h>
//#include <fstream>
#include <iostream>
//#include <map>
#include "tile.h"
using namespace std;

Tile::Tile(){
	this->id=0;
}
Tile::~Tile(){
//	if(this->texture!=NULL){
//			SDL_DestroyTexture(this->texture);
//			this->texture= NULL;
//		}
}
Tile::Tile(int id){
	this->id=id;
}
Tile::Tile(int id, int x, int y, int w, int h, bool isSolid,string file){
	this->id=id;
	this->isSolid=isSolid;
	this->src.x=x;
	this->src.w=w;
	this->src.y=y;
	this->src.h=h;
	this->file=file;
}
void Tile::setSolid(bool isSolid){
	this->isSolid=isSolid;
}
void Tile::setFile(string file){
	this->file=file;
}
void Tile::loadTile(SDL_Renderer* sdlr){
	SDL_Surface *temp;
	temp=IMG_Load(this->file.c_str());
	if(!temp) {
		cout<<"Error while loading Tile surface!:"<<IMG_GetError()<<endl;
	}
	this->texture=SDL_CreateTextureFromSurface(sdlr,temp);
	if(this->texture == NULL ){
		cout<<"Error while loading Tile texture!:"<<IMG_GetError()<<endl;
	}
	SDL_FreeSurface(temp);
}
SDL_Texture* Tile::getTexture(){
	return this->texture;
}
void Tile::setSrc(int x, int y, int w, int h){
	this->src.x=x;
	this->src.w=w;
	this->src.y=y;
	this->src.h=h;
}
int Tile::getId(){
	return this->id;
}
int Tile::addDst(int x, int y,int w, int h){
	SDL_Rect dst;
	dst.x=x;
	dst.y=y;
	dst.w=w;
	dst.h=h;
	this->dsts.push_back(dst);
	return this->dsts.size()-1;
}
void Tile::drawTile(SDL_Renderer* sdlr, SDL_Rect* dst){
	SDL_RenderCopy(sdlr,this->texture,&this->src,dst);
}


