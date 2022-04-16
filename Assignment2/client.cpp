// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
  #include <arpa/inet.h>
#include <unistd.h>
#include "transferobject.h"
#include <SDL2/SDL.h>
#define PORT 8080
using namespace std;

int main(int argc, char const* argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[1024] = { 0 };
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
//    TransferObject t;
//    SDL_Rect r={0,0,12,12};
//    t.dst=r;
//    t.name="shubham";
//    t.hp=100;
//    t.score=20;
//    t.maxhp=100;
//    void* transfer=(void*)&t;
//    int size=sizeof(t);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if (connect(sock, (struct sockaddr*)&serv_addr,
                sizeof(serv_addr))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sock, buffer, 1024);
    
    printf("%d\n", *((int*)buffer));
    return 0;
}



























