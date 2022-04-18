/*
 * menu.cpp
 *
 *  Created on: 02-Apr-2022
 *      Author: shubham
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
//#include <math.h>
//#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
#include "menu.h"

using namespace std;

Menu::Menu(){
	this->fullscreen=false;
	this->playMusic=true;
	this->isOpen=true;
	this->isPlaying=true;
}
Menu::~Menu(){
//	SDL_DestroyWindow(window);
//	SDL_DestroyRenderer(sdlr);
//	IMG_Quit();
//	SDL_Quit();
//	window=NULL;
//	sdlr=NULL;
}
void Menu::initialize(){
//	if(SDL_Init(SDL_INIT_EVERYTHING)<0){
//		cout<<"Error while initializing SDL:"<<SDL_GetError()<<endl;
//	}
//	this->window=SDL_CreateWindow( "Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MENU_WIDTH, MENU_HEIGHT, SDL_WINDOW_SHOWN );
//	if(this->window==NULL ){
//		cout<<"Error in creating Window:"<<SDL_GetError()<<endl;
//		this->isOpen=false;
//	}
//	this->sdlr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
//	if(this->sdlr== NULL ){
//		cout<<"Error in creating Renderer:"<<SDL_GetError()<<endl;
//		this->isOpen=false;
//	}
//	cout<<this->isOpen;
}
void Menu::loadMenu(SDL_Renderer* sdlr){
	//Music Handling
	this->music.loadMusic();
	this->music.startMenuMusic();
	//
	//
	this->updateFont("support/fonts/OpenSans-Semibold.ttf",32);
	for(int i=0;i<4;i++){
		SDL_Rect r;
		r.x=520;
		r.y=28+190*i;
		r.w=275;
		r.h=160;
		this->buttons.push_back(r);
	}

	string s;
        //Texture
		SDL_Surface *temp;
		s="support/menu/Slide1.PNG";
		//cout<<s<<endl;
		temp=IMG_Load(s.c_str());
		if(!temp) {
			cout<<"Error while loading Menu surface!:"<<IMG_GetError()<<endl;
		}
		//SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0xFF, 0xFF, 0xFF));
		//SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0, 0, 0));
		this->texture=SDL_CreateTextureFromSurface(sdlr,temp);
		if(this->texture == NULL ){
			cout<<"Error while loading Menu texture!:"<<SDL_GetError()<<endl;
		}
		//SDL_FreeSurface(temp);

		//Texture1
		//SDL_Surface *temp;
		 s="support/menu/Slide2.PNG";
		//cout<<s<<endl;
		temp=IMG_Load(s.c_str());
		if(!temp) {
			cout<<"Error while loading Menu surface!:"<<IMG_GetError()<<endl;
		}
		//SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0xFF, 0xFF, 0xFF));
		//SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0, 0, 0));
		this->texture1=SDL_CreateTextureFromSurface(sdlr,temp);
		if(this->texture1 == NULL ){
			cout<<"Error while loading Menu texture!:"<<SDL_GetError()<<endl;
		}
		//SDL_FreeSurface(temp);

		//Texture2
		//SDL_Surface *temp;
		s="support/menu/Slide3.PNG";
		//cout<<s<<endl;
		temp=IMG_Load(s.c_str());
		if(!temp) {
			cout<<"Error while loading Menu surface!:"<<IMG_GetError()<<endl;
		}
		//SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0xFF, 0xFF, 0xFF));
		//SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0, 0, 0));
		this->texture2=SDL_CreateTextureFromSurface(sdlr,temp);
		if(this->texture2 == NULL ){
			cout<<"Error while loading Menu texture!:"<<SDL_GetError()<<endl;
		}
		//SDL_FreeSurface(temp);
		//Texture3

		//SDL_Surface *temp;
		s="support/menu/Slide4.PNG";
		//cout<<s<<endl;
		temp=IMG_Load(s.c_str());
		if(!temp) {
			cout<<"Error while loading Menu surface!:"<<IMG_GetError()<<endl;
		}
		//SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0xFF, 0xFF, 0xFF));
		//SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0, 0, 0));
		this->texture3=SDL_CreateTextureFromSurface(sdlr,temp);
		if(this->texture3 == NULL ){
			cout<<"Error while loading Menu texture!:"<<SDL_GetError()<<endl;
		}
		//SDL_FreeSurface(temp);

		//Texture4
		//SDL_Surface *temp;
		s="support/menu/Slide5.PNG";
		//cout<<s<<endl;
		temp=IMG_Load(s.c_str());
		if(!temp) {
			cout<<"Error while loading Menu surface!:"<<IMG_GetError()<<endl;
		}
		//SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0xFF, 0xFF, 0xFF));
		//SDL_SetColorKey( temp, SDL_TRUE, SDL_MapRGB( temp->format, 0, 0, 0));
		this->texture4=SDL_CreateTextureFromSurface(sdlr,temp);
		if(this->texture4 == NULL ){
			cout<<"Error while loading Menu texture!:"<<SDL_GetError()<<endl;
		}
		s="support/menu/Slide6.PNG";
		//cout<<s<<endl;
		temp=IMG_Load(s.c_str());
		if(!temp) {
			cout<<"Error while loading Menu surface!:"<<IMG_GetError()<<endl;
		}
		this->texture5=SDL_CreateTextureFromSurface(sdlr,temp);
		if(this->texture5 == NULL ){
			cout<<"Error while loading Menu texture!:"<<SDL_GetError()<<endl;
		}
		s="support/menu/Slide7.PNG";
		//cout<<s<<endl;
		temp=IMG_Load(s.c_str());
		if(!temp) {
			cout<<"Error while loading Menu surface!:"<<IMG_GetError()<<endl;
		}
		this->instructions=SDL_CreateTextureFromSurface(sdlr,temp);
		if(this->instructions == NULL ){
			cout<<"Error while loading Menu texture!:"<<SDL_GetError()<<endl;
		}
		s="support/menu/Slide8.PNG";
		//cout<<s<<endl;
		temp=IMG_Load(s.c_str());
		if(!temp) {
			cout<<"Error while loading Menu surface!:"<<IMG_GetError()<<endl;
		}
		this->winscreen=SDL_CreateTextureFromSurface(sdlr,temp);
		if(this->winscreen == NULL ){
			cout<<"Error while loading Menu texture!:"<<SDL_GetError()<<endl;
		}
		s="support/menu/Slide9.PNG";
		//cout<<s<<endl;
		temp=IMG_Load(s.c_str());
		if(!temp) {
			cout<<"Error while loading Menu surface!:"<<IMG_GetError()<<endl;
		}
		this->nameScreen=SDL_CreateTextureFromSurface(sdlr,temp);
		if(this->nameScreen == NULL ){
			cout<<"Error while loading Menu texture!:"<<SDL_GetError()<<endl;
		}
		SDL_FreeSurface(temp);

}
bool Menu::render(SDL_Event event,SDL_Window* window,SDL_Renderer* sdlr){

	while(SDL_PollEvent(&event)){
		if(event.type==SDL_QUIT ||(event.type==SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)){
			this->isOpen=false;
			cout<<"Exiting The Game"<<endl;
			this->isPlaying=false;
			return false;
		}
		if(event.type==SDL_KEYDOWN){
			const Uint8* ks = SDL_GetKeyboardState( NULL );
			if(ks[SDL_SCANCODE_F]){
				this->fullscreen=!fullscreen;
				SDL_SetWindowFullscreen(window, fullscreen);
			}
			if(ks[SDL_SCANCODE_M]){
				this->toggleMusic();

			}
		}
		SDL_GetMouseState(&this->mousex, &this->mousey);
		//cout<<this->mousex<<" "<<this->mousey<<endl;
		SDL_Point p;
		p.x=this->mousex;
		p.y=this->mousey;
		if(SDL_PointInRect(&p, &buttons[0])==SDL_TRUE){
			this->currentTexture=texture1;
			if(event.type==SDL_MOUSEBUTTONDOWN){
				if(event.button.button!=SDL_BUTTON_RIGHT){
				this->isOpen=false;
				//Selecting Name and Hostel
				bool b=true;
				int n=0;
				string temp="";
				while(b){
					while(SDL_PollEvent(&event)){
						if(event.type==SDL_KEYDOWN){
							if(event.key.keysym.sym==SDLK_RETURN){
								if((isInteger(this->time))&&(p1Name.size()<=7) && (isClient.compare("YES")==0||isClient.compare("NO")==0)&&
										(p1Hostel.compare("ARAVALI")==0||p1Hostel.compare("JWALAMUKHI")==0||p1Hostel.compare("KARAKORAM")==0
												||p1Hostel.compare("VINDHYACHAL")==0||p1Hostel.compare("KUMAON")==0||
												p1Hostel.compare("NILGIRI")||p1Hostel.compare("GIRNAR")||p1Hostel.compare("ZANKSAR")||
										p1Hostel.compare("SATPURA")||p1Hostel.compare("UDAIGIRI")||p1Hostel.compare("SHIVALIK")
										 ||p1Hostel.compare("KAILASH")||p1Hostel.compare("HIMADRI"))){
									b=false;
								}
								else{
									SDL_Color col;
									col.a=255;
									col.r=255;
									col.b=col.g=0;
									this->write(sdlr, "Incorrect Hostel Spelling/ Client/Server Identification", col, 110,600);
									this->playSoundEffect("buzzer", false);
									SDL_Delay(3*1000);

								}

							}
							else if(event.key.keysym.sym==SDLK_TAB){
								n=(n+1)%5;
							}
							else if(event.key.keysym.sym==SDLK_LSHIFT||
									event.key.keysym.sym==SDLK_RSHIFT||
									event.key.keysym.sym==SDLK_LALT||
									event.key.keysym.sym==SDLK_RALT||
									event.key.keysym.sym==SDLK_LCTRL||
									event.key.keysym.sym==SDLK_RCTRL||
									event.key.keysym.sym==SDLK_CAPSLOCK||
									event.key.keysym.sym==SDLK_UP||
									event.key.keysym.sym==SDLK_DOWN||
									event.key.keysym.sym==SDLK_LEFT||
									event.key.keysym.sym==SDLK_RIGHT||
									event.key.keysym.sym==SDLK_ESCAPE){

							}


							else if(event.key.keysym.sym==SDLK_BACKSPACE){
								if(n==0){
									if(p1Name.size()>0){
										this->p1Name.pop_back();
									}
								}
								else if(n==1){
									if(p1Hostel.size()>0){
										this->p1Hostel.pop_back();
									}
								}
								else if(n==2){
									if(isClient.size()>0){
										this->isClient.pop_back();
									}
								}
								else if(n==3){
									if(ip.size()>0){
										this->ip.pop_back();
									}
								}
								else if(n==4){
									if(time.size()>0){
										this->time.pop_back();
									}
								}

							}

							else if(event.key.keysym.sym==SDLK_SPACE){
								if(n==0){
									this->p1Name+=" ";
								}
								else if(n==1){
									this->p1Hostel+=" ";
								}
								else if(n==2){
									this->isClient+=" ";
								}
								else if(n==3){
									this->ip+=" ";
								}

							}
							else{
								temp=SDL_GetKeyName(event.key.keysym.sym);
								if(n==0){
									this->p1Name+=temp;
								}
								else if(n==1){
									this->p1Hostel+=temp;
								}
								else if(n==2){
									this->isClient+=temp;
								}
								else if(n==3){
									this->ip+=temp;
								}
								else if(n==4){
									this->time+=temp;
								}

							}



						}
					}
					//cout<<"Reached"<<endl;
					SDL_Rect x={100,300,800,200};
					//SDL_SetRenderDrawBlendMode(sdlr, SDL_BLENDMODE_BLEND);
					//SDL_SetRenderDrawColor(sdlr, 180,0, 255, 100);
					//SDL_RenderFillRect( sdlr, &x );
					//SDL_SetRenderDrawBlendMode(sdlr, SDL_BLENDMODE_NONE);
					SDL_RenderCopy(sdlr,this->nameScreen,NULL, NULL);
					SDL_Color col;
					col.a=255;
					col.b=255;
					col.r=col.g=0;
					//this->write(sdlr, "Type Player Name & Hostel", col, 110,310);
					//this->write(sdlr, "Press 'Return' key to toggle between the two", col, 110,350);
					//this->write(sdlr, "Press 'Escape' key when done typing", col, 110,390);
					if(n==0){
						this->p1Name+="_";
					}
					if(n==1){
						this->p1Hostel+="_";
					}
					if(n==2){
						this->isClient+="_";
					}
					if(n==3){
						this->ip+="_";
					}
					if(n==4){
						this->time+="_";
					}

					this->write(sdlr, "Name: "+this->p1Name+" Hostel: "+this->p1Hostel, col, 110,440);
					this->write(sdlr, "Are you Client: "+this->isClient+" Server IP Address: "+this->ip, col, 110,500);
					this->write(sdlr, " Game Time: "+this->time, col, 110,550);
					SDL_RenderPresent(sdlr);
					if(n==0){
						this->p1Name.pop_back();
					}
					if(n==1){
						this->p1Hostel.pop_back();
					}
					if(n==2){
						this->isClient.pop_back();
					}
					if(n==3){
						this->ip.pop_back();
					}
					if(n==4){
						this->time.pop_back();
					}

				}
				SDL_SetRenderDrawColor( sdlr, 0xFF, 0xFF, 0xFF, 0xFF );
				//
				this->music.menuToGame();
				if(!this->playMusic){
					this->music.pauseMusic();
				}

				}
			}
		}
		else if(SDL_PointInRect(&p, &buttons[1])==SDL_TRUE){
			this->currentTexture=texture2;
			if(event.type==SDL_MOUSEBUTTONDOWN){
				if(event.button.button!=SDL_BUTTON_RIGHT){
					bool enter=true;
					while(enter){
						while(SDL_PollEvent(&event)){
							if(event.type==SDL_KEYUP && event.key.keysym.sym==SDLK_ESCAPE){
								//this->currentTexture=this->texture;
								enter=false;
							}
						}
						SDL_RenderCopy(sdlr, this->instructions,NULL,NULL);
						if(this->playMusic){
							SDL_Color c;
							c.r=0xFF;
							c.g=0;
							c.b=0;
							c.a=255;
							//cout<<24<<endl;
							this->write(sdlr,"ON",c,1190,20);
						}
						else{
							SDL_Color c;
							c.r=0xFF;
							c.g=0;
							c.b=0;
							c.a=255;
							this->write(sdlr,"OFF",c,1190,20);
						}
						SDL_RenderPresent(sdlr);
					}
//					this->updateFont("support/fonts/OpenSans-Semibold.ttf",32);
//					this->reloadHighScore();
//					string msg1="1. Use arrows/ WASD for motion.";
//					string msg2="2. Complete tasks to gain points.";
//					string msg3="3. Make sure Health (HP) doesn't go to 0.";
//					string msg4="4. Avoid obstacles such as dogs/angry professors.";
//					string msg5="5. Have lunch/dinner at proper time to avoid hp loss.";
////					SDL_Rect temp = {0,0,800,800};
//					SDL_SetRenderDrawColor( sdlr, 0xFF, 0xFF, 0xFF, 0xFF );
//					SDL_Color c;
//					c.r=c.g=0;
//					c.b=c.a=255;
//					SDL_RenderFillRect( sdlr, NULL );
//					this->write(sdlr,msg1,c, 0,0);
//					this->write(sdlr,msg2,c, 0,50);
//					this->write(sdlr,msg3,c, 0,100);
//					this->write(sdlr,msg4,c, 0,150);
//					this->write(sdlr,msg5,c, 0,200);
//					 SDL_RenderPresent(sdlr);
//					 SDL_Delay(10000);
//					this->updateFont("support/fonts/OpenSans-Semibold.ttf",32);

				}
			}
		}
		else if(SDL_PointInRect(&p, &buttons[2])==SDL_TRUE){
			this->currentTexture=texture3;
			if(event.type==SDL_MOUSEBUTTONDOWN){
				if(event.button.button!=SDL_BUTTON_RIGHT){
					this->updateFont("support/fonts/OpenSans-Semibold.ttf",48);
					this->reloadHighScore();
					string msg="High Score = "+to_string(this->highscore);
					SDL_Rect temp = { 900,400,350,66};
					SDL_SetRenderDrawColor( sdlr, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_Color c;
					c.r=c.b=c.g=0;
					c.a=255;
					SDL_RenderFillRect( sdlr, &temp );
					this->write(sdlr,msg,c, 910,400);
					 SDL_RenderPresent(sdlr);
					 SDL_Delay(2000);
					this->updateFont("support/fonts/OpenSans-Semibold.ttf",32);
				}
			}
		}
		else if(SDL_PointInRect(&p, &buttons[3])==SDL_TRUE){
			this->currentTexture=texture4;
			if(event.type==SDL_MOUSEBUTTONDOWN){
				if(event.button.button!=SDL_BUTTON_RIGHT){
				this->isOpen=false;
				this->isPlaying=false;
				}
			}
		}
		else{
			this->currentTexture=texture;
		}
	}
	SDL_SetRenderDrawColor(sdlr,0,0,255,255);
	SDL_RenderFillRect(sdlr,NULL);

	SDL_RenderCopy(sdlr,this->currentTexture,NULL,NULL);
	if(this->playMusic){
		SDL_Color c;
		c.r=0xFF;
		c.g=0;
		c.b=0;
		c.a=255;
		//cout<<24<<endl;
		this->write(sdlr,"ON",c,1190,20);
	}
	else{
		SDL_Color c;
		c.r=0xFF;
		c.g=0;
		c.b=0;
		c.a=255;
		this->write(sdlr,"OFF",c,1190,20);
	}
	SDL_RenderPresent(sdlr);
	return true;
}
void Menu::toggleMusic(){
	this->playMusic=!this->playMusic;
	if(this->playMusic){
		this->music.resumeMusic();
	}
	else{
		this->music.pauseMusic();
	}
}

void Menu::write(SDL_Renderer*sdlr,string text,SDL_Color colour,int x, int y){


	if(this->font==NULL){
		cout<<SDL_GetError()<<endl;
	}
	SDL_Surface* s;
	s=TTF_RenderText_Solid(this->font, text.c_str(), colour);
	SDL_Texture* t;
	t=SDL_CreateTextureFromSurface(sdlr, s);
	if(t==NULL){
	//	cout<<24;
	}
	SDL_Rect r;
	r.x=x;
	r.y=y;
	r.w=s->w;
	r.h=s->h;
	SDL_RenderCopy(sdlr,t,NULL,&r);
	SDL_FreeSurface(s);
	SDL_DestroyTexture(t);

}
void Menu::updateFont(string path,int fontSize){
	this->font=TTF_OpenFont(path.c_str(),fontSize);
}
void Menu::reloadHighScore(){
	fstream stream;
	stream.open("support/highscore.txt");
	string temp;
	getline(stream,temp);
	this->highscore=stoi(temp);
	//cout<<this->highscore<<endl;
}
void Menu::updateHighScore(int score){
	this->highscore=score;
	ofstream stream("support/highscore.txt");
	stream<<this->highscore;
	stream.close();
}
void Menu::playSoundEffect(string name,bool delay){
	if(this->playMusic){
		this->toggleMusic();
		Mix_PlayChannel( -1, this->music.audio_sounds.at(name), 0 );
		if(delay){
		SDL_Delay(3000);
		}
		this->toggleMusic();
	}
	else{
		Mix_PlayChannel( -1, this->music.audio_sounds.at(name), 0 );
		if(delay){
		SDL_Delay(3000);
		}
	}
}
bool Menu::isInteger(string s){
	if(s.find_first_not_of("0123456789") == string::npos){
		return true;
	}
	return false;

}
