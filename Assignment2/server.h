#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include "transferobject.h"
#define PORT 8080
using namespace std;
class Server{
	public:
	//	void sendData();
        //void receiveData();
        vector<int> transferIntData(vector<int> v);
        string transferStringData(string s);
        vector<int> transferData(TransferObject t);
};       
