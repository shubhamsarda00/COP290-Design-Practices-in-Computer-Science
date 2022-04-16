
// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include "transferobject.h"
#include <SDL2/SDL.h>
#define PORT 8080
using namespace std;
int main()
{
 char buffer[1024] = { 0 };
    char hello[32] = "Hello motherfucker!!!!!!!!!!!!\n";
    
    int a=socket(AF_INET,SOCK_STREAM,0);
    if(a<0)
    {
        cout<<"Socket making for server is failed\n";
    }
    else
    cout<<"Step 1 done succesfully\n";

//step 
int opt = 1;
if (setsockopt(a, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

cout<<"Step 2 done succesfully\n";
	TransferObject t;
    SDL_Rect r={0,0,12,12};
    t.dst=r;
    t.name="shubham";
    t.hp=100;
    t.score=20;
    t.maxhp=100;
    void* transfer=(void*)&t;
    int size=sizeof(t);
struct sockaddr_in adress;

   int adrlen = sizeof(adress);
   adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = INADDR_ANY;
    adress.sin_port = htons(PORT);

    if (bind(a, (struct sockaddr*)&adress,
             sizeof(adress))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

cout<<"Binding passed now its time for fourth step\n";
 
 if (listen(a ,2) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

cout<<"Waiting for the clients to join...........................\n";
int new_socket= accept(a, (struct sockaddr*)&adress,
                  (socklen_t*)&adrlen);

   while(new_socket<0)
         {
        
        cout<<"Cant able to connect try again\n";
    }
int l=68;
if(new_socket>0)
{
     // send(new_socket,"You are succesfully connected to server\n", strlen(hello), 0);
      send(new_socket,(void*)&l,sizeof(l),0);
}

 int valread = read(new_socket, buffer, 1024);
 printf("%s",buffer);

return 0;








}
