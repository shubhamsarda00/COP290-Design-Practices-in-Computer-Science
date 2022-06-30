
// Server side C/C++ program to demonstrate Socket
// programming
#include "server.h"


//  void Server::receiveData()
//  {

// char buffer[1024] = { 0 };
//    // char hello[32] = "Hello motherfucker!!!!!!!!!!!!\n";
    
//     int a=socket(AF_INET,SOCK_STREAM,0);
//     if(a<0)
//     {
//         cout<<"Socket making for server is failed\n";
//     }
//     else
//     cout<<"Step 1 done succesfully\n";

// //step 
// int opt = 1;
// if (setsockopt(a, SOL_SOCKET,
//                    SO_REUSEADDR | SO_REUSEPORT, &opt,
//                    sizeof(opt))) {
//         perror("setsockopt");
//         exit(EXIT_FAILURE);
//     }

// cout<<"Step 2 done succesfully\n";

// struct sockaddr_in adress;

//    int adrlen = sizeof(adress);
//    adress.sin_family = AF_INET;
//     adress.sin_addr.s_addr = INADDR_ANY;
//     adress.sin_port = htons(PORT);

//     if (bind(a, (struct sockaddr*)&adress,
//              sizeof(adress))
//         < 0) {
//         perror("bind failed");
//         exit(EXIT_FAILURE);
//     }

// cout<<"Binding passed now its time for fourth step\n";
 

// //int input[5]={1,2,3,4,5};


//     int read[5];
    
    
//     int count=0;
//     int i=0;
//     int j=0;
    
//     while(count<=4)
    
//    { 
   

//  if (listen(a ,2) < 0) {
//         perror("listen");
//         exit(EXIT_FAILURE);
//     }

// cout<<"Waiting for the clients to join...........................\n";
// int new_socket= accept(a, (struct sockaddr*)&adress,
//                   (socklen_t*)&adrlen);

//    while(new_socket<0)
//          {
        
//         cout<<"Cant able to connect try again\n";
//     }

// if(new_socket>0)
// {
//      // send(new_socket,"You are succesfully connected to server\n", strlen(hello), 0);
//     //  send(new_socket,(void*)(a+i),sizeof(int), 0);
//      // send(new_socket,(void*)hello,32,0);
// }

//  int valread = recv(new_socket, buffer, 1024,0);

//    read[j]=*((int*)buffer);
//    printf("%d\n",read[j]);
//    count++;
//    i++;
//    j++;
   
//    }


//  }

 
 
//  void Server::sendData(){



//    // char hello[32] = "Hello motherfucker!!!!!!!!!!!!\n";
//     int input[5]={1,2,3,4,5};


//     int read[5]={0,0,0,0,0};
    
    
//     int count=0;
//     int i=0;
//     int j=0;
    
//     while(count<=4)
    
//    { 

//  void* buffer;
   
//     int a=socket(AF_INET,SOCK_STREAM,0);
//     if(a<0)
//     {
//         cout<<"Socket making for server is failed\n";
//     }
//     else
//     cout<<"Step 1 done succesfully\n";

// //step 
// int opt = 1;
// if (setsockopt(a, SOL_SOCKET,
//                    SO_REUSEADDR | SO_REUSEPORT, &opt,
//                    sizeof(opt))) {
//         perror("setsockopt");
//         exit(EXIT_FAILURE);
//     }

// cout<<"Step 2 done succesfully\n";

// struct sockaddr_in adress;

//    int adrlen = sizeof(adress);
//    adress.sin_family = AF_INET;
//     adress.sin_addr.s_addr = INADDR_ANY;
//     adress.sin_port = htons(PORT);

//     if (bind(a, (struct sockaddr*)&adress,
//              sizeof(adress))
//         < 0) {
//         perror("bind failed");
//         exit(EXIT_FAILURE);
//     }

// cout<<"Binding passed now its time for fourth step\n";
 



//  if (listen(a ,2) < 0) {
//         perror("listen");
//         exit(EXIT_FAILURE);
//     }

// cout<<"Waiting for the clients to join...........................\n";
// int new_socket= accept(a, (struct sockaddr*)&adress,
//                   (socklen_t*)&adrlen);

//    while(new_socket<0)
//          {
        
//         cout<<"Cant able to connect try again\n";
//     }

// if(new_socket>0)
// {
//      // send(new_socket,"You are succesfully connected to server\n", strlen(hello), 0);
//       send(new_socket,(void*)(input+i),sizeof(int), 0);
//      // send(new_socket,(void*)hello,32,0);
// }

//  //int valread = recv(new_socket, buffer, 1024,0);

//    read[j]=*((int*)buffer);
//    count++;
//    i++;
//    j++;
   
//    }




//  /* if (listen(a ,2) < 0) {
//         perror("listen");
//         exit(EXIT_FAILURE);
//     }

// cout<<"Waiting for the clients to join...........................\n";
// int new_socket= accept(a, (struct sockaddr*)&adress,
//                   (socklen_t*)&adrlen);

//    while(new_socket<0)
//          {
        
//         cout<<"Cant able to connect try again\n";
//     }

// if(new_socket>0)
// {
//      // send(new_socket,"You are succesfully connected to server\n", strlen(hello), 0);
//       send(new_socket,(void*)hello,32,0);
// }

//  int valread = read(new_socket, buffer, 1024);
//  //printf("%s",buffe

// }


//  */

//  }
string Server::transferStringData(string s){
int count=0;
char *hello = new char[s.length() + 1];
	strcpy(hello, s.c_str());
//char* hello="Hi\n";
//  char *adress2=(char*)malloc(s.length()*sizeof(char)+1);
    const void *adr=hello;

 void *buffer=malloc(7);

    int a=socket(AF_INET,SOCK_STREAM,0);
    if(a<0)
    {
       // cout<<"Socket making for server is failed\n";
    }
    else{}
    //cout<<"Step 1 done succesfully\n";

//step 
int opt = 1;
if (setsockopt(a, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

//cout<<"Step 2 done succesfully\n";

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

//cout<<"Binding passed now its time for fourth step\n";

 if (listen(a ,2) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

//cout<<"Waiting for the clients to join...........................\n";
int new_socket= accept(a, (struct sockaddr*)&adress,
                  (socklen_t*)&adrlen);

   while(new_socket<0)
         {
        
      //  cout<<"Cant able to connect try again\n";
    }

if(new_socket>0)
{
     // send(new_socket,"You are succesfully connected to server\n", strlen(hello), 0);
      send(new_socket,hello,strlen(hello)+1,0);
}

 int valread = read(new_socket, buffer,7);
// printf("%s\n",buffer);
 close(new_socket);
close(a);
char*buffer2=(char*)buffer;

string s1(buffer2);
return s1;

}






vector<int> Server::transferIntData(vector<int> input){
    int count=0;
//	vector<int> input;
//	input.push_back(x);
//	input.push_back(y);
	
//char* hello=s.c_str();

 int *adress2=(int*)malloc(sizeof(int)*input.size());
for(int i=0;i<input.size();i++)
{
  adress2[i]=input[i];
 // printf("%d\n",adress[i]);
}
 
 //char buffer[1024] = { 0 };


int *add=(int*)malloc(sizeof(int)*input.size());

//for(int i=0;i<input.size();i++)
//{
 // add[i]=input[i];
 // printf("%d\n",add[i]);
//}
//
 void* add2=(void*)add;

   const void* adr=(void*)adress2;




    int a=socket(AF_INET,SOCK_STREAM,0);
    if(a<0)
    {
     //   cout<<"Socket making for server is failed\n";
    }
    else{}
    //cout<<"Step 1 done succesfully\n";

//step 
int opt = 1;
if (setsockopt(a, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

//cout<<"Step 2 done succesfully\n";

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

//cout<<"Binding passed now its time for fourth step\n";
// while(count<v.size()){
 if (listen(a ,2) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

//cout<<"Waiting for the clients to join...........................\n";
int new_socket= accept(a, (struct sockaddr*)&adress,
                  (socklen_t*)&adrlen);

   while(new_socket<0)
         {
        
      //  cout<<"Cant able to connect try again\n";
    }
//int l=80;
if(new_socket>0)
{	//int temp=v[count];
     // send(new_socket,"You are succesfully connected to server\n", strlen(hello), 0);
      send(new_socket,adr,sizeof(int)*input.size(),0);
}

 int valread = read(new_socket,add2, 1024);


vector<int>out;
for(int i=0;i<input.size();i++)
{
   out.push_back(*((int*)add2+i));
  // cout<<out[i]<<endl;
}

close(new_socket);

close(a);
return out;

//count++;
//}
}





vector<int> Server::transferData(TransferObject t){

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
	vector<int> v{score, money,hp, maxhp,onBike,sx,sy,sw,sh,dx,dy,dw,dh,gameOver,connectionStrength};
	return this->transferIntData(v);
	//this->transferStringData(s);
	
	
}	
	
	

