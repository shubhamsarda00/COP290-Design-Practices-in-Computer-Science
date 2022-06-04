/*
 * a1task2_naive.cpp
 *
 *  Created on: 12-Feb-2022
 *      Author: shubham
 */
#include <math.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
#include <chrono>
using namespace std;


// Function for reading a matrix from an input file
vector<vector<float>> read_matrix(string file){
	fstream stream;
	try {
		stream.open(file);
		//Catching error if input file is not present
		if(stream.fail()){
			throw file;
		}
	}
	catch(string& s){
		cout<<"File with the name '"<<s<< "' doesn't exist."<<"\n\n";
		exception e;
		throw e;
		//exit(0);
	}
	string line;
	getline(stream,line);
	int c=stoi(line);
	getline(stream,line);
	int r=stoi(line);
	vector<vector<float>> matrix( r , vector<float> (c));
	for(int i=0;i<c;i++){
		for(int j=0;j<r;j++){
			getline(stream,line);
			matrix[j][i]=stof(line);
		}
	}

	return matrix;
}

//Function for writing a matrix to an output file
void write_matrix(string file, vector<vector<float>> matrix){
	ofstream stream(file);
	int c=matrix[0].size();
	int r=matrix.size();
	stream<<c<<'\n';
	stream<<r<<'\n';

	for(int i=0;i<c;i++){
		for(int j=0;j<r;j++){
			stream<<matrix[j][i]<<'\n';
		}
	}
	stream.close();
}

//Function for writing a vector to an output file
void write_vector(string file, vector<float> vec){
	ofstream stream(file);
	int n=vec.size();
	stream<<n<<'\n';

	for(int i=0;i<n;i++){
		stream<<vec[i]<<'\n';
	}
	stream.close();
}

//Function for printing a matrix on the console in a readable manner
void print_matrix(vector<vector<float>> m){
	for(int i=0;i<m.size();i++){
			for(int j=0;j<m[0].size();j++){
				cout<<m[i][j]<<" ";
				}
			cout<<'\n';
			}
}

//Function for printing a vector on the console in a readable manner
void print_vector(vector<float> v){
	for(int i=0;i<v.size();i++){
		cout<<v[i]<<" ";
	}
}

// Function for reading a vector from an input file
vector<float> read_vector(string file){
	fstream stream;
	try {
			stream.open(file);
			//Catching error if input file is not present
			if(stream.fail()){
				throw file;
			}
		}
		catch(string& s){
			cout<<"File with the name '"<<s<< "' doesn't exist."<<"\n\n";
			exception e;
			throw e;
			//exit(0);
		}
	string line;
	getline(stream,line);
	int n=stoi(line);
	vector<float> vec(n);
	for(int i=0;i<n;i++){
		getline(stream,line);
		vec[i]=stof(line);
	}

	return vec;
}

// Function for adding two matrices
vector<vector<float>> add_matrix(vector<vector<float>> a, vector<vector<float>> b){
	vector<vector<float>> c(a.size() , vector<float> (a[0].size()));
	for(int i=0;i<a.size();i++){
		for(int j=0;j<a[0].size();j++){
			c[i][j]=a[i][j]+b[i][j];
		}
	}
	return c;
}


// Function for multiplying two matrices
vector<vector<float>> mul_matrix(vector<vector<float>> a, vector<vector<float>> b){
	vector<vector<float>> c(a.size() , vector<float> (b[0].size()));
	for(int i=0;i<a.size();i++){
		for(int j=0;j<b[0].size();j++){
			float x=0;
			for(int k=0;k<b.size();k++){
				x+=a[i][k]*b[k][j];
			}
			c[i][j]=x;
		}
	}
	return c;
}

//Function to find tanh output of a single float
float tanh_float(float a){
	float s = expf(2*a);

	float x=(s-1)/(s+1);
	return x;
}
//Helper Function for sigmoid
float sigmoid_float(float a){
	float s = expf(-a);

	float x=(1.)/(s+1);
	return x;
}

//Function to find relu output of a single float
float relu_float(float a){
	if (a>0){
		return a;
	}
	return 0;
}

//Function for average pooling of an input matrix with given stride
vector<vector<float>> average_pool(string input,int stride){
	vector<vector<float>> i=read_matrix(input);
	//Printing Error Message when stride doesn't divide input matrix dimensions
	if(i.size()%stride!=0 || i[0].size()%stride!=0){
		cout<<"Stride of pooling("<<stride<<") isn't a divisor of input matrix"
				" dimensions("<<i.size()<<","<<i[0].size()<<")\n\n";
		exception e;
		throw e;
	}

	vector<vector<float>> output(i.size()/stride , vector<float> (i[0].size()/stride));
	for(int r=0;r<i.size()/stride;r++){
		for(int c=0;c<i[0].size()/stride;c++){
			float x=0;
			for(int k=0;k<stride;k++){
				for(int l=0;l<stride;l++){
					x+=i[r*stride+k][c*stride+l];
				}
			}
			output[r][c]=x/(stride*stride);
		}
	}
	return output;
}

//Function for max pooling of an input matrix with given stride
vector<vector<float>> max_pool(string input,int stride){
	vector<vector<float>> i=read_matrix(input);

	//Printing Error Message when stride doesn't divide input matrix dimensions
	if(i.size()%stride!=0 || i[0].size()%stride!=0){
		cout<<"Stride of pooling("<<stride<<") isn't a divisor of input matrix"
				" dimensions("<<i.size()<<","<<i[0].size()<<")\n\n";
		exception e;
		throw e;
	}
	vector<vector<float>> output(i.size()/stride , vector<float> (i[0].size()/stride));
	for(int r=0;r<i.size()/stride;r++){
		for(int c=0;c<i[0].size()/stride;c++){
			float x=i[r*stride+0][c*stride+0];
			for(int k=0;k<stride;k++){
				for(int l=0;l<stride;l++){
					if(x<i[r*stride+k][c*stride+l]){
						x=i[r*stride+k][c*stride+l];
					}
				}
			}
			output[r][c]=x;
		}
	}
	return output;
}

// Function to output sigmoid probability, given an input vector file
vector<float> sigmoid(string file){
	vector<float> vec=read_vector(file);
//	print_vector(vec);
	for(int i=0;i<vec.size();i++){
		vec[i]=sigmoid_float(vec[i]);
	}
	return vec;
}

// Function to output softmax probability, given an input vector file
vector<float> softmax(string file){
	vector<float> vec=read_vector(file);
	float s=0;
	for(int i=0;i<vec.size();i++){
		vec[i]=expf(vec[i]);
		s+=vec[i];
	}
	for(int i=0;i<vec.size();i++){
			vec[i]/=s;
		}
	return vec;
}

// Function to compute tanh activation output, given an input matrix file
vector<vector<float>> tanh(string input){
	vector<vector<float>> i=read_matrix(input);
	vector<vector<float>> output(i.size() , vector<float> (i[0].size()));
	for(int r=0;r<i.size();r++){
		for(int c=0;c<i[0].size();c++){
			output[r][c]=tanh_float(i[r][c]);
		}
	}
	return output;
}

// Function to compute relu activation output, given an input matrix file
vector<vector<float>> relu(string input){
	vector<vector<float>> i=read_matrix(input);
	vector<vector<float>> output(i.size() , vector<float> (i[0].size()));
	for(int r=0;r<i.size();r++){
		for(int c=0;c<i[0].size();c++){
			output[r][c]=relu_float(i[r][c]);
		}
	}
	return output;
}

// Function to compute fully connected layer output: Input*Weight+Bias,
// given input, weight and bias matrix files
vector<vector<float>> fc_output_naive(string input, string weights,string bias){
	vector<vector<float>> i=read_matrix(input);
	vector<vector<float>> w=read_matrix(weights);
	vector<vector<float>> b=read_matrix(bias);
//	print_matrix(i);
//	cout<<'\n';
//	print_matrix(w);
//	cout<<'\n';
//	print_matrix(mul_matrix(i, w));
//	cout<<"\n";

	//Catching error when input and weights matrix can't be multiplied because of wrong dimensions
	if(i[0].size()!=w.size()){
		cout<<"The dimensions of input("<<i.size()<<","<<i[0].size()<<") and weight("
				<<w.size()<<","<<w[0].size()<<") matrixes are not suitable for matrix multiplication"<<"\n\n";
		exception e;
		throw e;
	}

	//Catching error when dimensions of input*weight doesn't match with bias matrix
	if(i.size()!=b.size() || w[0].size()!=b[0].size() ){
		cout<<"The dimensions of input*weight matrix("<<i.size()<<","<<w[0].size()<<") "
				"doesn't match with the bias matrix("<<b.size()<<","<<b[0].size() <<")\n"
				"Hence elements wise addition isn't possible."<<"\n\n";
		exception e;
		throw e;
	}
	vector<vector<float>> output=add_matrix(mul_matrix(i, w), b);
	return output;
}
void create_plot_files_naive(int matrix_size, int num_runs, string outputfile){
	float runtime[num_runs];
	for(int t=0;t<num_runs;t++){
		vector<vector<float>> input( matrix_size, vector<float> (matrix_size));
		for(int i=0;i<matrix_size;i++){
			for(int j=0;j<matrix_size;j++){
				input[j][i]=rand()*1.0/rand();
			}
		}
		vector<vector<float>> weights( matrix_size, vector<float> (matrix_size));
		for(int i=0;i<matrix_size;i++){
			for(int j=0;j<matrix_size;j++){
				weights[j][i]=rand()*1.0/rand();
			}
		}
		vector<vector<float>> bias( matrix_size, vector<float> (matrix_size));
		for(int i=0;i<matrix_size;i++){
			for(int j=0;j<matrix_size;j++){
				bias[j][i]=rand()*1.0/rand();
			}
		}
		auto start_time = chrono::high_resolution_clock::now();
		vector<vector<float>> output=add_matrix(mul_matrix(input, weights), bias);

		auto end_time = chrono::high_resolution_clock::now();
		auto elapsed_time =chrono::duration_cast<chrono::microseconds>(end_time - start_time);
		runtime[t]=elapsed_time.count();
	}
	ofstream stream(outputfile);


	float sde=0;

	float mean=0;
	for(int i=0;i<num_runs;i++){
			mean+=runtime[i];
		}
	mean/=num_runs;
	for(int i=0;i<num_runs;i++){
		sde+=(mean-runtime[i])*(mean-runtime[i]);
	}
	sde/=num_runs;
	sde=sqrt(sde);
	for(int i=0;i<num_runs;i++){
		stream<<runtime[i]<<" "<<mean<<" "<<sde<<'\n';
	}
	stream.close();

}
void create_all_plot_files_naive(int num_runs){
	for(int i=10;i<=100;i+=10){
		create_plot_files_naive(i, num_runs, "plot_naive_"+to_string(i)+"_"+to_string(num_runs)+".txt");
	}
	for(int i=150;i<=750;i+=50){
		create_plot_files_naive(i, num_runs, "plot_naive_"+to_string(i)+"_"+to_string(num_runs)+".txt");
	}
}

//int main(int argc, char **argv) {
//	string function=argv[1];
//	if(function.compare("fullyconnected")==0){
//		//Checking if number of arguments are correct
//		if(argc<6){
//			cout<<"Only "<<argc<<" command line arguments have been provided (including executable name). 6"
//					" are required for correct functioning.\nSample cmd line arguments:"
//					" './yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt'"
//					" \n\n";
//			return 0;
//		}
//
//		vector<vector<float>> output=fc_output(argv[2],argv[3],argv[4]);
////		print_matrix(output);
//		write_matrix(argv[5], output);
//	}
//	else if(function.compare("activation")==0){
//		//Checking if number of arguments are correct
//		if(argc<5){
//			cout<<"Only "<<argc<<" command line arguments have been provided (including executable name). 5"
//					" are required for correct functioning.\nSample cmd line arguments:"
//					" './yourcode.out activation relu inputmatrix.txt outputmatrix.txt'"
//					" \n\n";
//			return 0;
//				}
//		string activation=argv[2];
//		if(activation.compare("relu")==0){
//			vector<vector<float>> output=relu(argv[3]);
//			write_matrix(argv[4], output);
//		}
//		else if(activation.compare("tanh")==0){
//			vector<vector<float>> output=tanh(argv[3]);
//			write_matrix(argv[4], output);
//		}
//		//Printing Error Message in case of wrong command line argument
//		else{
//			cout<<"Activation function specified in argument 3 is neither 'relu' nor 'tanh'."<<'\n';
//		}
//	}
//	else if(function.compare("pooling")==0){
//		//Checking if number of arguments are correct
//			if(argc<6){
//				cout<<"Only "<<argc<<" command line arguments have been provided (including executable name). 6"
//						" are required for correct functioning.\nSample cmd line arguments:"
//						" './yourcode.out pooling max inputmatrix.txt stride outputmatrix.txt'"
//						" \n\n";
//				return 0;
//			}
//			string type=argv[2];
//
//			string temp=argv[4];
//			int j=0;
//			//Checking if stride given in arguments is an integer
//			for(int i=0;i<temp.length();i++){
//				if(isdigit(temp[i])==0){
//					cout<<"Stride:'"<<argv[4]<<"' - given in arguments is not an integer. \n\n";
//					return 0;
//				}
//			}
//
//			int stride=stoi(argv[4]);
//			if(type.compare("max")==0){
//				vector<vector<float>> output=max_pool(argv[3], stride);
//				write_matrix(argv[5], output);
//
//			}
//			else if(type.compare("average")==0){
//				vector<vector<float>> output=average_pool(argv[3], stride);
//				write_matrix(argv[5], output);
//			}
//			//Printing Error Message in case of wrong command line argument
//			else{
//				cout<<"Type of stride mentioned in 3rd argument is neither 'max' nor 'average'."<<'\n';
//			}
//	}
//	else if(function.compare("probability")==0){
//		//Checking if number of arguments are correct
//		if(argc<5){
//			cout<<"Only "<<argc<<" command line arguments have been provided (including executable name). 5"
//					" are required for correct functioning.\nSample cmd line arguments:"
//					" './yourcode.out probability softmax inputvector.txt outputvector.txt'"
//					" \n\n";
//			return 0;
//		}
//		string type=argv[2];
//		if(type.compare("sigmoid")==0){
//			vector<float> output=sigmoid(argv[3]);
//			write_vector(argv[4], output);
//		}
//		else if(type.compare("softmax")==0){
//			vector<float> output=softmax(argv[3]);
//			write_vector(argv[4], output);
//		}
//		//Printing Error Message in case of wrong command line argument
//		else{
//			cout<<"Type of probability specified in argument 3 is neither 'softmax' nor 'sigmoid'."<<'\n';
//		}
//	}
//	//Printing Error Message in case of wrong command line argument
//	else{
//		cout<<"Function specified in 2nd argument is not present in {'fullyconnected', 'activation', 'pooling', "
//				"'probability'}. Try again with a correct function."<<'\n';
//	}
//
//
//
//	return 0;
//}
//


