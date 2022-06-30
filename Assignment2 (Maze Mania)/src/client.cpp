// programming

#include "client.h"
#include <math.h>


string Client ::transferStringData(string s,string ip)
{
 
  int sock = 0, valread;

  
      struct sockaddr_in serv_addr;
    char* hello =new char[s.length()+1];
   // char *adress2=(char*)malloc(s.length()*sizeof(char)+1);
    const void *adr=hello;

   strcpy(hello,s.c_str());
   void *buffer=malloc(7);
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
       // printf("\n Socket creation error \n");
       
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
 
    // Convert IPv4 and IPv6 addresses from text to binary
    // form

  
    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr)
        <= 0) {
       // printf(
         //   "\nInvalid address/ Address not supported \n");
        
    }
 
    
    while(true){   
     if (connect(sock, (struct sockaddr*)&serv_addr,
                sizeof(serv_addr))
        < 0) {
        //printf("\nConnection Failed \n");
       

    }
    else{
      break;
    }
    }
    send(sock,hello,s.length()+1, 0);

   // printf("Hello message sent\n");
  
   valread = read(sock, buffer,7);
    
char*buffer2=(char*)buffer;

close(sock);
string s1(buffer2);
return s1;



}



// struct read
// {
//   int a;
//   int b;
//   int c;
//   int d;
//  int e;
// };


// void Client::receiveData(){    
//    int a[5]={1,2,3,4,5};
// int b;
// int c;
// int d;
// int e;

//     int read[5];
    
    
//     int count=0;
//     int i=0;
//     int j=0;
   
   
  
   
//     while(count<=4){ 
//     int sock = 0, valread;
//     struct sockaddr_in serv_addr;
//     char* hello = "Hello from client";
//     char buffer[1024]={0};
//     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//         printf("\n Socket creation error \n");
    
//     }
//     cout<<"created Socket"<<endl;
 
//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_port = htons(PORT);
 
//     // Convert IPv4 and IPv6 addresses from text to binary
//     // form
//     if (inet_pton(AF_INET, "192.168.16.3", &serv_addr.sin_addr)
//         <= 0) {
//         printf(
//             "\nInvalid address/ Address not supported \n");
    
//     }
    

// //int a int b int c int d int e

    
//     if (connect(sock, (struct sockaddr*)&serv_addr,
//                 sizeof(serv_addr))
//         < 0) {
//         printf("\nConnection Failed \n");
//     }
//     cout<<"Connection Successfull"<<endl;
//     //send(sock,(void*)(a+i),sizeof(int), 0);
    
//     valread = recv(sock, buffer, 1024,0);
//     printf("%d\n",valread);
//     read[j]=*((int*)buffer);
//    printf("%d\n",read[j]);
//    count++;
//    i++;
//    j++;
   
//    }
   
   
//    }


// void Client::sendData()
//    {


//   int input[5]={1,2,3,4,5};
// int b;
// int c;
// int d;
// int e;

//     int read[5];
    
    
//     int count=0;
//     int i=0;
//     int j=0;
    

//       while(count<=4)
//       {
//     int sock = 0, valread;
//     struct sockaddr_in serv_addr;
//     char* hello = "Hello from client";
//     void* buffer;
//     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//         printf("\n Socket creation error \n");
    
//     }
 
//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_port = htons(PORT);
 
//     // Convert IPv4 and IPv6 addresses from text to binary
//     // form
//     if (inet_pton(AF_INET, "192.168.16.3", &serv_addr.sin_addr)
//         <= 0) {
//         printf(
//             "\nInvalid address/ Address not supported \n");
    
//     }

// //int a int b int c int d int e

  
    
//    if (connect(sock, (struct sockaddr*)&serv_addr,
//                 sizeof(serv_addr))
//         < 0) {
//         printf("\nConnection Failed \n");
//     }
//     send(sock,(void*)&(input[count]),sizeof(int), 0);
//     printf("Hello message sent\n");
//    // valread = recv(sock, buffer, 1024,0);
    
//     read[j]=*((int*)buffer);
   
//    count++;
//  //  i++;
//    j++;
   

//    }
   
 


//    }
vector<int> Client::transferIntData(vector<int>input,string ip){
	totalCount++;
    int count=0;
 //   vector<int>input;
   // input.push_back(x);
   // input.push_back(y);
    
int *adress=(int*)malloc(sizeof(int)*input.size());
for(int i=0;i<input.size();i++)
{
  adress[i]=input[i];
 // printf("%d\n",adress[i]);
}

int *add=(int*)malloc(sizeof(int)*input.size());
for(int i=0;i<input.size();i++)
{
  add[i]=input[i];
  //printf("%d\n",add[i]);
}

 void* add2=(void*)add;

   const void* adr=(void*)adress;

   int sock = 0, valread;

   //    //  while(count<input.size())
  //  {
      struct sockaddr_in serv_addr;
 //   char* hello =new char[s.length()+1];
   //strcpy(hello,s.c_str());
    char buffer[input.size()] = { 0 };
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
       // printf("\n Socket creation error \n");
       
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
 
    // Convert IPv4 and IPv6 addresses from text to binary
    // form

  
    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr)
        <= 0) {
       // printf(
         //   "\nInvalid address/ Address not supported \n");
        
    }
 
    
   
    while(true){   
     if (connect(sock, (struct sockaddr*)&serv_addr,
                sizeof(serv_addr))
        < 0) {
      //  printf("\nConnection Failed \n");
    	 badCount++;
    	 totalCount++;
       
    }
    else{
      break;
    }
    }
      int l=7888;
    send(sock,adr,sizeof(int)*input.size(), 0);

   // printf("Hello message sent\n");
  
   valread = read(sock, add2, sizeof(int)*input.size());
    

  
//count++;


vector<int>out;

for(int i=0;i<input.size();i++)
{
  out.push_back(*((int*)add2+i));
  //cout<<out[i]<<endl;
  
   //printf("%d\n",*((int*)add2+i));
}

badPercent=ceil((100*badCount)/totalCount);

close(sock);
return out;
//    }
}


vector<int> Client::transferData(TransferObject t,string ip)
{
string s=t.name;
int score=t.score;
int money=t.money;
int gameOver=t.gameOver;
int hp=t.hp;
int maxhp=t.maxhp;
int onBike=int(t.onBike);
int sx=t.src.x;
int sy=t.src.y;
int sw=t.src.w;
int sh=t.src.h;

int dx=t.dst.x;
int dy=t.dst.y;
int dw=t.dst.w;
int dh=t.dst.h;
int connectionStrength=t.connectionStrength;
totalCount++;
badPercent=badCount*100.0/totalCount;
//cout<<"Connectivity Strength: "<<to_string(100-badPercent)<<endl;
vector<int> v{score,money,hp,maxhp,onBike,sx,sy,sw,sh,dx,dy,dw,dh,gameOver,connectionStrength};
return this->transferIntData(v,ip);
//this->transferStringData(s);

}











