#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "transferobject.h"
#define PORT 8080
using namespace std;

class Client{
	public:
	int badCount=0;
	int totalCount=0;
	int badPercent=0; //bad/total*100;
	vector<int> transferIntData(vector<int>s,string ip);
	string transferStringData(string s,string ip);
	vector<int> transferData(TransferObject t,string ip);
	
	
	//void sendData();
      //  void receiveData();
      
};   
