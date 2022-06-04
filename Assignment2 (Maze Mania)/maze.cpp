/*
 * maze.cpp
 *
 *  Created on: 02-Apr-2022
 *      Author: shubham
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>
//#include <math.h>
//#include <vector>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "maze.h"
#include "tile.h"
using namespace std;

Maze::Maze(){

}
Maze::Maze(string mapfile){
	this->mapfile=mapfile;
}
Maze::~Maze(){
//	for (auto i=this->tiles.begin();i!=this->tiles.end();i++){
//			 i->second.~Tile();
//		 }
}
//int** Maze::getMaze(){
//	return &this->map;
//}
void Maze::readMaze(){
	fstream stream;
	stream.open(this->mapfile);
	string line;
	int j=0;
	int length=0;
	while(!stream.eof()){
		getline(stream,line);
		if(line[line.size()-1]==','){
			line.pop_back();
		}
	//	cout<<line.size();
		stringstream ss(line);
		int i=0;
		string temp;
		while(ss.good()){
		    getline( ss, temp, ',' );   //calling getline fuction
		    int tag=stoi(temp);
		    this->background[j][i]=tag;
//		    cout<<i<<" "<<j<<" "<<tag<<endl;
//		    if(i==0,j==0){
//		    	cout<<tag<<endl;
//		    }
//		    try{
		    length=this->tiles.at(tag).addDst(i*32,j*32,32,32);

		    this->checkLandmark(j,i);
//		    }
//		    catch(int tag){
//		    	cout<<tag<<endl;
//		    	exception e;
//		    	throw e;
//		    }
		    //cout<<"i: "<<i<<" j: "<<j<<endl;
		    i++;
		}
		j++;
//		for(int i=0;i<list.size();i++){
//			cout<<list[i]<<endl;
//		}
	}
	for(auto a=this->landmarks.begin();a!=this->landmarks.end();a++){
		SDL_Rect r;
		r.x=a->second.x;
		r.y=a->second.y;
		r.h=300;
		r.w=300;
		string name=a->first;
		if(name=="ARAVALI"){
			r.x-=100;
		}
		if(name=="VINDHYACHAL"){
			r.x-=250;
		}
		if(name=="NALANDA"){
			r.y-=150;
			r.x-=150;
		}
		if(name=="SATPURA"){
			r.x-=250;
		}
		if(name=="UDAIGIRI"){
			r.y-=150;
		}
		if(name=="ZANSKAR"){
			r.x-=250;
		}
		if(name=="SHIVALIK"){
			r.x-=250;
		}
		if(name=="SAC-AREA"){
			r.y-=250;
			r.x-=180;
		}
		if(name=="FOOTBALL"){
			r.y-=400;
			r.x-=180;
		}
		if(name=="LECTURE HALL COMPLEX"){
			r.y-=80;
			r.x-=200;
		}
		if(name=="SBI"){
			r.x-=200;
		}
		if(name=="BIOTECH LAWNS"){
			r.x-=200;
		}
		if(name=="CSC"){
			r.x-=200;
		}
		if(name=="CAFETERIA"){
			r.y-=150;
		}
		if(name=="YULU 1"){
			r.x-=150;
			r.y-=150;
		}
		if(name=="YULU 2"){
			r.x-=50;
			r.y-=200;
		}
		if(name=="YULU 3"){
			//r.x+=70;
			r.y-=70;
		}
		if(name=="YULU 4"){
			//r.x-=240;
			r.y-=100;
		}
		if(name=="DELHI-16"){
			r.x-=200;
			r.y-=200;
		}
		if(name=="MASALA MIX"){
			r.y-=200;
		}
		if(name=="HOSPITAL"){
			r.y-=50;
			r.x-=200;
		}
		if(name=="HIMADRI"){
			r.x-=200;
		}
		if(name=="KAILASH"){
			r.x-=300;
			r.y-=300;
		}
		if(name=="HAIR SALON"){
			r.y-=150;
		}

		this->landmarkBoxes.insert({name,r});
	}

}
void Maze::addTile(Tile tile){
	//cout<<3;
	this->tiles.insert({tile.getId(),tile});
	//cout<<6;
}
void Maze::scroll(int vx,int vy){
	 for (auto i=this->tiles.begin();i!=this->tiles.end();i++){
		 Tile t=i->second;
		 vector<SDL_Rect> dsts=t.getDsts();
		 for(int j=0;j<dsts.size();j++){
			 dsts[j].x+=vx;
			 dsts[j].y+=vy;
		 }
		 t.dsts=dsts;
		 i->second=t;
	 }
	 for(auto j=this->landmarks.begin();j!=this->landmarks.end();j++){
		 SDL_Rect r=j->second;
		 r.x+=vx;
		 r.y+=vy;
		 j->second=r;
	 }
	 for(auto j=this->landmarkBoxes.begin();j!=this->landmarkBoxes.end();j++){
		 SDL_Rect r=j->second;
		 r.x+=vx;
		 r.y+=vy;
		 j->second=r;
	 }

}
void Maze::render(SDL_Renderer* sdlr){
	 for (auto i=this->tiles.begin();i!=this->tiles.end();i++){
		 Tile t=i->second;
		 vector<SDL_Rect> dsts=t.getDsts();

		 for(int j=0;j<dsts.size();j++){
			SDL_Rect r=dsts[j];
			if(r.x>=-62 & r.y>=-64 & r.x<=1280+32 & r.y<=800+32){
			t.drawTile(sdlr,&dsts[j]);
			}
		 }
	 }


}
void Maze::checkLandmark(int r, int c){
	SDL_Rect dst;
	dst.x=(c-1)*32;
	dst.y=(r-1)*32;
	dst.w=128;
	dst.h=128;

	if(r==19 & c==27){
//		this->buildingLandmarks.insert({"Jwala",length});
		dst.w=164;
		this->landmarks.insert({"JWALAMUKHI",dst});
//		cout<<"Inserted: "<<to_string(length)<<endl;
	}
	if(r==70 & c==30){
		this->landmarks.insert({"ARAVALI",dst});
	}
	if(r==100 & c==29){
		this->landmarks.insert({"KARAKORAM",dst});
	}
	if(r==121 & c==27){
		this->landmarks.insert({"NILGIRI",dst});
	}
	if(r==15 & c==68){
		this->landmarks.insert({"KUMAON",dst});
	}
	if(r==8 & c==105){
		this->landmarks.insert({"VINDHYACHAL",dst});
	}
	if(r==98 & c==55){
		this->landmarks.insert({"NALANDA",dst});
	}
	if(r==12 & c==120){
		this->landmarks.insert({"SATPURA",dst});
	}
	if(r==15 & c==155){
		this->landmarks.insert({"UDAIGIRI",dst});
	}
	if(r==22 & c==155){
		this->landmarks.insert({"GIRNAR",dst});
	}
	if(r==85 & c==88){
		this->landmarks.insert({"ZANSKAR",dst});
	}
	if(r==65 & c==88){
		this->landmarks.insert({"SHIVALIK",dst});
	}
	if(r==98 & c==115){
		this->landmarks.insert({"SAC-AREA",dst});
	}
	if(r==100 & c==125){
		dst.w=164;
		this->landmarks.insert({"SWIMMING-POOL",dst});

	}
	if(r==125 & c==122){
		this->landmarks.insert({"OAT",dst});
	}
	if(r==86 & c==153){
		this->landmarks.insert({"HOSPITAL",dst});
	}
	if(r==102 & c==160){
		this->landmarks.insert({"FOOTBALL",dst});
	}
	if(r==107 & c==185){
		this->landmarks.insert({"ATHLETICS",dst});
	}
	if(r==107 & c==170){
		this->landmarks.insert({"CRICKET",dst});
	}
	if(r==107 & c==220){
		this->landmarks.insert({"HOCKEY",dst});
	}
	if(r==97 & c==170){
		this->landmarks.insert({"BASKETBALL",dst});
	}
	if(r==97 & c==287){
		dst.w=248;
		this->landmarks.insert({"LECTURE HALL COMPLEX",dst});
	}
	if(r==85 & c==288){
		this->landmarks.insert({"SBI",dst});
	}
	if(r==77 & c==287){
		dst.w=248;
		this->landmarks.insert({"TEXTILE DEPARTMENT",dst});
	}
	if(r==52 & c==265){
		dst.w=248;
		this->landmarks.insert({"BIOTECH LAWNS",dst});
	}
	if(r==84 & c==226){
		this->landmarks.insert({"LIBRARY",dst});
	}
	if(r==74 & c==236){
		this->landmarks.insert({"CSC",dst});
	}
	if(r==73 & c==187){
		this->landmarks.insert({"KHOSLA",dst});
	}
	if(r==81 & c==192){
		this->landmarks.insert({"BHARTI",dst});
	}
	if(r==134 & c==205){
		this->landmarks.insert({"CAFETERIA",dst});
	}
	if(r==14 & c==37){
		dst.w=80;
		dst.h=80;
		this->landmarks.insert({"YULU 1",dst});
	}
	if(r==70 & c==45){
		this->landmarks.insert({"DELHI-16",dst});
	}
	if(r==84 & c==125){
		dst.w=200;
		this->landmarks.insert({"MASALA MIX",dst});
	}
	if(r==98 & c==100){
		dst.w=dst.h=64;
		this->landmarks.insert({"YULU 2",dst});
	}
	if(r==42 & c==295){
		dst.w=248;
		this->landmarks.insert({"HIMADRI CIRCLE",dst});
	}
	if(r==22 & c==322){
		this->landmarks.insert({"KAILASH",dst});
	}
	if(r==8 & c==328){
		this->landmarks.insert({"HIMADRI",dst});
	}
//	if(r==54 & c==226){
//		this->landmarks.insert({"BLOCKS",dst});
//	}
	if(r==38 & c==252){
		this->landmarks.insert({"BLOCK 1",dst});
	}
	if(r==55 & c==224){
		this->landmarks.insert({"BLOCK 2",dst});
	}
	if(r==50 & c==216){
		this->landmarks.insert({"BLOCK 3",dst});
	}
	if(r==46 & c==210){
		this->landmarks.insert({"BLOCK 4",dst});
	}
	if(r==43 & c==205){
		this->landmarks.insert({"BLOCK 5",dst});
	}
	if(r==41 & c==200){
		this->landmarks.insert({"BLOCK 6",dst});
	}
	if(r==186 & c==31){
		dst.w=248;
		this->landmarks.insert({"INSPECTOR GADGET",dst});
	}
	if(r==28 & c==365){
		dst.w=168;
		this->landmarks.insert({"GUEST HOUSE",dst});
	}
	if(r==134 & c==274){
		this->landmarks.insert({"HAIR SALON",dst});
	}
	if(r==130 & c==32){
		this->landmarks.insert({"YULU 3",dst});
	}
	if(r==89 & c==259){
//		dst.w=248;
		this->landmarks.insert({"YULU 4",dst});
	}
}
SDL_Rect Maze::getLandmarkDest(string name){
	SDL_Rect r;
	r=this->landmarks.at(name);
	return r;

//	cout<<r.x<<" "<<r.y<<" :Jwala"<<endl;
//	int index;
//
//	if(type.compare("building")==0){
//		index=this->buildingLandmarks.at(name);
//	}
//	else if(type.compare("road")==0){
//		index=this->roadLandmarks.at(name);
//	}
//	else if(type.compare("grass")==0){
//		index=this->grassLandmarks.at(name);
//	}
//	else if(type.compare("water")==0){
//		index=this->waterLandmarks.at(name);
//	}
//	else if(type.compare("terrain")==0){
//		index=this->terrainLandmarks.at(name);
//	}


//	vector<SDL_Rect> dsts=this->tiles.at(this->tidMap.at(type)).getDsts();
//	r=dsts[index];
//	cout<<"Jwala "<<dsts[index].x<<" "<<r.x<<endl;


}

