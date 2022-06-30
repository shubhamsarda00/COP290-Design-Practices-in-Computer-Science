#include <math.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
#include "libaudio.h"
//#include <chrono>
using namespace std;

void output(string inputfile,string outputfile,pred_t* pred){
	ofstream stream(outputfile,ios_base::app);
	stream<<inputfile<<" ";
	vector<string> labels={"silence", "unknown", "yes", "no", "up", "down", "left", "right", "on", "off", "stop", "go"};
	for(int i=0;i<3;i++){
		cout<<"Word: "<<labels[pred[i].label]<<" Probability: "<<pred[i].prob<<endl;
		stream<<labels[pred[i].label]<<" ";
	}
	for(int i=0;i<3;i++){
		//cout<<"Word: "<<labels[pred[i].label]<<" Probability: "<<pred[i].prob<<endl;
		if(i==2){
			stream<<pred[i].prob<<endl;
			continue;
		}
		stream<<pred[i].prob<<" ";
	}

	stream.close();
}

int main(int argc, char **argv) {

		//Checking if number of arguments are correct
	if(argc<3){
		cout<<"Only "<<argc<<" command line arguments have been provided (including executable name). 3"
				" are required for correct functioning.\nSample cmd line arguments:"
				" './yourcode.out audiosample outputfile'"
				" \n\n";
		return 0;
	}
	const char* inputfile=argv[1];
	pred_t* pred;
	string outputfile=argv[2];
//	auto start_time = chrono::high_resolution_clock::now();
	pred=libaudioAPI(inputfile,pred);
//	auto end_time = chrono::high_resolution_clock::now();
//	auto elapsed_time =chrono::duration_cast<chrono::microseconds>(end_time - start_time);
//	cout<<"TIME: "<<elapsed_time.count()<<endl;
	output(argv[1],outputfile,pred);
	return 0;
}





