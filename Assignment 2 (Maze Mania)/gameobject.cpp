#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
//#include <math.h>
//#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
#include "gameobject.h"

using namespace std;

Gameobject::Gameobject(){

}
Gameobject::Gameobject(string name, string path,bool green){
	this->name=name;
	this->path=path;
	this->green=green;
	this->timer=SDL_GetTicks();
}
Gameobject::~Gameobject(){
//	if(this->icon!=NULL){
//		SDL_DestroyTexture(this->icon);
//		this->icon= NULL;
//	}
}
void Gameobject::loadIcon(SDL_Renderer* sdlr){
	SDL_Surface* s1;
	s1=IMG_Load(this->path.c_str());
//	if(!temp) {
//		cout<<"Error while loading player avatar surface!:"<<IMG_GetError()<<endl;
//	}
	SDL_SetColorKey( s1, SDL_TRUE, SDL_MapRGB( s1->format, 0xFF, 0xFF, 0xFF));
	//SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0, 0, 0));
	this->icon=SDL_CreateTextureFromSurface(sdlr,s1);
//	this->gameObjects.insert({"prof_f",prof_f});
//	this->gameObjects.insert({"prof_m",prof_m});
//	this->gameObjects.insert({"dog",dog});

//	if(this->p == NULL ){
//		cout<<"Error while loading player avatar texture!:"<<SDL_GetError()<<endl;
//	}
	SDL_FreeSurface(s1);

}
void Gameobject::move(){
	for(int i=0;i<this->dsts.size();i++){
		if(this->position==0){
			int x=rand()/(RAND_MAX/2);
			if(x==0){
				this->position=1;
				this->dsts[i].x+=vx;
			}
			else{
				this->position=2;
				this->dsts[i].y+=vy;
			}
		}
		else if(this->position==1){
			this->position=0;
			this->dsts[i].x-=this->vx;
		}
		else{
			this->position=0;
			this->dsts[i].y-=this->vy;
		}
	}
}
void Gameobject::render(SDL_Renderer* sdlr){
//	if(SDL_GetTicks()-this->timer>this->interval){
//		this->timer=SDL_GetTicks();
//		this->move();
//	}
	this->showIcon(sdlr);
	this->showBoundaryBox(sdlr);
}
void Gameobject::showBoundaryBox(SDL_Renderer* sdlr){
	for(int i=0;i<this->dsts.size();i++){
		SDL_Rect r=this->dsts[i];
		r.x-=50;
		r.y-=50;
		r.w=150;
		r.h=150;
		SDL_SetRenderDrawBlendMode(sdlr, SDL_BLENDMODE_BLEND);
		if(this->green){
			SDL_SetRenderDrawColor(sdlr, 0x00, 0xFF, 0x00, 100 );
		}
		else{
			SDL_SetRenderDrawColor(sdlr, 0xFF, 0x00, 0x00, 100 );
		}
		//SDL_RenderDrawRect(this->sdlr,&r );
		SDL_RenderFillRect(sdlr, &r );
		SDL_SetRenderDrawBlendMode(sdlr, SDL_BLENDMODE_NONE);
	}

}
void Gameobject::showIcon(SDL_Renderer* sdlr){
	for(int i=0;i<this->dsts.size();i++){
		SDL_RenderCopy(sdlr,this->icon,NULL,&this->dsts[i]);
//		cout<<i<<endl;
	}
}
void Gameobject::addDstRect(int x, int y, int w, int h){
	SDL_Rect dst;
	dst.x=x;
	dst.y=y;
	dst.w=w;
	dst.h=h;
	this->dsts.push_back(dst);
}
void Gameobject::setSrcRect(int x, int y, int w, int h){
	src.x=x;
	src.y=y;
	src.w=w;
	src.h=h;
}

