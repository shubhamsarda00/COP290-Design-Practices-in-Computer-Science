/*
 * player.cpp
 *
 *  Created on: 29-Mar-2022
 *      Author: shubham
 */

#include "player.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>
//#include <math.h>
//#include <vector>
#include <string.h>
//#include <fstream>
#include <iostream>

using namespace std;


Player::Player(){
	this->hp=maxhp;
	animation left;
	animation right;
	animation up;
	animation down;
	animations.insert({"left",left});
	animations.insert({"right",right});
	animations.insert({"up",up});
	animations.insert({"down",down});
}
Player::Player(string name){
	this->hp=maxhp;
	this->name=name;
	animation left;
	animation right;
	animation up;
	animation down;
	animations.insert({"left",left});
	animations.insert({"right",right});
	animations.insert({"up",up});
	animations.insert({"down",down});
}
Player::~Player(){
	if(this->avatar!=NULL){
		SDL_DestroyTexture(this->avatar);
		SDL_DestroyTexture(this->bikeTexture);
		SDL_DestroyTexture(this->currentTexture);
		this->avatar= NULL;
		this->bikeTexture=NULL;
		this->currentTexture=NULL;

	}
}
void Player::setName(string name){
	this->name=name;
}
void Player::setSrcRect(int x, int y, int w, int h){
	src.x=x;
	src.y=y;
	src.w=w;
	src.h=h;
}
void Player::setDstRect(int x, int y, int w, int h){
	dst.x=x;
	dst.y=y;
	dst.w=w;
	dst.h=h;
}
void Player::render(SDL_Renderer* sdlr){
	if(this->isMoving){
	}
	this->bufferAnimation();

	this->showPlayer(sdlr);
}
void Player::moveLeft(){
	if(!onBike){
		if(this->atStart){
			this->setAnimation("left");
			this->isMoving=true;
			this->atStart=false;
		}
	}
	this->isMoving=true;
	int x_hat=this->dst.x;
//	if(this->dst.x>this->speed){
		x_hat=this->dst.x-this->speed;
//	}
	this->absoluteDst.x-=this->speed;
	this->setDstRect(x_hat, this->dst.y,this->dst.w,this->dst.h);

}
void Player::moveRight(){
	if(!onBike){
	if(this->atStart){
		this->setAnimation("right");
		this->isMoving=true;
		this->atStart=false;
	}
	}
	this->isMoving=true;
	int x_hat=this->dst.x;
//	if(1280>this->dst.x+this->speed){
		x_hat=this->dst.x+this->speed;
//	}
		this->absoluteDst.x+=this->speed;
	this->setDstRect(x_hat, this->dst.y,this->dst.w,this->dst.h);

}
void Player::moveUp(){
	if(!onBike){
	if(this->atStart){
		this->setAnimation("up");
		this->isMoving=true;
		this->atStart=false;
	}
	}
	this->isMoving=true;
	int y_hat=this->dst.y;
//	if(this->dst.y>this->speed){
	y_hat=this->dst.y-this->speed;
//	}
	this->absoluteDst.y-=this->speed;
	this->setDstRect(this->dst.x,y_hat,this->dst.w,this->dst.h);

}
void Player::moveDown(){
	if(!onBike){
	if(this->atStart){
		this->setAnimation("down");
		this->isMoving=true;
		this->atStart=false;
	}
	}
	this->isMoving=true;
	int y_hat=this->dst.y;
//	if(1280>this->dst.y+this->speed){
		y_hat=this->dst.y+this->speed;
//	}
	this->absoluteDst.y+=this->speed;
	this->setDstRect(this->dst.x, y_hat,this->dst.w,this->dst.h);


}
//void Player::idleLeft(){
//
//}
//void Player::idleRight(){
//
//}
//void Player::idleUp(){
//
//}
//void Player::idleDown(){
//
//}
void Player::addAnimation(string animationName,int x,int y,int r,int step,int w,int h,int length,int speed_reduction_factor){

	animation a;
	a.x=x;
	a.y=y;
	a.r=r;
	a.w=w;
	a.h=h;
	a.step=step;
	a.length=length;
	a.speed_reduction_factor=speed_reduction_factor;
	map<string,animation>::iterator i=this->animations.find(animationName);
	if(i!=this->animations.end()){
		i->second=a;
	}
	else{
		this->animations.insert({animationName,a});
	}

}
void Player::setAnimation(string name){
	this->presentAnimation=animations.at(name);
}
void Player::bufferAnimation(){
	if(this->isMoving){
		this->moveCounter++;

		if(this->moveCounter==presentAnimation.speed_reduction_factor){
			this->moveCounter=0;
			presentAnimation.r++;
		}

		if(presentAnimation.r==presentAnimation.length){
			presentAnimation.r=0;
		}

		this->setSrcRect(presentAnimation.x+presentAnimation.step*presentAnimation.r
				, presentAnimation.y
				, presentAnimation.w
				, presentAnimation.h);
		//cout<<"buffer"<<presentAnimation.r<<endl;
		}
		//cout<<"buffer_out"<<this->moveCounter<<endl;

	else{

	}
}
//void Player::endAnimation(){
//	presentAnimation.r=0;
//	this->setSrcRect(presentAnimation.x+presentAnimation.step*presentAnimation.r
//				, presentAnimation.y
//				, presentAnimation.w
//				, presentAnimation.h);
//	this->isMoving=false;
//	this->moveCounter=0;
//	this->atStart=true;
//}
void Player::stopLeft(){
	if(!onBike){
	presentAnimation.r=10;
	this->setSrcRect(presentAnimation.x+presentAnimation.step*presentAnimation.r
				, presentAnimation.y
				, presentAnimation.w
				, presentAnimation.h);
	this->isMoving=false;
	presentAnimation.r=0;
	this->moveCounter=0;
	this->atStart=true;
	}
	this->isMoving=false;
}
void Player::stopRight(){
	if(!onBike){
	presentAnimation.r=0;
	this->setSrcRect(presentAnimation.x+presentAnimation.step*presentAnimation.r
				, presentAnimation.y
				, presentAnimation.w
				, presentAnimation.h);
	this->isMoving=false;
	this->moveCounter=0;
	this->atStart=true;
	}
	this->isMoving=false;
}
void Player::stopUp(){
	if(!onBike){
	presentAnimation.r=0;
	this->setSrcRect(presentAnimation.x+presentAnimation.step*presentAnimation.r
				, presentAnimation.y
				, presentAnimation.w
				, presentAnimation.h);
	this->isMoving=false;
	this->moveCounter=0;
	this->atStart=true;
	}
	this->isMoving=false;
}
void Player::stopDown(){
	if(!onBike){
	presentAnimation.r=10;
	this->setSrcRect(presentAnimation.x+presentAnimation.step*presentAnimation.r
				, presentAnimation.y
				, presentAnimation.w
				, presentAnimation.h);
	this->isMoving=false;
	presentAnimation.r=0;
	this->moveCounter=0;
	this->atStart=true;
	}
	this->isMoving=false;
}


void Player::loadAvatar(SDL_Renderer* sdlr, string img_path){
	SDL_Surface *temp;
	SDL_Surface *temp1;
	SDL_Surface *temp2;
	temp=IMG_Load(img_path.c_str());
	if(!temp) {
		cout<<"Error while loading player avatar surface!:"<<IMG_GetError()<<endl;
	}
	temp1=IMG_Load("support/bike.jpeg");

	if(!temp1) {
		cout<<"Error while loading player Bike surface!:"<<IMG_GetError()<<endl;
	}
	temp2=IMG_Load("support/playerpointer.jpeg");

	if(!temp2) {
		cout<<"Error while loading player Pointer surface!:"<<IMG_GetError()<<endl;
	}
	SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0xFF, 0xFF, 0xFF));
	SDL_SetColorKey( temp1, SDL_TRUE, SDL_MapRGB( temp1->format, 0xFF, 0xFF, 0xFF));
	SDL_SetColorKey( temp2, SDL_TRUE, SDL_MapRGB( temp2->format, 0xFF, 0xFF, 0xFF));
	//SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0, 0, 0));
	this->avatar=SDL_CreateTextureFromSurface(sdlr,temp);
	if(this->avatar == NULL ){
		cout<<"Error while loading player avatar texture!:"<<SDL_GetError()<<endl;
	}
	this->bikeTexture=SDL_CreateTextureFromSurface(sdlr,temp1);;
	if(this->bikeTexture == NULL ){
		cout<<"Error while loading player bike avatar texture!:"<<SDL_GetError()<<endl;
	}
	this->playerPointer=SDL_CreateTextureFromSurface(sdlr,temp2);;
	if(this->playerPointer == NULL ){
		cout<<"Error while loading player pointer texture!:"<<SDL_GetError()<<endl;
	}
	SDL_FreeSurface(temp);
	SDL_FreeSurface(temp1);
	SDL_FreeSurface(temp2);
	this->currentTexture=this->avatar;
}
void Player::showPlayer(SDL_Renderer* sdlr){
	SDL_Rect source=this->src;
	SDL_Rect dest=this->dst;
	if(!onBike){
		SDL_RenderCopy(sdlr,this->getAvatar(),&source,&dest);
	}
	else{
		SDL_RenderCopy(sdlr,this->currentTexture,NULL,&dest);
	}
	dest.y-=32;dest.x+=2;
	dest.w=dest.h=32;

	SDL_RenderCopy(sdlr, this->playerPointer,NULL , &dest);
}
SDL_Texture* Player::getAvatar(){
	return this->currentTexture;
}
SDL_Point Player::getCoordinates(){
	SDL_Point p;
	p.x=this->dst.x+16;
	p.y=this->dst.y+16;
	return p;
}
void Player::toggleTexture(){
	if(onBike){
		this->currentTexture=this->bikeTexture;
	}
	else{
		this->currentTexture=this->avatar;
	}
}



