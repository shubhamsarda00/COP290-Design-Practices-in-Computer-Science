/*
 * game.cpp
 *
 *  Created on: 29-Mar-2022
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
#include <ctime>
#include "game.h"
#include "menu.h"
#include "player.h"
#include "transferobject.h"

using namespace std;

//Uint32 temp(Uint32 timeInterval, void* param){
//	cout<<"Callback called back with message:\n"<<(char*)(param)<<endl;
//	return 0;
//}

Game::Game(){
		this->playing=true;
		srand(time(0));
	}

void Game::initialize(){
	if(SDL_Init(SDL_INIT_EVERYTHING)<0){
		cout<<"Error while initializing SDL:"<<SDL_GetError()<<endl;
	}
	TTF_Init();
	SDL_Init(SDL_INIT_AUDIO);
	SDL_Init(SDL_INIT_TIMER);
	this->window=SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
	if(this->window==NULL ){
		cout<<"Error in creating Window:"<<SDL_GetError()<<endl;
		this->playing=false;
	}
	this->sdlr = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	if(this->sdlr== NULL ){
		cout<<"Error in creating Renderer:"<<SDL_GetError()<<endl;
		this->playing=false;
	}
//MAZE INITIALIZATION
	this->maze=Maze("support/map_final.txt");

	Tile grass=Tile(2,0,0,32,32,true,"support/maze/grass.jpg");
	grass.loadTile(sdlr);
	this->maze.addTile(grass);
	this->maze.tidMap.insert({"grass",2});

	Tile water=Tile(100,0,0,32,32,true,"support/maze/water.jpg");
	water.loadTile(sdlr);
	this->maze.addTile(water);
	this->maze.tidMap.insert({"water",100});

	Tile road=Tile(53,0,0,32,32,false,"support/maze/road.jpg");
	road.loadTile(sdlr);
	this->maze.addTile(road);
	this->maze.tidMap.insert({"road",53});

	Tile terrain=Tile(1,0,0,32,32,true,"support/maze/terrain1.png");
	terrain.loadTile(sdlr);
	this->maze.addTile(terrain);
	this->maze.tidMap.insert({"terrain",1});

	Tile terrain_road=Tile(51,0,0,32,32,false,"support/maze/terrain_road.png");
	terrain_road.loadTile(sdlr);
	this->maze.addTile(terrain_road);
	this->maze.tidMap.insert({"terrain_road",51});

	Tile terrain_road1=Tile(99,0,0,32,32,false,"support/maze/terrain_road1.png");
	terrain_road1.loadTile(sdlr);
	this->maze.addTile(terrain_road1);
	this->maze.tidMap.insert({"terrain_road1",99});

	Tile terrain_road2=Tile(52,0,0,32,32,false,"support/maze/terrain_road2.png");
	terrain_road2.loadTile(sdlr);
	this->maze.addTile(terrain_road2);
	this->maze.tidMap.insert({"terrain_road2",52});

	Tile terrain_road3=Tile(98,0,0,32,32,false,"support/maze/terrain_road3.png");
	terrain_road3.loadTile(sdlr);
	this->maze.addTile(terrain_road3);
	this->maze.tidMap.insert({"terrain_road3",98});

	Tile building=Tile(149,0,0,32,32,false,"support/building.png");
	building.loadTile(sdlr);
	this->maze.addTile(building);
	this->maze.tidMap.insert({"building",149});
	//cout<<this->maze.tiles.at(149).file<<endl;

	Tile terrain_building=Tile(206,0,0,32,32,false,"support/maze/terrain_building.png");
	terrain_building.loadTile(sdlr);
	this->maze.addTile(terrain_building);
	this->maze.tidMap.insert({"terrain_building",206});

	Tile terrain_building1=Tile(150,0,0,32,32,false,"support/maze/terrain_building1.png");
	terrain_building1.loadTile(sdlr);
	this->maze.addTile(terrain_building1);
	this->maze.tidMap.insert({"terrain_building1",150});

	Tile terrain_building2=Tile(151,0,0,32,32,false,"support/maze/terrain_building2.png");
	terrain_building2.loadTile(sdlr);
	this->maze.addTile(terrain_building2);
	this->maze.tidMap.insert({"terrain_building2",151});

	Tile terrain_building3=Tile(152,0,0,32,32,false,"support/maze/terrain_building3.png");
	terrain_building3.loadTile(sdlr);
	this->maze.addTile(terrain_building3);
	this->maze.tidMap.insert({"terrain_building3",152});


//	Tile brick=Tile(203,0,0,32,32,false,"support/maze/terrain_buidling3.png");
//	terrain_road3.loadTile(sdlr);
//	this->maze.addTile(brick);
	//	Tile t=this->maze.tiles.at(98);
//	cout<<t.id;
	this->maze.readMaze();

//Landmark INIT
	this->loadLandmarkNames(this->sdlr);
//TaskManager Loading
	this->taskManager.loadTasks(this->sdlr);
//Restaurant Menu INIT
	this->loadRestaurantMenus();
//Inspector Gadget INIT
	this->loadInspectorGadget();
//Bank INIT
	this->loadBank();
//PLAYER INITIALIZATION
	this->player1=Player("shubham");
	this->player1.setDstRect(22*32,16*32,32,32);
	this->player1.absoluteDst=this->player1.dst;
	//this->player1.prevAbsoluteDst=this->player1.dst;
	this->player1.setSrcRect(32+118*3,502+350,58,105);
	this->player1.loadAvatar(sdlr, "support/walking_sequence.jpg");
		if(this->player1.getAvatar()==NULL){
			this->playing=false;
		}
	player1.addAnimation("left", 18, 502+120, 0, 120, 68, 100,11,10);
	player1.addAnimation("right", 18, 502, 0, 120, 68, 100,11, 10);
	player1.addAnimation("up", 32, 502+235, 0, 118, 68, 105,11,10);
	player1.addAnimation("down", 32, 502+350, 0, 118, 58, 105,11,10);
	//right:player1.setSrc(18+120*3,502+120*0,68,100);
	//left:player1.setSrc(32+120*2,502+120,68,100);
	//up:player1.setSrc(32+118*6,502+235,58,105);
	//down: player1.setSrc(32+118*3,502+350,58,105);

// FONT INIT
	this->updateFont("support/fonts/OpenSans-Italic.ttf",16,this->font);

	//Func
}
bool Game::render(){

	while(SDL_PollEvent(&event)){
		if(event.type==SDL_QUIT ||(event.type==SDL_KEYDOWN &&event.key.keysym.sym == SDLK_ESCAPE)){
			playing=false;
			myTransferObject.gameOver=1;
			this->transfer();
			cout<<"Exiting The Game"<<endl;
			return false;
		}
		if(event.type==SDL_KEYDOWN){
			const Uint8* ks = SDL_GetKeyboardState( NULL );
			if((ks[SDL_SCANCODE_D] ||ks[SDL_SCANCODE_RIGHT])){//||this->checkCollision(&this->player1,this->player1.speed,0)
				if(this->checkCollision(&this->player1,this->player1.speed,0)){
					//player1.outOfBounds=true;
					player1.moveRight();
				}
				//server.func(int x, int y, int z, int w, int p, string s);
				//server.receive()
//				else{
//					player1.outOfBounds=false;
//				}

//				else{
//					cout<<"Cant Move R"<<endl;
//				}
				//cout<<"right"<<endl;
			}
			if((ks[SDL_SCANCODE_A]||ks[SDL_SCANCODE_LEFT])){//||this->checkCollision(&this->player1,-this->player1.speed,0)
				if(this->checkCollision(&this->player1,-this->player1.speed,0)){
					//player1.outOfBounds=true;
					player1.moveLeft();
				}
//				else{
//					cout<<"Cant Move L"<<endl;
//				}
//				else{
//					player1.outOfBounds=false;
//				}

				//cout<<"left"<<endl;
			}
			if((ks[SDL_SCANCODE_W]|| ks[SDL_SCANCODE_UP])){//||this->checkCollision(&this->player1,0,this->player1.speed)
				if(this->checkCollision(&this->player1,0,-this->player1.speed)){
				//	player1.outOfBounds=true;
					player1.moveUp();
				}
//				else{
//					cout<<"Cant Move U"<<endl;
//				}
//				else{
//					player1.outOfBounds=false;
//				}
//

				//cout<<"up"<<endl;
			}
			if((ks[SDL_SCANCODE_S] ||ks[SDL_SCANCODE_DOWN])){//||this->checkCollision(&this->player1,0,-this->player1.speed)
				if(this->checkCollision(&this->player1,0,this->player1.speed)){
					player1.moveDown();
					//player1.outOfBounds=true;
				}
//				else{
//					cout<<"Cant Move D"<<endl;
//				}
//				else{
//					player1.outOfBounds=false;
//				}

				//cout<<"down"<<endl;
			}
			if(ks[SDL_SCANCODE_F]){
				this->fullscreen=!fullscreen;
				SDL_SetWindowFullscreen(this->window, fullscreen);
			}
			if(ks[SDL_SCANCODE_M]){
				this->playMusic=!this->playMusic;
				this->menu.toggleMusic();
			}

		}
		if(event.type==SDL_KEYUP){
			if(event.key.keysym.sym == SDLK_d || event.key.keysym.sym==SDLK_RIGHT){
				if(this->player1.isMoving){
					// cout<<"STopped"<<endl;
					player1.stopRight();
				}
			}
			if(event.key.keysym.sym == SDLK_a || event.key.keysym.sym==SDLK_LEFT){
				if(this->player1.isMoving){
					player1.stopLeft();
				}
			}
			if(event.key.keysym.sym == SDLK_w || event.key.keysym.sym==SDLK_UP){
				if(this->player1.isMoving){
					player1.stopUp();
				}
			}
			if(event.key.keysym.sym == SDLK_s || event.key.keysym.sym==SDLK_DOWN){
				if(this->player1.isMoving){
					player1.stopDown();
				}
			}
		}

		SDL_GetMouseState(&this->mousex, &this->mousey);
	//	cout<<mousex<<" "<<mousey<<endl;
	}

	SDL_SetRenderDrawColor(sdlr,0,0,255,255);
	SDL_RenderFillRect(sdlr,NULL);
	maze.render(sdlr);
	//maze.scroll(-1, -1);
	player1.render(sdlr);

	//MAZE SCROLLING


	if(player1.dst.x<300){
		maze.scroll(300-player1.dst.x, 0);
		player1.dst.x=300;
		//maze.scroll(player1.speed, 0);
	}
	if(player1.dst.y<300){
		maze.scroll(0,300-player1.dst.y);
		player1.dst.y=300;
	//	maze.scroll(0,player1.speed);
	}
	if(player1.dst.x>WINDOW_WIDTH-300){
		maze.scroll(-(player1.dst.x-(WINDOW_WIDTH-300)),0);
		player1.dst.x=WINDOW_WIDTH-300;
//		maze.scroll(-player1.speed,0);
	}
	if(player1.dst.y>WINDOW_HEIGHT-300){
		maze.scroll(0,-(player1.dst.y-(WINDOW_HEIGHT-300)));
		player1.dst.y=WINDOW_HEIGHT-300;
//		maze.scroll(0,-player1.speed);
	}
//Shield Check
	if(this->player1.shield){
		SDL_Color c;
		c.r=c.a=255;
		c.g=c.b=0;
		this->menu.write(sdlr, "SHIELDS ON", c, 30, 80);
		if(SDL_GetTicks()-this->player1.shieldTimer>=3*60*1000){
			this->player1.shield=false;
			this->player1.shieldTimer=0;
		}
	}
//
	//Landmark Rendering
//	SDL_Rect r;
//	r=this->maze.getLandmarkDest("Jwala");
	this->showLandmarkNames();
//	cout<<"Jwala Coordinates: "<<to_string(r.x)<<" "<<to_string(r.y)<<endl;

	//SCORING AND HP RENDERING
//	if(player1.outOfBounds){
//		player1.hp-=2;
//	}



	string msg=this->player1.name+": HP = "+to_string(this->player1.hp)+"/"+to_string(this->player1.maxhp)+" Score = "
			+to_string(this->player1.score)+" Money: "+to_string(this->player1.money);
	SDL_Rect temp = { 0,0,500,100};
	SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor( sdlr, 40, 60,160, 180 );
	SDL_Color c;
	c.r=c.b=0;
	c.g=c.a=255;
	SDL_RenderFillRect( sdlr, &temp );
	SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
	this->menu.write(this->sdlr,msg,c,4,0);
	if(lunchTime && !lunchTaken){
		c.r=c.a=255;
		c.g=c.b=0;
		this->menu.write(this->sdlr,"Lunch Time!!!!",c,4,62);
	}
//Checking gameover
	if(this->transferObject.gameOver==1){
		this->winGame();
	}
	if(this->transferObject.gameOver==2){
		this->winGame();
	}


	//
	//Render Player 2
	TransferObject sendObject;

	sendObject.dst=this->player1.absoluteDst;
	sendObject.src=this->player1.src;
	sendObject.name=this->player1.name;
	sendObject.hp=this->player1.hp;
	sendObject.maxhp=this->player1.maxhp;
	sendObject.score=this->player1.score;
	sendObject.money=this->player1.money;
	//this->transferObject=receive();
	this->myTransferObject.dst=this->player1.absoluteDst;
	this->myTransferObject.src=this->player1.src;
	this->myTransferObject.hp=this->player1.hp;
	this->myTransferObject.maxhp=this->player1.maxhp;
	this->myTransferObject.money=this->player1.money;
	this->myTransferObject.score=this->player1.score;
	this->myTransferObject.onBike=this->player1.onBike;
	if(!this->isServer){
	this->myTransferObject.connectionStrength=100-this->c.badPercent;
	}

	this->transfer();
	//cout<<"Connection Strength in Game: "<<to_string(myTransferObject.connectionStrength)<<endl;
	 msg=this->transferObject.name+": HP = "+to_string(this->transferObject.hp)+"/"+to_string(this->transferObject.maxhp)+" Score = "
	 		+to_string(this->transferObject.score)+" Money: "+to_string(this->transferObject.money)+" Connection Strength: "+to_string(this->myTransferObject.connectionStrength);
	 this->menu.write(this->sdlr,msg,c,4,28);

	SDL_Rect srcp2=transferObject.src;
	SDL_Rect absdstp2=transferObject.dst;
	absdstp2=this->absoluteToRelative(absdstp2);
	if(!this->transferObject.onBike){
		SDL_RenderCopy(sdlr, this->player1.avatar, &srcp2, &absdstp2);
	}
	else{
		SDL_RenderCopy(sdlr, this->player1.bikeTexture,NULL, &absdstp2);
	}
///////Check Game end condition

	if(SDL_GetTicks()-this->gameClock>=this->gameTime){
		//cout<<this->transferObject.score<<"P2Score"<<endl;
		if(this->player1.score>this->transferObject.score){
			this->winGame();

		}
		else if(this->player1.score<this->transferObject.score){
			this->endGame();

		}
		else if(this->player1.hp>this->transferObject.hp){
			this->winGame();
		}
		else if(this->player1.hp<this->transferObject.hp){
			this->endGame();
		}
		else if(this->player1.money>this->transferObject.money){
			this->winGame();
		}
		else if(this->player1.money<this->transferObject.money){
			this->endGame();
		}
		else if(this->isServer){
			this->winGame();
		}
		else{
			this->endGame();
		}
	}

/////////////////////
// Rendering Gameobjects
	this->scrollGameObjects();
	this->showGameObjects();
	this->checkGameObjectIntersection(&this->player1);

	//ACTIVTY COMPLETION BOX
//	this->showCompletionBox("JWALAMUKHI");
//	this->showCompletionBox("ARAVALI");
//	this->showCompletionBox("KARAKORAM");
//	this->showCompletionBox("NILGIRI");
//	this->showCompletionBox("KUMAON");
//	this->showCompletionBox("VINDHYACHAL");
//	this->showCompletionBox("NALANDA");
//	this->showCompletionBox("SATPURA");
//	this->showCompletionBox("UDAIGIRI");
//	this->showCompletionBox("GIRNAR");
//	this->showCompletionBox("SHIVALIK");
//	this->showCompletionBox("ZANSKAR");
//	this->showCompletionBox("SAC-AREA");
//	this->showCompletionBox("SWIMMING-POOL");
//	this->showCompletionBox("OAT");
//	this->showCompletionBox("HOSPITAL");
//	this->showCompletionBox("FOOTBALL");
//	this->showCompletionBox("LECTURE HALL COMPLEX");
	this->showCompletionBox("SBI");
//	this->showCompletionBox("BIOTECH LAWNS");
//	this->showCompletionBox("LIBRARY");
//	this->showCompletionBox("CSC");
	this->showCompletionBox("CAFETERIA");
	this->showCompletionBox("YULU 1");
	this->showCompletionBox("DELHI-16");
	this->showCompletionBox("MASALA MIX");
	this->showCompletionBox("YULU 2");
	this->showCompletionBox("YULU 3");
	this->showCompletionBox("YULU 4");
//	this->showCompletionBox("HIMADRI");
//	this->showCompletionBox("KAILASH");
	this->showCompletionBox("INSPECTOR GADGET");
//	this->showCompletionBox("GUEST HOUSE");
//	this->showCompletionBox("HAIR SALON");

	//LUNCH CHECK
	if(SDL_GetTicks()-this->timerFuncs.at("startLunch")>=this->timerFuncsInterval.at("startLunch")){
		this->timerFuncs.at("startLunch")=SDL_GetTicks();
		this->startLunch();
	}
	this->checkLunch();
	if(lunchTime && SDL_GetTicks()-this->timerFuncs.at("startLunch")>=60*1000){

		this->stopLunch();
	}
	//////
	//YULU CHECK
	this->checkYulu();
	if(this->player1.onBike){
		if(SDL_GetTicks()-this->timerFuncs.at("payYuluFee")>=this->timerFuncsInterval.at("payYuluFee")){
				this->timerFuncs.at("payYuluFee")=SDL_GetTicks();
				this->payYuluFee();
			}
	}
	///RESTAURANT CHECK
	this->checkRestaurants();
	///Bank Check
	this->checkBank();
	///Inspector gadget check
	this->checkInspectorGadget();
	/// Task Check
	this->checkTaskHelper();
//	cout<<"In the game"<<endl;
	this->checkTaskProgress();
	///
	SDL_SetRenderDrawColor( sdlr, 40, 60,160, 0xFF );
	//

//	if(this->checkLandmarkIntersection("ARAVALI", this->player1.dst)){
//		this->menu.playSoundEffect("eventCompletion", true);
//	}
	//Render GameClock
	this->showTime();
	//Render Task Clock

	//Render Task At Bottom


	//TIMER FUNC
//	cout<<(SDL_GetTicks()-this->temp);
//	cout<<endl;

	//cout<<"absoulte x: "<<this->player1.absoluteDst.x<<"absoulte y: "<<this->player1.absoluteDst.y<<endl;
	if(SDL_GetTicks()-this->timerFuncs.at("updateGameObjects")>=this->timerFuncsInterval.at("updateGameObjects")){
		this->timerFuncs.at("updateGameObjects")=SDL_GetTicks();
		this->updateGameObjects(this->sdlr);
	}


	//
	SDL_RenderPresent(this->sdlr);
	if(this->player1.hp<=0){
		playing=false;
		this->endGame();
		return false;
	}
	return true;
}
void Game::reloadHighScore(){
	fstream stream;
	stream.open("support/highscore.txt");
	string temp;
	getline(stream,temp);
	this->highscore=stoi(temp);
	//cout<<this->highscore<<endl;
}
void Game::updateHighScore(int score){
	this->highscore=score;
	fstream stream1;
	stream1.open("support/highscore.txt");
	string temp;
	getline(stream1,temp);
	if(stoi(temp)<this->highscore){
		ofstream stream("support/highscore.txt");
		stream<<this->highscore;
		//cout<<this->highscore<<" :High score"<<endl;
		stream.close();
	}

}
Game::~Game(){
//	this->player1.~Player();
//	this->maze.~Maze();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(sdlr);
	IMG_Quit();
	SDL_Quit();
	window=NULL;
	sdlr=NULL;

}
void Game::updateFont(string path,int fontSize,TTF_Font* f){
	f=TTF_OpenFont(path.c_str(),fontSize);
}
void Game::write1(SDL_Renderer*sdlr,string text,SDL_Color colour,int x, int y){

	SDL_Surface* s;
	s=TTF_RenderText_Solid(this->menu.font, text.c_str(), colour);
//	if(s==NULL){
//		cout<<"wRoNg"<<endl;;
//	}
//	SDL_Texture* t;
	//t=SDL_CreateTextureFromSurface(sdlr, s);
//	if(t==NULL){
//	//	cout<<24;
//	}
//	SDL_Rect r;
//	r.x=x;
//	r.y=y;
//	r.w=s->w;
//	r.h=s->h;
	//SDL_RenderCopy(sdlr,t,NULL,&r);
//	SDL_FreeSurface(s);
//	SDL_DestroyTexture(t);
}
int Game::getDistance(SDL_Point p1,SDL_Point p2){
	int d=0;
	d=sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
	return d;
}
void Game::startGame(){
	if(this->menu.isClient.compare("YES")==0){
		this->isServer=false;
	}
	else{
		this->isServer=true;
	}
	this->gameTime=stoi(this->menu.time)*60*1000;
	this->ip=this->menu.ip;
//
	if(this->isServer){
		this->player1.setDstRect(25*32,16*32,32,32);
		this->player1.absoluteDst=this->player1.dst;
	}
//	TTF_CloseFont(game.menu.font);
	this->menu.updateFont("support/fonts/OpenSans-Italic.ttf",16);
	this->menu.playSoundEffect("game_start",false);
	this->playMusic=this->menu.playMusic;
	//
	this->loadGameObjects(this->sdlr);
	this->updateGameObjects(this->sdlr);
	this->gameObjectMotionTimer=SDL_GetTicks();
	//
	this->gameClock=SDL_GetTicks();
	//
	this->player1.name=this->menu.p1Name;
	this->player1.hostel=this->menu.p1Hostel;
	this->taskManager.hostel=this->menu.p1Hostel;
	maze.scroll(-20*32, -4*32);
	//
//Timer Funcs INIT
//	this->tid=SDL_AddTimer(3000,temp, (void*)("3 seconds waited!"));
	this->startTime=SDL_GetTicks();
	//Func temp
	this->timerFuncs.insert({"updateGameObjects",(long long unsigned int)SDL_GetTicks()});
	this->timerFuncsInterval.insert({"updateGameObjects",60*1000});

	this->timerFuncs.insert({"startLunch",(long long unsigned int)SDL_GetTicks()});
	this->timerFuncsInterval.insert({"startLunch",5*60*1000});

	this->timerFuncs.insert({"payYuluFee",(long long unsigned int)SDL_GetTicks()});
	this->timerFuncsInterval.insert({"payYuluFee",10*1000});

//	this->timerFuncs.insert({"stopLunch",(long long unsigned int)SDL_GetTicks()-60*1000});
//	this->timerFuncsInterval.insert({"stopLunch",1*60*1000});

	//Sending Player Name
	 if(this->isServer){
	 	transferObject.name=s.transferStringData(this->player1.name);
	 }
	 else{
	 	transferObject.name=c.transferStringData(this->player1.name,this->ip);
	 }

}
void Game::loadGameObjects(SDL_Renderer* sdlr){
	Gameobject g1=Gameobject("prof_f","support/prof_f.jpg",false);
	Gameobject g2=Gameobject("prof_m","support/prof_m.jpg",false);
	Gameobject g3=Gameobject("money","support/money.png",true);
	Gameobject g4=Gameobject("dog","support/dog.jpg",false);
//	g1.addDstRect(32, 32, 64, 64);
//	g2.addDstRect(100, 100, 64, 64);
//	g3.addDstRect(200, 200, 64, 64);
//	g4.addDstRect(300, 300, 64, 64);
	this->gameObjects.insert({"prof_f",g1});
	this->gameObjects.insert({"prof_m",g2});
	this->gameObjects.insert({"money",g3});
	this->gameObjects.insert({"dog",g4});

	for(auto i=this->gameObjects.begin();i!=this->gameObjects.end();i++){
		i->second.loadIcon(sdlr);
	}
}
void Game::updateGameObjects(SDL_Renderer* sdlr){
	vector<SDL_Rect> vec=this->maze.tiles.at(this->maze.tidMap.at("road")).dsts;
	for(auto i=this->gameObjects.begin();i!=this->gameObjects.end();i++){
		Gameobject g=i->second;
		g.dsts.clear();
		g.indexDsts.clear();
		for(int j=0;j<10;j++){
			int y=rand()%vec.size();
			g.indexDsts.push_back(y);
			SDL_Rect r=vec[y];
			r.w=r.h=64;
			g.addDstRect(r.x, r.y, r.w, r.h);
		}
		i->second=g;
	}
}
void Game::startLunch(){
	this->lunchTime=true;
	//cout<<"Lunch Started!!"<<endl;
}
void Game::stopLunch(){
	this->lunchTime=false;
	if(!this->lunchTaken){
		SDL_Color c;
		c.r=c.a=255;
		c.g=c.b=0;
		//cout<<"MISSED"<<endl;
		this->menu.write(sdlr, "Missed Lunch", c, 4, 32);
		this->menu.playSoundEffect("buzzer",false);
		if(!this->player1.shield){
			this->player1.hp-=20;
		}
		SDL_Delay(3*1000);

	}
	this->lunchTaken=false;
}
void Game::checkLunch(){
	if(this->lunchTime){
		if(lunchTaken){

		}
		else{
			this->showCompletionBox(this->player1.hostel);
			if(this->checkLandmarkIntersection(this->player1.hostel, this->player1.dst)){
				this->lunchTaken=true;
				this->menu.playSoundEffect("chime", false);
			}
		}
	}
}
void Game::checkGameObjectIntersection(Player* p){
	bool t=false;
	SDL_Rect r=p->dst;
	Gameobject g1=this->gameObjects.at("dog");
	//cout<<"CHECKING"<<endl;
	for(int i=0;i<g1.dsts.size();i++){
		SDL_Rect r1=g1.dsts[i];
		r1.x-=50;
		r1.y-=50;
		r1.w=150;
		r1.h=150;

		if(SDL_HasIntersection(&r,&r1)==SDL_TRUE){
			t=true;
			if(!this->player1.shield){
			p->hp-=10;
			}
			g1.dsts.erase(g1.dsts.begin()+i);
			g1.indexDsts.erase(g1.indexDsts.begin()+i);
			this->menu.playSoundEffect("dog", false);
			this->gameObjects.at("dog")=g1;
			return;
		}
	}

	Gameobject g2=this->gameObjects.at("prof_f");
	//cout<<"CHECKING"<<endl;
	for(int i=0;i<g2.dsts.size();i++){
		SDL_Rect r1=g2.dsts[i];
		r1.x-=50;
		r1.y-=50;
		r1.w=150;
		r1.h=150;
		if(SDL_HasIntersection(&r,&r1)==SDL_TRUE){
			t=true;
			if(!this->player1.shield){
			p->hp-=5;
			}
			g2.dsts.erase(g2.dsts.begin()+i);
			g2.indexDsts.erase(g2.indexDsts.begin()+i);
			this->menu.playSoundEffect("prof", false);
			this->gameObjects.at("prof_f")=g2;
			return;
		}
	}

	Gameobject g3=this->gameObjects.at("prof_m");
	//cout<<"CHECKING"<<endl;
	for(int i=0;i<g3.dsts.size();i++){
		SDL_Rect r1=g3.dsts[i];
		r1.x-=50;
		r1.y-=50;
		r1.w=150;
		r1.h=150;
		if(SDL_HasIntersection(&r,&r1)==SDL_TRUE){
			t=true;
			if(!this->player1.shield){
			p->hp-=5;
			}
			g3.dsts.erase(g3.dsts.begin()+i);
			g3.indexDsts.erase(g3.indexDsts.begin()+i);
			this->menu.playSoundEffect("prof", false);
			this->gameObjects.at("prof_m")=g3;
			return;
		}
	}

	Gameobject g4=this->gameObjects.at("money");
	//cout<<"CHECKING"<<endl;
	for(int i=0;i<g4.dsts.size();i++){
		SDL_Rect r1=g4.dsts[i];
		r1.x-=50;
		r1.y-=50;
		r1.w=150;
		r1.h=150;
		if(SDL_HasIntersection(&r,&r1)==SDL_TRUE){
			t=true;
			p->money+=30;
			g4.dsts.erase(g4.dsts.begin()+i);
			g4.indexDsts.erase(g4.indexDsts.begin()+i);
			this->menu.playSoundEffect("chime", false);
			this->gameObjects.at("money")=g4;
			return;
		}
	}

}
void Game::showGameObjects(){
//	SDL_Rect dest;
//	dest.x=x;
//	dest.y=y;
//	dest.w=w;
//	dest.h=h;
//	SDL_RenderCopy(sdlr,this->gameObjects.at(name),NULL,&dest);
	for(auto i=this->gameObjects.begin();i!=this->gameObjects.end();i++){
		i->second.render(sdlr);
	}
}
void Game::scrollGameObjects(){
	vector<SDL_Rect> vec=this->maze.tiles.at(this->maze.tidMap.at("road")).dsts;

	if(SDL_GetTicks()-this->gameObjectMotionTimer>=1*1000){
		this->gameObjectMotionDirection=rand()%4;
		this->gameObjectMotionTimer=SDL_GetTicks();
	}
	for(auto i=this->gameObjects.begin();i!=this->gameObjects.end();i++){
		Gameobject g=i->second;

		for(int j=0;j<g.indexDsts.size();j++){
			SDL_Rect r=vec[g.indexDsts[j]];
			r.w=r.h=64;

			if(this->gameObjectMotionDirection==0){
				r.x+=g.vx;
			}
			else if(this->gameObjectMotionDirection==1){
				r.y+=g.vy;
			}
			else if(this->gameObjectMotionDirection==2){
				r.x-=g.vx;
			}
			else if(this->gameObjectMotionDirection==3){
				r.y-=g.vy;
			}


//			if(i->second.position==1){
//				r.x+=i->second.vx;
//				cout<<"SHIFTED"<<endl;
//			}
//			if(i->second.position==2){
//				r.y+=i->second.vy;
//				cout<<"SHIFTED"<<endl;
//			}
			g.dsts[j]=r;

		}

		i->second=g;
	}
}
void Game::temp(){

}
void Game::loadLandmarkName(SDL_Renderer* sdlr,string name){
//	this->menu.updateFont("support/fonts/OpenSans-ExtraBold.ttf",1028);
	SDL_Color c;
	c.a=255;
	c.r=c.b=c.g=0;
	SDL_Surface* s1;

	s1=TTF_RenderText_Solid(this->menu.font,name.c_str(),c);
	SDL_Texture* t1;
	t1=SDL_CreateTextureFromSurface(this->sdlr, s1);

	this->landmarkNameTexture.insert({name,t1});
	SDL_FreeSurface(s1);

}
void Game::loadLandmarkNames(SDL_Renderer* sdlr){
	this->menu.updateFont("support/fonts/OpenSans-ExtraBold.ttf",1028);
	for(auto i=this->maze.landmarks.begin();i!=this->maze.landmarks.end();i++){
		this->loadLandmarkName(this->sdlr,i->first);
	}
	this->menu.updateFont("support/fonts/OpenSans-Italic.ttf",16);

//	if(this->menu.font==NULL){
//		cout<<SDL_GetError()<<endl;
//	}
//	SDL_Color c;
//	c.a=255;
//	c.r=c.b=c.g=0;
//	SDL_Surface* s1;
//	s1=TTF_RenderText_Solid(this->menu.font, "JWALAMUKHI",c);
//
//
//	SDL_Texture* t1;
//
//
//	t1=SDL_CreateTextureFromSurface(sdlr, s1);
//
//	this->landmarkNameTexture.insert({"JWALAMUKHI",t1});

//	if(t==NULL){
//	//	cout<<24;
//	}
//	SDL_Rect r;
//	r.x=x;
//	r.y=y;
//	r.w=s->w;
//	r.h=s->h;
//	SDL_RenderCopy(sdlr,t,NULL,&r);
//	SDL_FreeSurface(s1);

}
void Game::showLandmarkName(string name){
	SDL_Rect r1;
	r1=this->maze.getLandmarkDest(name);
//	r1.w=128;
//	r1.h=128;
	r1.x-=64;
	r1.y-=64;
	SDL_RenderCopy(sdlr,this->landmarkNameTexture.at(name),NULL,&r1);
}
void Game::showLandmarkNames(){
	for(auto i=this->maze.landmarks.begin();i!=this->maze.landmarks.end();i++){
		this->showLandmarkName(i->first);

	}
//	this->showLandmarkName("Jwala");
}
//void Game::loadCompletionBox(SDL_Renderer* sdlr){
//
//}
void Game::showCompletionBox(string name){
	SDL_Rect r=this->maze.landmarkBoxes.at(name);
//	r.w=300;
//	r.h=300;

	SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(this->sdlr, 0x00, 0xFF, 0x00, 100 );
	//SDL_RenderDrawRect(this->sdlr,&r );
	SDL_RenderFillRect( this->sdlr, &r );
	SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
}
void Game::showTime(){
	if(!this->taskManager.taskOngoing){
	long long unsigned int t=SDL_GetTicks()-this->gameClock;
	int days=t/(24*60*1000);
	int hours=(t-days*24*60*1000)/(60*1000);
	int minutes=(t-days*24*60*1000-hours*60*1000)/(1000);
	SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
	//SDL_RenderDrawRect(this->sdlr,&r );
	SDL_Rect r={1200,0,80,50};
	SDL_RenderFillRect( this->sdlr, &r );
	SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
	SDL_Color colour;
	colour.a=255;
	colour.g=colour.b=colour.r=0;
	this->menu.write(this->sdlr, to_string(days)+":"+to_string(hours)+":"+to_string(minutes), colour, 1205, 5);
	}
	else{
		this->showTaskTimer();

	}
}

bool Game::checkLandmarkIntersection(string landMark, SDL_Rect y){
	SDL_Rect r=this->maze.landmarkBoxes.at(landMark);

//	r.w=300;
//	r.h=300;
	bool t=false;
	if(SDL_HasIntersection(&r,&y)==SDL_TRUE){
		t=true;
	}
	return t;
}
bool Game::checkCollision(Player* player,int vx, int vy){

	bool b=false;
	SDL_Rect p=player->dst;
	p.x+=vx;
	p.y+=vy;
	SDL_Rect s=absoluteToRelative(this->transferObject.dst);
	if(SDL_HasIntersection(&p, &s)){
		return false;
	}
	for(auto i=this->maze.tiles.begin();i!=this->maze.tiles.end();i++){
		if(i->first==53 || i->first==52 ||i->first==98||i->first==99||i->first==51){
//			cout<<i->first<<endl;
			//continue;
			Tile t=i->second;
			vector<SDL_Rect> dsts=t.getDsts();
				for(int j=0;j<dsts.size();j++){
				SDL_Rect r=dsts[j];
					if(r.x>=-62 & r.y>=-64 & r.x<=1280+32 & r.y<=800+32){
						if(SDL_HasIntersection(&p, &r)==SDL_TRUE){
	//					if(this->checkIntersection(&r, &p)){
							b=true;
//							cout<<"tile: "<<r.x<<" "<<r.y<<" "<<r.w<<" "<<r.h<<" "<<endl;
//							cout<<"player: "<<p.x<<" "<<p.y<<" "<<p.w<<" "<<p.h<<" "<<endl;
//							cout<<i->first<<endl;
							return b;
							//cout<<"ds";
						}
					}
			}
		}

	}
	return b;
}
bool Game::checkIntersection(SDL_Rect* r1,SDL_Rect* r2){
	bool b=false;
	if(r1->x+r1->w>r2->x && r1->x+r1->w<r2->x+r2->w){
		b=true;
		return b;
	}
	if(r2->x+r2->w>r1->x && r2->x+r2->w<r1->x+r1->w){
		b=true;
		return b;
	}
	if(r1->y+r1->h>r2->y && r1->y+r1->h<r2->y+r2->h){
		b=true;
		return b;
	}
	if(r2->y+r2->h>r1->y && r2->y+r2->h<r1->y+r1->h){
		b=true;
		return b;
	}
	return b;
}
void Game::checkYulu(){
	if(checkLandmarkIntersection("YULU 1", this->player1.dst)||checkLandmarkIntersection("YULU 2", this->player1.dst)
			||checkLandmarkIntersection("YULU 3", this->player1.dst)||checkLandmarkIntersection("YULU 4", this->player1.dst)){
		if(!this->player1.onBike){
			SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
			//SDL_RenderDrawRect(this->sdlr,&r );
			SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
			SDL_RenderFillRect( this->sdlr, &r );
			SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
			SDL_Color colour;
			colour.a=255;
			colour.g=colour.b=colour.r=0;
			this->menu.write(this->sdlr,"Press 'k' to get a YULU @0.5$/second",
					colour, 205, WINDOW_HEIGHT-50+10);
			//while(SDL_PollEvent(&event)){
				const Uint8* ks = SDL_GetKeyboardState( NULL );
				if( ks[SDL_SCANCODE_K]||(this->event.key.keysym.sym==SDLK_k)){
					this->player1.onBike=true;
					this->player1.speed*=2;
					//this->player1.money+=5;
					this->player1.toggleTexture();
					this->timerFuncs.at("payYuluFee")=SDL_GetTicks();
				}
			//}
		}
		else{
			SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
			//SDL_RenderDrawRect(this->sdlr,&r );
			SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
			SDL_RenderFillRect( this->sdlr, &r );
			SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
			SDL_Color colour;
			colour.a=255;
			colour.g=colour.b=colour.r=0;
			this->menu.write(this->sdlr,"Press 'k' to return the YULU",
					colour, 205, WINDOW_HEIGHT-50+10);
		//	while(SDL_PollEvent(&event)){
				const Uint8* ks = SDL_GetKeyboardState( NULL );
				if( ks[SDL_SCANCODE_K]||(this->event.key.keysym.sym==SDLK_k)){
					this->player1.onBike=false;
					this->player1.speed/=2;
					this->player1.toggleTexture();
				}
			//}
		}
	}
}
void Game::payYuluFee(){
	if(this->player1.money>=.5*10){
		this->player1.money-=.5*10;
	}
	else{
		this->menu.playSoundEffect("buzzer", false);
		this->player1.speed/=2;
		this->player1.onBike=false;
		this->player1.money=0;
		this->player1.toggleTexture();
	}
}
void Game::loadRestaurantMenus(){
	SDL_Surface *temp;
	SDL_Surface *temp1;
	SDL_Surface *temp2;
	temp=IMG_Load("support/restaurants/restaurant_menu/delhi16.PNG");
	if(!temp) {
		cout<<"Error while loading delhi16 menu surface!:"<<IMG_GetError()<<endl;
	}
	temp1=IMG_Load("support/restaurants/restaurant_menu/masalamix.PNG");
	if(!temp1) {
		cout<<"Error while loading masala mix menu surface!:"<<IMG_GetError()<<endl;
	}
	temp2=IMG_Load("support/restaurants/restaurant_menu/cafeteria.PNG");
	if(!temp2) {
		cout<<"Error while loading cafeteria menu surface!:"<<IMG_GetError()<<endl;
	}
	this->restaurantMenus.insert({"delhi16",SDL_CreateTextureFromSurface(sdlr,temp)});
	this->restaurantMenus.insert({"masalamix",SDL_CreateTextureFromSurface(sdlr,temp1)});
	this->restaurantMenus.insert({"cafeteria",SDL_CreateTextureFromSurface(sdlr,temp2)});

	SDL_FreeSurface(temp);
	SDL_FreeSurface(temp1);
	SDL_FreeSurface(temp2);

}
void Game::checkRestaurants(){
	if(this->checkLandmarkIntersection("DELHI-16", this->player1.dst)){
		SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
		//SDL_RenderDrawRect(this->sdlr,&r );
		SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
		SDL_RenderFillRect( this->sdlr, &r );
		SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
		SDL_Color colour;
		colour.a=255;
		colour.g=colour.b=colour.r=255;
		this->menu.write(this->sdlr,"Press 'e' to go inside the restaurant!",
				colour, 205, WINDOW_HEIGHT-50+10);
		const Uint8* ks = SDL_GetKeyboardState( NULL );
		if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym==SDLK_e){
			bool enter=true;
			while(enter){
				this->transfer();
				SDL_RenderCopy(sdlr,this->restaurantMenus.at("delhi16"),NULL,NULL);
				this->menu.write(this->sdlr,"Press 'esc' to exit the restaurant!",
						colour, 205, WINDOW_HEIGHT-50+10);
				while(SDL_PollEvent(&event)){
					const Uint8* ks = SDL_GetKeyboardState( NULL );
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_ESCAPE]||event.key.keysym.sym == SDLK_ESCAPE))){
						enter=false;
						//cout<<"EXITING"<<endl;
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_1]||event.key.keysym.sym == SDLK_1))){
						if(this->player1.hp==this->player1.maxhp){
							this->menu.playSoundEffect("buzzer",false);
						}
						else if(this->player1.money>=40){
							this->menu.playSoundEffect("chime", false);
							this->player1.hp+=40;
							if(this->player1.hp>this->player1.maxhp){
								this->player1.hp=this->player1.maxhp;
							}
							this->player1.money-=40;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_2]||event.key.keysym.sym == SDLK_2))){
						if(this->player1.hp==this->player1.maxhp){
							this->menu.playSoundEffect("buzzer",false);
						}
						else if(this->player1.money>=60){
							this->menu.playSoundEffect("chime", false);
							this->player1.hp+=65;
							if(this->player1.hp>this->player1.maxhp){
								this->player1.hp=this->player1.maxhp;
							}
							this->player1.money-=60;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_3]||event.key.keysym.sym == SDLK_3))){
						if(this->player1.hp==this->player1.maxhp){
							this->menu.playSoundEffect("buzzer",false);
						}
						else if(this->player1.money>=30){
							this->menu.playSoundEffect("chime", false);
							this->player1.hp+=25;
							if(this->player1.hp>this->player1.maxhp){
								this->player1.hp=this->player1.maxhp;
							}
							this->player1.money-=30;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}



				}
				string msg=this->player1.name+": HP = "+to_string(this->player1.hp)+"/"+to_string(this->player1.maxhp)+" Score = "+to_string(this->player1.score)+" Money: "+to_string(this->player1.money);
				SDL_Rect temp = { 0,0,370,30};
				SDL_SetRenderDrawColor( sdlr, 40, 60,160, 0xFF );
				SDL_Color c;
				c.r=c.b=0;
				c.g=c.a=255;
				SDL_RenderFillRect( sdlr, &temp );
				this->menu.write(this->sdlr,msg,c,4,0);
				SDL_RenderPresent(this->sdlr);
			}
		}
	}
	else if(this->checkLandmarkIntersection("MASALA MIX", this->player1.dst)){
		SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
		//SDL_RenderDrawRect(this->sdlr,&r );
		SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
		SDL_RenderFillRect( this->sdlr, &r );
		SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
		SDL_Color colour;
		colour.a=255;
		colour.g=colour.b=colour.r=255;
		this->menu.write(this->sdlr,"Press 'e' to go inside the restaurant!",
				colour, 205, WINDOW_HEIGHT-50+10);

		const Uint8* ks = SDL_GetKeyboardState( NULL );
		if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym==SDLK_e){
			bool enter=true;
			while(enter){
				this->transfer();
				SDL_RenderCopy(sdlr,this->restaurantMenus.at("masalamix"),NULL,NULL);
				this->menu.write(this->sdlr,"Press 'esc' to exit the restaurant!",
						colour, 205, WINDOW_HEIGHT-50+10);
				while(SDL_PollEvent(&event)){

					const Uint8* ks = SDL_GetKeyboardState( NULL );
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_ESCAPE]||event.key.keysym.sym == SDLK_ESCAPE))){
						enter=false;
						//cout<<"EXITING"<<endl;
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_1]||event.key.keysym.sym == SDLK_1))){
						if(this->player1.hp==this->player1.maxhp){
							this->menu.playSoundEffect("buzzer",false);
						}
						else if(this->player1.money>=60){
							this->menu.playSoundEffect("chime", false);
							this->player1.hp+=65;
							if(this->player1.hp>this->player1.maxhp){
								this->player1.hp=this->player1.maxhp;
							}
							this->player1.money-=60;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_2]||event.key.keysym.sym == SDLK_2))){
						if(this->player1.hp==this->player1.maxhp){
							this->menu.playSoundEffect("buzzer",false);
						}
						else if(this->player1.money>=70){
							this->menu.playSoundEffect("chime", false);
							this->player1.hp+=75;
							if(this->player1.hp>this->player1.maxhp){
								this->player1.hp=this->player1.maxhp;
							}
							this->player1.money-=70;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_3]||event.key.keysym.sym == SDLK_3))){
						if(this->player1.hp==this->player1.maxhp){
							this->menu.playSoundEffect("buzzer",false);
						}
						else if(this->player1.money>=40){
							this->menu.playSoundEffect("chime", false);
							this->player1.hp+=40;
							if(this->player1.hp>this->player1.maxhp){
								this->player1.hp=this->player1.maxhp;
							}
							this->player1.money-=40;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}



				}
				string msg=this->player1.name+": HP = "+to_string(this->player1.hp)+"/"+to_string(this->player1.maxhp)+" Score = "+to_string(this->player1.score)+" Money: "+to_string(this->player1.money);
				SDL_Rect temp = { 0,0,370,30};
				SDL_SetRenderDrawColor( sdlr, 40, 60,160, 0xFF );
				SDL_Color c;
				c.r=c.b=0;
				c.g=c.a=255;
				SDL_RenderFillRect( sdlr, &temp );
				this->menu.write(this->sdlr,msg,c,4,0);
				SDL_RenderPresent(this->sdlr);
			}
		}

	}
	else if(this->checkLandmarkIntersection("CAFETERIA", this->player1.dst)){
		SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
		//SDL_RenderDrawRect(this->sdlr,&r );
		SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
		SDL_RenderFillRect( this->sdlr, &r );
		SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
		SDL_Color colour;
		colour.a=255;
		colour.g=colour.b=colour.r=255;
		this->menu.write(this->sdlr,"Press 'e' to go inside the restaurant!",
				colour, 205, WINDOW_HEIGHT-50+10);

		const Uint8* ks = SDL_GetKeyboardState( NULL );
		if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym==SDLK_e){
			bool enter=true;
			while(enter){
				this->transfer();
				SDL_RenderCopy(sdlr,this->restaurantMenus.at("cafeteria"),NULL,NULL);
				this->menu.write(this->sdlr,"Press 'esc' to exit the restaurant!",
						colour, 205, WINDOW_HEIGHT-50+10);
				while(SDL_PollEvent(&event)){
					const Uint8* ks = SDL_GetKeyboardState( NULL );
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_ESCAPE]||event.key.keysym.sym == SDLK_ESCAPE))){
						enter=false;
						//cout<<"EXITING"<<endl;
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_1]||event.key.keysym.sym == SDLK_1))){
						if(this->player1.hp==this->player1.maxhp){
							this->menu.playSoundEffect("buzzer",false);
						}
						else if(this->player1.money>=15){
							this->menu.playSoundEffect("chime", false);
							this->player1.hp+=15;
							if(this->player1.hp>this->player1.maxhp){
								this->player1.hp=this->player1.maxhp;
							}
							this->player1.money-=15;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_2]||event.key.keysym.sym == SDLK_2))){
						if(this->player1.hp==this->player1.maxhp){
							this->menu.playSoundEffect("buzzer",false);
						}
						else if(this->player1.money>=30){
							this->menu.playSoundEffect("chime", false);
							this->player1.hp+=35;
							if(this->player1.hp>this->player1.maxhp){
								this->player1.hp=this->player1.maxhp;
							}
							this->player1.money-=30;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_3]||event.key.keysym.sym == SDLK_3))){
						if(this->player1.hp==this->player1.maxhp){
							this->menu.playSoundEffect("buzzer",false);
						}
						else if(this->player1.money>=10){
							this->menu.playSoundEffect("chime", false);
							this->player1.hp+=10;
							if(this->player1.hp>this->player1.maxhp){
								this->player1.hp=this->player1.maxhp;
							}
							this->player1.money-=10;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}



				}
				string msg=this->player1.name+": HP = "+to_string(this->player1.hp)+"/"+to_string(this->player1.maxhp)+" Score = "+to_string(this->player1.score)+" Money: "+to_string(this->player1.money);
				SDL_Rect temp = { 0,0,370,30};
				SDL_SetRenderDrawColor( sdlr, 40, 60,160, 0xFF );
				SDL_Color c;
				c.r=c.b=0;
				c.g=c.a=255;
				SDL_RenderFillRect( sdlr, &temp );
				this->menu.write(this->sdlr,msg,c,4,0);
				SDL_RenderPresent(this->sdlr);
			}
		}
	}
}
void Game::loadInspectorGadget(){
	SDL_Surface *temp;

	temp=IMG_Load("support/inspectorgadget/inspectorgadget.PNG");
	if(!temp) {
		cout<<"Error while loading inspector Gadget surface!:"<<IMG_GetError()<<endl;
	}

	this->inspectorGadget=SDL_CreateTextureFromSurface(sdlr,temp);


	SDL_FreeSurface(temp);
}
void Game::checkInspectorGadget(){
	if(this->checkLandmarkIntersection("INSPECTOR GADGET",this->player1.dst)){
		SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
		//SDL_RenderDrawRect(this->sdlr,&r );
		SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
		SDL_RenderFillRect( this->sdlr, &r );
		SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
		SDL_Color colour;
		colour.a=255;
		colour.g=colour.b=colour.r=255;
		this->menu.write(this->sdlr,"Press 'e' to go inside the store!",
				colour, 205, WINDOW_HEIGHT-50+10);
		const Uint8* ks = SDL_GetKeyboardState( NULL );
		if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym==SDLK_e){
			bool enter=true;
			while(enter){
				this->transfer();
				SDL_RenderCopy(sdlr,this->inspectorGadget,NULL,NULL);
				this->menu.write(this->sdlr,"Press 'esc' to exit the store!",
						colour, 205, WINDOW_HEIGHT-50+10);
				while(SDL_PollEvent(&event)){
					const Uint8* ks = SDL_GetKeyboardState( NULL );
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_ESCAPE]||event.key.keysym.sym == SDLK_ESCAPE))){
						enter=false;
						//cout<<"EXITING"<<endl;
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_1]||event.key.keysym.sym == SDLK_1))){

						if(this->player1.money>=100){
							this->menu.playSoundEffect("chime", false);
							this->player1.shield=true;
							this->player1.shieldTimer=SDL_GetTicks();
							this->player1.money-=100;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_2]||event.key.keysym.sym == SDLK_2))){

						if(this->player1.money>=200){
							this->menu.playSoundEffect("chime", false);
							this->player1.scoreMultiplier=2;
							this->player1.money-=200;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_3]||event.key.keysym.sym == SDLK_3))){
						if(this->player1.money>=120){
							this->menu.playSoundEffect("chime", false);
							this->player1.maxhp=200;

							this->player1.money-=120;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_4]||event.key.keysym.sym == SDLK_4))){
						if(this->player1.money>=200 &!this->player1.runningShoes){
							this->menu.playSoundEffect("chime", false);

							this->player1.speed*=2;
							this->player1.runningShoes=true;
							this->player1.money-=200;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_5]||event.key.keysym.sym == SDLK_5))){
						if(this->player1.money>=240){
							this->menu.playSoundEffect("chime", false);
							int l=rand()%2;
							if(l==0){
								this->player1.score=0;
								this->menu.playSoundEffect("buzzer", false);
							}
							else{
								this->player1.score*=2;
								this->menu.playSoundEffect("chime", false);
							}
							this->player1.money-=240;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}


				}
				string msg=this->player1.name+": HP = "+to_string(this->player1.hp)+"/"+to_string(this->player1.maxhp)+" Score = "+to_string(this->player1.score)+" Money: "+to_string(this->player1.money);
				SDL_Rect temp = { 0,0,370,30};
				SDL_SetRenderDrawColor( sdlr, 40, 60,160, 0xFF );
				SDL_Color c;
				c.r=c.b=0;
				c.g=c.a=255;
				SDL_RenderFillRect( sdlr, &temp );
				this->menu.write(this->sdlr,msg,c,4,0);
				SDL_RenderPresent(this->sdlr);
			}
		}
	}
}
void Game::checkTaskHelper(){
	const Uint8* ks = SDL_GetKeyboardState( NULL );
		if(ks[SDL_SCANCODE_T]||this->event.key.keysym.sym==SDLK_t){
		//this->taskManager.checkTasks(this->sdlr, this->event);
		//cout<<"OUTTT"<<endl;
		bool enter=true;
		while(enter){
			this->transfer();
			SDL_RenderCopy(sdlr,this->taskManager.currentTexture,NULL,NULL);

			while(SDL_PollEvent(&event)){
				const Uint8* ks = SDL_GetKeyboardState( NULL );
				if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_ESCAPE]||event.key.keysym.sym == SDLK_ESCAPE))){
					enter=false;
					//cout<<"EXITING"<<endl;
				}

				if((!this->taskManager.taskOngoing && (event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_S]||event.key.keysym.sym == SDLK_s)))){

					int taskNumber=this->taskManager.getTask();
					if(taskNumber==-1){
						this->menu.playSoundEffect("buzzer",false);
						enter=false;
					}
					else{
						this->taskManager.currentTask=taskNumber;
						this->taskManager.taskOngoing=true;
						this->taskManager.taskTimer=SDL_GetTicks();
						this->taskManager.currentTexture=this->taskManager.tasks.at(taskNumber);


					}
				}

			}
			string msg=this->player1.name+": HP = "+to_string(this->player1.hp)+"/"+to_string(this->player1.maxhp)+" Score = "+to_string(this->player1.score)+" Money: "+to_string(this->player1.money);
			SDL_Rect temp = { 0,0,370,30};
			SDL_SetRenderDrawColor( sdlr, 40, 60,160, 0xFF );
			SDL_Color c;
			c.r=c.b=0;
			c.g=c.a=255;
			SDL_RenderFillRect( sdlr, &temp );
			string task="Task: "+to_string(this->taskManager.tasksCompleted.size()+1)+"/10";
			this->menu.write(this->sdlr,msg,c,4,0);


			this->menu.write(this->sdlr,task,c,400,0);
			//this->menu.updateFont("support/fonts/OpenSans-Italic.ttf",16);
			SDL_RenderPresent(sdlr);
		}
	}

}
void Game::showTaskTimer(){
	int taskTime=this->taskManager.taskTimes.at(this->taskManager.currentTask);
	long long unsigned int t=SDL_GetTicks()-this->taskManager.taskTimer;
	if(t>=taskTime){
		this->menu.playSoundEffect("buzzer", false);
		this->taskManager.taskProgress=0;
		this->taskManager.taskOngoing=false;
//		this->player1.score+=40*this->player1.scoreMultiplier;
		this->taskManager.tasksCompleted.push_back(this->taskManager.currentTask);
		this->taskManager.currentTexture=this->taskManager.tasks.at(0);
		this->taskManager.currentTask=0;
	}
	t=taskTime-t;
	int days=t/(24*60*1000);
	int hours=(t-days*24*60*1000)/(60*1000);
	int minutes=(t-days*24*60*1000-hours*60*1000)/(1000);
	SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
	//SDL_RenderDrawRect(this->sdlr,&r );
	SDL_Rect r={1120,0,80+100,50};
	SDL_RenderFillRect( this->sdlr, &r );
	SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
	SDL_Color colour;
	colour.a=255;
	colour.g=colour.b=colour.r=0;
	this->menu.write(this->sdlr,"Task Timer: "+ to_string(days)+":"+to_string(hours)+":"+to_string(minutes), colour, 1150, 5);
}
void Game::checkTaskProgress(){
	if(this->taskManager.taskOngoing){


		if(this->taskManager.currentTask==2){
			if(this->taskManager.taskProgress==0){
				this->showCompletionBox("HOSPITAL");

				if(this->checkLandmarkIntersection("HOSPITAL",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to get the medicines!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						if(this->player1.money>=40){
							this->player1.money-=40;
							this->menu.playSoundEffect("chime", false);
							this->taskManager.taskProgress+=1;
						}
						else{
							this->menu.playSoundEffect("buzzer", false);
						}
					}
				}
			}
			if(this->taskManager.taskProgress==1){
				this->showCompletionBox("VINDHYACHAL");
				if(this->checkLandmarkIntersection("VINDHYACHAL",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to deliver the medicines!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						//this->menu.playSoundEffect("chime", false);
						this->menu.playSoundEffect("eventCompletion", false);
						this->taskManager.taskProgress=0;
						this->taskManager.taskOngoing=false;
						this->player1.score+=(100*(10*60*1000-(SDL_GetTicks()-this->taskManager.taskTimer))/(10*60*1000))*this->player1.scoreMultiplier;
						this->taskManager.tasksCompleted.push_back(this->taskManager.currentTask);
						this->taskManager.currentTexture=this->taskManager.tasks.at(0);
						this->taskManager.currentTask=0;
						if(this->taskManager.tasksCompleted.size()==this->taskManager.totalTasks){
							this->taskManager.currentTexture=this->taskManager.tasks.at(this->taskManager.totalTasks+1);

						}
					}
				}

			}
		}

		if(this->taskManager.currentTask==3){
			if(this->taskManager.taskProgress==0){
				this->showCompletionBox(this->player1.hostel);

				if(this->checkLandmarkIntersection(this->player1.hostel,this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to assemble all the facches!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						this->menu.playSoundEffect("chime", false);
						this->taskManager.taskProgress+=1;
					}
				}
			}
			if(this->taskManager.taskProgress==1){
				this->showCompletionBox("OAT");
				if(this->checkLandmarkIntersection("OAT",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to enter OAT!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						//this->menu.playSoundEffect("chime", false);
						this->menu.playSoundEffect("eventCompletion", false);
						this->taskManager.taskProgress=0;
						this->taskManager.taskOngoing=false;
						this->player1.score+=(100*(10*60*1000-(SDL_GetTicks()-this->taskManager.taskTimer))/(10*60*1000))*this->player1.scoreMultiplier;
						this->taskManager.tasksCompleted.push_back(this->taskManager.currentTask);
						this->taskManager.currentTexture=this->taskManager.tasks.at(0);
						this->taskManager.currentTask=0;
						if(this->taskManager.tasksCompleted.size()==this->taskManager.totalTasks){
							this->taskManager.currentTexture=this->taskManager.tasks.at(this->taskManager.totalTasks+1);

						}
					}
				}

			}
		}
		if(this->taskManager.currentTask==4){
			if(this->taskManager.taskProgress==0){
				this->showCompletionBox("JWALAMUKHI");

				if(this->checkLandmarkIntersection("JWALAMUKHI",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to give your clothes for laundering!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						if(this->player1.money>=20){
							this->player1.money-=20;
							this->menu.playSoundEffect("chime", false);
							this->taskManager.taskProgress+=1;
						}
						else{
							this->menu.playSoundEffect("buzzer", false);
						}
					}
				}
			}
			if(this->taskManager.taskProgress==1){
				this->showCompletionBox("HAIR SALON");
				if(this->checkLandmarkIntersection("HAIR SALON",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to get a hair cut!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						if(this->player1.money>=20){
							this->player1.money-=20;
							this->menu.playSoundEffect("chime", false);
							this->taskManager.taskProgress+=1;
						}
						else{
							this->menu.playSoundEffect("buzzer", false);
						}
					}
				}

			}
			if(this->taskManager.taskProgress==2){
				this->showCompletionBox("JWALAMUKHI");
				if(this->checkLandmarkIntersection("JWALAMUKHI",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to collect your clothes!",
							colour, 205, WINDOW_HEIGHT-50+10);
					if(this->event.key.keysym.sym==SDLK_e){
						this->menu.playSoundEffect("chime", false);
						this->taskManager.taskProgress+=1;
					}
				}

			}
			if(this->taskManager.taskProgress==3){
				this->showCompletionBox(this->player1.hostel);
				if(this->checkLandmarkIntersection(this->player1.hostel,this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to enter the hostel!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						this->menu.playSoundEffect("eventCompletion", false);
						//this->menu.playSoundEffect("chime", false);
						this->taskManager.taskProgress=0;
						this->taskManager.taskOngoing=false;
						this->player1.score+=(100*(10*60*1000-(SDL_GetTicks()-this->taskManager.taskTimer))/(10*60*1000))*this->player1.scoreMultiplier;
						this->taskManager.tasksCompleted.push_back(this->taskManager.currentTask);
						this->taskManager.currentTexture=this->taskManager.tasks.at(0);
						this->taskManager.currentTask=0;
						if(this->taskManager.tasksCompleted.size()==this->taskManager.totalTasks){
							this->taskManager.currentTexture=this->taskManager.tasks.at(this->taskManager.totalTasks+1);

						}
					}
				}

			}
		}
		if(this->taskManager.currentTask==5){
			if(this->taskManager.taskProgress==0){
				this->showCompletionBox("KAILASH");

				if(this->checkLandmarkIntersection("KAILASH",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to learn about the secret deals!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){

						this->menu.playSoundEffect("chime", false);
						this->taskManager.taskProgress+=1;
					}
				}
			}
			if(this->taskManager.taskProgress==1){
				this->showCompletionBox("SATPURA");
				if(this->checkLandmarkIntersection("SATPURA",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to learn about the secret deals!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						this->menu.playSoundEffect("chime", false);
						this->taskManager.taskProgress+=1;

					}
				}

			}
			if(this->taskManager.taskProgress==2){
				this->showCompletionBox("KUMAON");
				if(this->checkLandmarkIntersection("KUMAON",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to learn about the secret deals!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						this->menu.playSoundEffect("chime", false);
						this->taskManager.taskProgress+=1;
					}
				}

			}
			if(this->taskManager.taskProgress==3){
				this->showCompletionBox(this->player1.hostel);
				if(this->checkLandmarkIntersection(this->player1.hostel,this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to report the information learned!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						this->menu.playSoundEffect("eventCompletion", false);
						//this->menu.playSoundEffect("chime", false);
						this->taskManager.taskProgress=0;
						this->taskManager.taskOngoing=false;
						this->player1.score+=(100*(10*60*1000-(SDL_GetTicks()-this->taskManager.taskTimer))/(10*60*1000))*this->player1.scoreMultiplier;
						this->taskManager.tasksCompleted.push_back(this->taskManager.currentTask);
						this->taskManager.currentTexture=this->taskManager.tasks.at(0);
						this->taskManager.currentTask=0;
						if(this->taskManager.tasksCompleted.size()==this->taskManager.totalTasks){
							this->taskManager.currentTexture=this->taskManager.tasks.at(this->taskManager.totalTasks+1);

						}

					}
				}

			}
		}
		if(this->taskManager.currentTask==6){
			if(this->taskManager.taskProgress==0){
				this->showCompletionBox("LIBRARY");

				if(this->checkLandmarkIntersection("LIBRARY",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to get the required books",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){

						this->menu.playSoundEffect("chime", false);
						this->taskManager.taskProgress+=1;
					}
				}
			}
			if(this->taskManager.taskProgress==1){
				this->showCompletionBox("CSC");
				if(this->checkLandmarkIntersection("CSC",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to enter CSC!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						this->menu.playSoundEffect("eventCompletion", false);
						//this->menu.playSoundEffect("chime", false);
						this->taskManager.taskProgress=0;
						this->taskManager.taskOngoing=false;
						this->player1.score+=(100*(10*60*1000-(SDL_GetTicks()-this->taskManager.taskTimer))/(10*60*1000))*this->player1.scoreMultiplier;
						this->taskManager.tasksCompleted.push_back(this->taskManager.currentTask);
						this->taskManager.currentTexture=this->taskManager.tasks.at(0);
						this->taskManager.currentTask=0;
						if(this->taskManager.tasksCompleted.size()==this->taskManager.totalTasks){
							this->taskManager.currentTexture=this->taskManager.tasks.at(this->taskManager.totalTasks+1);

						}

					}
				}

			}
		}
		if(this->taskManager.currentTask==7){
			if(this->taskManager.taskProgress==0){
				this->showCompletionBox("ARAVALI");

				if(this->checkLandmarkIntersection("ARAVALI",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to buy pens! Shop is out of A4 sheets, head to printing shop in library!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						if(this->player1.money>=5){
							this->player1.money-=5;
							this->menu.playSoundEffect("chime", false);
							this->taskManager.taskProgress+=1;
						}
						else{
							this->menu.playSoundEffect("buzzer", false);
						}
					}
				}
			}
			if(this->taskManager.taskProgress==1){
				this->showCompletionBox("LIBRARY");
				if(this->checkLandmarkIntersection("LIBRARY",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to buy A4 sheets!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						if(this->player1.money>=5){
							this->player1.money-=5;
							this->menu.playSoundEffect("eventCompletion", false);
							//this->menu.playSoundEffect("chime", false);
							this->taskManager.taskProgress=0;
							this->taskManager.taskOngoing=false;
							this->player1.score+=(100*(10*60*1000-(SDL_GetTicks()-this->taskManager.taskTimer))/(10*60*1000))*this->player1.scoreMultiplier;
							this->taskManager.tasksCompleted.push_back(this->taskManager.currentTask);
							this->taskManager.currentTexture=this->taskManager.tasks.at(0);
							this->taskManager.currentTask=0;
							if(this->taskManager.tasksCompleted.size()==this->taskManager.totalTasks){
								this->taskManager.currentTexture=this->taskManager.tasks.at(this->taskManager.totalTasks+1);
							}
						}
						else{
							this->menu.playSoundEffect("buzzer", false);
						}

					}
				}

			}
		}
		if(this->taskManager.currentTask==8){
			if(this->taskManager.taskProgress==0){
				this->showCompletionBox("LECTURE HALL COMPLEX");

				if(this->checkLandmarkIntersection("LECTURE HALL COMPLEX",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to get wedding invite!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){

						this->menu.playSoundEffect("chime", false);
						this->taskManager.taskProgress+=1;
					}
				}
			}
			if(this->taskManager.taskProgress==1){
				this->showCompletionBox("NALANDA");
				if(this->checkLandmarkIntersection("NALANDA",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to enter the ground!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						this->menu.playSoundEffect("eventCompletion", false);
						//this->menu.playSoundEffect("chime", false);
						this->player1.hp+=50;
						if(this->player1.hp>this->player1.maxhp){
							this->player1.hp=this->player1.maxhp;
						}
						this->taskManager.taskProgress=0;
						this->taskManager.taskOngoing=false;
						this->player1.score+=(100*(10*60*1000-(SDL_GetTicks()-this->taskManager.taskTimer))/(10*60*1000))*this->player1.scoreMultiplier;
						this->taskManager.tasksCompleted.push_back(this->taskManager.currentTask);
						this->taskManager.currentTexture=this->taskManager.tasks.at(0);
						this->taskManager.currentTask=0;
						if(this->taskManager.tasksCompleted.size()==this->taskManager.totalTasks){
							this->taskManager.currentTexture=this->taskManager.tasks.at(this->taskManager.totalTasks+1);
						}

					}
				}

			}
		}
		if(this->taskManager.currentTask==9){
			if(this->taskManager.taskProgress==0){
				this->showCompletionBox("GUEST HOUSE");

				if(this->checkLandmarkIntersection("GUEST HOUSE",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to meet the band members!!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){

						this->menu.playSoundEffect("chime", false);
						this->taskManager.taskProgress+=1;
					}
				}
			}
			if(this->taskManager.taskProgress==1){
				this->showCompletionBox("SAC-AREA");
				if(this->checkLandmarkIntersection("SAC-AREA",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to enter the SAC ground!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						//this->menu.playSoundEffect("chime", false);
						this->menu.playSoundEffect("eventCompletion", false);
						this->taskManager.taskProgress=0;
						this->taskManager.taskOngoing=false;
						this->player1.score+=(100*(10*60*1000-(SDL_GetTicks()-this->taskManager.taskTimer))/(10*60*1000))*this->player1.scoreMultiplier;
						this->taskManager.tasksCompleted.push_back(this->taskManager.currentTask);
						this->taskManager.currentTexture=this->taskManager.tasks.at(0);
						this->taskManager.currentTask=0;
						if(this->taskManager.tasksCompleted.size()==this->taskManager.totalTasks){
							this->taskManager.currentTexture=this->taskManager.tasks.at(this->taskManager.totalTasks+1);
						}

					}
				}

			}
		}
		if(this->taskManager.currentTask==10){
			if(this->taskManager.taskProgress==0){
				this->showCompletionBox(this->player1.hostel);

				if(this->checkLandmarkIntersection(this->player1.hostel,this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to get pick the jersey from your room!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){

						this->menu.playSoundEffect("chime", false);
						this->taskManager.taskProgress+=1;
					}
				}
			}
			if(this->taskManager.taskProgress==1){
				this->showCompletionBox("LECTURE HALL COMPLEX");
				if(this->checkLandmarkIntersection("LECTURE HALL COMPLEX",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to get the jersey signed!!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						//this->menu.playSoundEffect("chime", false);
						this->menu.playSoundEffect("eventCompletion", false);
						this->taskManager.taskProgress=0;
						this->taskManager.taskOngoing=false;
						this->player1.score+=(100*(10*60*1000-(SDL_GetTicks()-this->taskManager.taskTimer))/(10*60*1000))*this->player1.scoreMultiplier;
						this->taskManager.tasksCompleted.push_back(this->taskManager.currentTask);
						this->taskManager.currentTexture=this->taskManager.tasks.at(0);
						this->taskManager.currentTask=0;
						if(this->taskManager.tasksCompleted.size()==this->taskManager.totalTasks){
							this->taskManager.currentTexture=this->taskManager.tasks.at(this->taskManager.totalTasks+1);
						}

					}
				}

			}
		}
		if(this->taskManager.currentTask==1){
			if(this->taskManager.taskProgress==0){
				this->showCompletionBox(this->player1.hostel);

				if(this->checkLandmarkIntersection(this->player1.hostel,this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to get pick up the football and call your friends!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){

						this->menu.playSoundEffect("chime", false);
						this->taskManager.taskProgress+=1;
					}
				}
			}
			if(this->taskManager.taskProgress==1){
				this->showCompletionBox("FOOTBALL");
				if(this->checkLandmarkIntersection("FOOTBALL",this->player1.dst)){
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
					SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
					//SDL_RenderDrawRect(this->sdlr,&r );
					SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
					SDL_RenderFillRect( this->sdlr, &r );
					SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
					SDL_Color colour;
					colour.a=255;
					colour.g=colour.b=colour.r=255;
					this->menu.write(this->sdlr,"Press 'e' to enter the ground!",
							colour, 205, WINDOW_HEIGHT-50+10);
					const Uint8* ks = SDL_GetKeyboardState( NULL );		
					if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
						bool enter=true;
						int goals=0;
						int mousex,mousey;
						SDL_Rect r;
						r.x=163;
						r.y=270;
						r.w=880;
						r.h=260;
						bool reset=true;
						SDL_Rect dst={590,680,100,100};
						while(goals<=20 && enter){
							this->transfer();
							if(this->taskManager.taskTimes.at(1)<=SDL_GetTicks()-this->taskManager.taskTimer){
								enter=false;
								this->menu.playSoundEffect("buzzer", false);
							}
							while(SDL_PollEvent(&event)){

								SDL_GetMouseState(&mousex, &mousey);
								SDL_Point p;
								p.x=mousex;
								p.y=mousey;
								const Uint8* ks = SDL_GetKeyboardState( NULL );		
					// if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym == SDLK_e){
								if(((event.type==SDL_MOUSEBUTTONUP && event.button.button==SDL_BUTTON_LEFT )||(event.type==SDL_KEYUP &&(ks[SDL_SCANCODE_S]||this->event.key.keysym.sym == SDLK_s)))){
									if(SDL_PointInRect(&p, &r)&&reset){
										this->menu.playSoundEffect("chime", false);
										dst.x=mousex;
										dst.y=mousey;
										goals+=1;
										reset=false;
									}
									else{
										this->menu.playSoundEffect("buzzer", false);
									}
								}
								if((event.type==SDL_KEYUP &&(ks[SDL_SCANCODE_R]||this->event.key.keysym.sym == SDLK_r))){
									dst.x=590;
									dst.y=680;
									reset=true;
								}
							}

							//cout<<"X: "<<to_string(mousex)<<" Y: "<<to_string(mousey)<<endl;

							SDL_RenderCopy(sdlr, this->taskManager.footballgoal, NULL, NULL);
							SDL_RenderCopy(sdlr, this->taskManager.football, NULL, &dst);
							string msg=this->player1.name+": HP = "+to_string(this->player1.hp)+"/"+to_string(this->player1.maxhp)+" Score = "+to_string(this->player1.score)+" Money: "+to_string(this->player1.money);

							string msg1="GOALS SCORED: "+to_string(goals);
							string msg2="Keep your mouse pointer in the goal and Press 's' or 'left mouse button' to score.";
							string msg3="Press 'r' to Reset the ball. You must reset after every goal";
							SDL_Rect temp = { 0,0,370,30};
							SDL_SetRenderDrawColor( sdlr, 40, 60,160, 0xFF );
							SDL_Color c;
							c.r=c.b=0;
							c.g=c.a=255;
							SDL_RenderFillRect( sdlr, &temp );
							this->menu.write(this->sdlr,msg,c,4,0);
							this->menu.write(this->sdlr,msg2,c,4,200);
							this->menu.write(this->sdlr,msg3,c,4,160);

							this->menu.write(this->sdlr,msg1,c,500,5);
							SDL_RenderPresent(this->sdlr);

						}


						//this->menu.playSoundEffect("chime", false);
						if(enter){
						this->menu.playSoundEffect("eventCompletion", false);
						}
						this->taskManager.taskProgress=0;
						this->taskManager.taskOngoing=false;
						if(enter){
						this->player1.score+=(100*(10*60*1000-(SDL_GetTicks()-this->taskManager.taskTimer))/(10*60*1000))*this->player1.scoreMultiplier;
						}
						this->taskManager.tasksCompleted.push_back(this->taskManager.currentTask);
						this->taskManager.currentTexture=this->taskManager.tasks.at(0);
						this->taskManager.currentTask=0;
						if(this->taskManager.tasksCompleted.size()==this->taskManager.totalTasks){
							this->taskManager.currentTexture=this->taskManager.tasks.at(this->taskManager.totalTasks+1);
						}

					}
				}

			}
		}

	}
}
void Game::loadBank(){
	SDL_Surface *temp;
	string path="support/bank/Slide1.PNG";
	temp=IMG_Load(path.c_str());
	if(!temp) {
		cout<<"Error while loading bank surface!:"<<IMG_GetError()<<endl;
	}
	this->bank=SDL_CreateTextureFromSurface(sdlr,temp);
	SDL_FreeSurface(temp);

}
void Game::checkBank(){
	if(this->checkLandmarkIntersection("SBI",this->player1.dst)){
		SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(this->sdlr, 0,160,240, 100 );
		//SDL_RenderDrawRect(this->sdlr,&r );
		SDL_Rect r={200,WINDOW_HEIGHT-50,800,200};
		SDL_RenderFillRect( this->sdlr, &r );
		SDL_SetRenderDrawBlendMode(this->sdlr, SDL_BLENDMODE_NONE);
		SDL_Color colour;
		colour.a=255;
		colour.g=colour.b=colour.r=255;
		this->menu.write(this->sdlr,"Press 'e' to go inside the bank!",
				colour, 205, WINDOW_HEIGHT-50+10);
		const Uint8* ks = SDL_GetKeyboardState( NULL );
		if(ks[SDL_SCANCODE_E]||this->event.key.keysym.sym==SDLK_e){
			bool enter=true;
			while(enter){
				this->transfer();
				SDL_RenderCopy(sdlr,this->bank,NULL,NULL);

				while(SDL_PollEvent(&event)){
					const Uint8* ks = SDL_GetKeyboardState( NULL );
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_ESCAPE]||event.key.keysym.sym == SDLK_ESCAPE))){
						enter=false;
						//cout<<"EXITING"<<endl;
					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_D]||event.key.keysym.sym == SDLK_d))){
						if(this->moneyInBank>0){
							this->menu.playSoundEffect("buzzer", false);
						}
						else{
							bool b=true;
							string temp="";
							while(b){
								this->transfer();
								while(SDL_PollEvent(&event)){
									const Uint8* ks = SDL_GetKeyboardState( NULL );
									if(event.type==SDL_KEYDOWN){

										if(ks[SDL_SCANCODE_ESCAPE]||event.key.keysym.sym == SDLK_ESCAPE){
											if(temp==""){
												b=false;
											}
											else if(stoi(temp)<=this->player1.money){
													b=false;
												this->bankClock=SDL_GetTicks();
												this->menu.playSoundEffect("chime", false);
												this->player1.money-=stoi(temp);
												this->moneyInBank=stoi(temp);
											}
											else{
												SDL_Color col;
												col.a=255;
												col.r=col.b=col.g=255;
												this->menu.write(sdlr, "Insufficient Funds", col, 1100,90);
												this->menu.playSoundEffect("buzzer", false);
												//SDL_Delay(3*1000);

											}

										}

										else if(ks[SDL_SCANCODE_BACKSPACE]||event.key.keysym.sym == SDLK_BACKSPACE){
											if(temp.size()>0){
												temp.pop_back();
											}
										}

										else if(ks[SDL_SCANCODE_0]||event.key.keysym.sym == SDLK_0){
											temp+="0";
										}
										else if(ks[SDL_SCANCODE_1]||event.key.keysym.sym == SDLK_1){
											temp+="1";
										}
										else if(ks[SDL_SCANCODE_2]||event.key.keysym.sym == SDLK_2){
											temp+="2";
										}
										else if(ks[SDL_SCANCODE_3]||event.key.keysym.sym == SDLK_3){
											temp+="3";
										}
										else if(ks[SDL_SCANCODE_4]||event.key.keysym.sym == SDLK_4){
											temp+="4";
										}
										else if(ks[SDL_SCANCODE_5]||event.key.keysym.sym == SDLK_5){
											temp+="5";
										}
										else if(ks[SDL_SCANCODE_6]||event.key.keysym.sym == SDLK_6){
											temp+="6";
										}
										else if(ks[SDL_SCANCODE_7]||event.key.keysym.sym == SDLK_7){
											temp+="7";
										}
										else if(ks[SDL_SCANCODE_8]||event.key.keysym.sym == SDLK_8){
											temp+="8";
										}
										else if(ks[SDL_SCANCODE_9]||event.key.keysym.sym == SDLK_9){
											temp+="9";
										}

									}
								}
								//cout<<"Reached"<<endl;
								SDL_Rect x={100,300,800,200};
								SDL_SetRenderDrawBlendMode(sdlr, SDL_BLENDMODE_BLEND);
								SDL_SetRenderDrawColor(sdlr, 180,0, 255, 100);
								SDL_RenderFillRect( sdlr, &x );

								SDL_Color col;
								col.a=255;
								col.b=255;
								col.r=col.g=0;

								this->menu.write(sdlr, "Press 'Escape' key when done typing", col, 110,390);
								this->menu.write(sdlr, "Money Deposited: "+temp, col, 110,440);
								SDL_SetRenderDrawBlendMode(sdlr, SDL_BLENDMODE_NONE);
								SDL_RenderPresent(sdlr);

							}
						}



					}
					if((event.type==SDL_KEYDOWN &&(ks[SDL_SCANCODE_W]||event.key.keysym.sym == SDLK_w))){

						if(this->moneyInBank>0){
							this->menu.playSoundEffect("chime", false);
							int t=SDL_GetTicks()-this->bankClock;
							int interest=(t/(60*1000))*10*this->moneyInBank/100;
							this->player1.money+=this->moneyInBank+interest;
							this->bankClock=0;
							this->moneyInBank=0;
						}
						else{
							this->menu.playSoundEffect("buzzer",false);
						}
					}

				}
				string msg=this->player1.name+": HP = "+to_string(this->player1.hp)+"/"+to_string(this->player1.maxhp)+" Score = "+to_string(this->player1.score)+" Money: "+to_string(this->player1.money);
				SDL_Rect temp = { 0,0,370,30};
				SDL_SetRenderDrawColor( sdlr, 40, 60,160, 0xFF );
				SDL_Color c;
				c.r=c.b=0;
				c.g=c.a=255;
				SDL_RenderFillRect( sdlr, &temp );
				this->menu.write(this->sdlr,msg,c,4,0);
				string msg1="Money in Bank: "+to_string(this->moneyInBank);
				this->menu.write(this->sdlr,msg1,c,1100,5);
				SDL_RenderPresent(this->sdlr);
			}

		}

	}

}
void Game::endGame(){
	myTransferObject.gameOver=1;
	this->transfer();

	bool enter =true;
	this->reloadHighScore();
	if(this->player1.score>this->highscore){
		this->updateHighScore(this->player1.score);
	}
	while(enter){

		while(SDL_PollEvent(&event)){
			const Uint8* ks = SDL_GetKeyboardState( NULL );
			if(event.type==SDL_QUIT||(event.type==SDL_KEYDOWN && (ks[SDL_SCANCODE_ESCAPE]||event.key.keysym.sym == SDLK_ESCAPE))){
				enter=false;
				this->playing=false;
			}
			//if(transferObject.gameOver){
			//	SDL_RenderCopy(sdlr, this->menu.winscreen, NULL, NULL);
		//	}
	//		else{
				SDL_RenderCopy(sdlr, this->menu.texture5, NULL, NULL);

//			}
			string msg=this->player1.name+": HP = "+to_string(this->player1.hp)+"/"+to_string(this->player1.maxhp)+" Score = "+to_string(this->player1.score)+" Money: "+to_string(this->player1.money);
			SDL_Rect temp = { 0,0,370,30};
			SDL_SetRenderDrawColor( sdlr, 40, 60,160, 0xFF );
			SDL_Color c;
			c.r=c.b=0;
			c.g=c.a=255;
			SDL_RenderFillRect( sdlr, &temp );
			this->menu.write(this->sdlr,msg,c,4,0);
			SDL_RenderPresent(this->sdlr);
		}

	}
}
SDL_Rect Game::absoluteToRelative(SDL_Rect r){
	SDL_Rect t;
	int delx= this->player1.dst.x-this->player1.absoluteDst.x;
	int dely= this->player1.dst.y-this->player1.absoluteDst.y;
	t.x=r.x+delx;
	t.y=r.y+dely;
	t.w=r.w;
	t.h=r.h;
	return t;
}
void Game::vecToTranferObject(vector<int> v){
	//vector<int> v{score, money, hp, maxhp,onBike,sx,sy,sw,sh,dx,dy,dw,dh};
	this->transferObject.score=v[0];
	this->transferObject.money=v[1];
	this->transferObject.hp=v[2];
	this->transferObject.maxhp=v[3];
	if(v[4]==1){
		this->transferObject.onBike=true;
	}
	else{
		this->transferObject.onBike=false;
	}
	this->transferObject.src.x=v[5];
	this->transferObject.src.y=v[6];
	this->transferObject.src.w=v[7];
	this->transferObject.src.h=v[8];
	this->transferObject.dst.x=v[9];
	this->transferObject.dst.y=v[10];
	this->transferObject.dst.w=v[11];
	this->transferObject.dst.h=v[12];
	this->transferObject.gameOver=v[13];
	if(this->isServer){
		this->transferObject.connectionStrength=v[14];
		myTransferObject.connectionStrength=v[14];
	}

}
void Game::transfer(){
	if(transferObject.gameOver==0){
		vector<int> v;
		 if(this->isServer){
			//cout<<"Transfer Started"<<endl;
			//Server s;
			v=this->s.transferData(this->myTransferObject);

		 }
		 else{
			//Client c;
			v=this->c.transferData(this->myTransferObject,this->ip);
		 }
		 vecToTranferObject(v);
		 if(transferObject.gameOver==1){
			 cout<<"YOU WIN"<<endl;
		 }
	}
}
void Game::winGame(){
	   myTransferObject.gameOver=2;
		this->transfer();

		bool enter =true;
		this->reloadHighScore();
		if(this->player1.score>this->highscore){
			this->updateHighScore(this->player1.score);
		}
		while(enter){

			while(SDL_PollEvent(&event)){
				const Uint8* ks = SDL_GetKeyboardState( NULL );
				if(event.type==SDL_QUIT||(event.type==SDL_KEYDOWN && (ks[SDL_SCANCODE_ESCAPE]||event.key.keysym.sym == SDLK_ESCAPE))){
					enter=false;
					this->playing=false;
				}
				//if(transferObject.gameOver){
				//	SDL_RenderCopy(sdlr, this->menu.winscreen, NULL, NULL);
			//	}
		//		else{
					SDL_RenderCopy(sdlr, this->menu.winscreen, NULL, NULL);

	//			}
				string msg=this->player1.name+": HP = "+to_string(this->player1.hp)+"/"+to_string(this->player1.maxhp)+" Score = "+to_string(this->player1.score)+" Money: "+to_string(this->player1.money);
				SDL_Rect temp = { 0,0,370,30};
				SDL_SetRenderDrawColor( sdlr, 40, 60,160, 0xFF );
				SDL_Color c;
				c.r=c.b=0;
				c.g=c.a=255;
				SDL_RenderFillRect( sdlr, &temp );
				this->menu.write(this->sdlr,msg,c,4,0);
				SDL_RenderPresent(this->sdlr);
			}

		}
}

