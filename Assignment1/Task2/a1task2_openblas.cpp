/*
 * a1task2_openblas.cpp
 *
 *  Created on: 09-Feb-2022
 *      Author: shubham
 */

#include <math.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
#include <cblas.h>
#include <pthread.h>
//#include "mkl/mkl.h"
#include <chrono>


using namespace std;

// Function for reading a matrix from an input file
vector<vector<float>> read_matrix_openblas(string file){
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
void write_matrix_openblas(string file, vector<vector<float>> matrix){
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
//double* matrix_to_array( vector<vector<double>> matrix,double* arr){
//	int c=matrix[0].size();
//	int r=matrix.size();
//	for(int i=0;i<c;i++){
//		for(int j=0;j<r;j++){
//			arr[i*c+j]=matrix[j][i];
//		}
//	}
//	return arr;
//}

//Function for writing a vector to an output file
void write_vector_openblas(string file, vector<float> vec){
	ofstream stream(file);
	int n=vec.size();
	stream<<n<<'\n';

	for(int i=0;i<n;i++){
		stream<<vec[i]<<'\n';
	}
	stream.close();
}

//Function for printing a matrix on the console in a readable manner
void print_matrix_openblas(vector<vector<float>> m){
	for(int i=0;i<m.size();i++){
			for(int j=0;j<m[0].size();j++){
				cout<<m[i][j]<<" ";
				}
			cout<<'\n';
			}
}

//Function for printing a vector on the console in a readable manner
void print_vector_openblas(vector<float> v){
	for(int i=0;i<v.size();i++){
		cout<<v[i]<<" ";
	}
}

// Function for reading a vector from an input file
vector<float> read_vector_openblas(string file){
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
vector<vector<float>> fc_output_openblas(string input, string weights,string bias){
	vector<vector<float>> i=read_matrix_openblas(input);
	vector<vector<float>> w=read_matrix_openblas(weights);
	vector<vector<float>> b=read_matrix_openblas(bias);
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
	//print_matrix(i);
	float i_arr[i.size()*i[0].size()];
	for(int m=0;m<i[0].size();m++){
		for(int n=0;n<i.size();n++){
			//cout<<m<<","<<n<<"\n";
			i_arr[m*i.size()+n]=i[n][m];
			//cout<<m*i.size()+n<<","<<i[n][m]<<"\n";
		}
	}

	float w_arr[w.size()*w[0].size()];
		for(int m=0;m<w[0].size();m++){
			for(int n=0;n<w.size();n++){
				w_arr[m*w.size()+n]=w[n][m];
		}
	}
	float b_arr[b.size()*b[0].size()];
	for(int m=0;m<b[0].size();m++){
		for(int n=0;n<b.size();n++){
			b_arr[m*b.size()+n]=b[n][m];
		}
	}
//	for(int p=0;p<i.size()*i[0].size();p++){
//		cout<<i_arr[p]<<'\n';
//	}
	cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, b.size(), b[0].size(), i[0].size(),
			1, i_arr, i.size(), w_arr, w.size(),1, b_arr, b.size());

	vector<vector<float>> output( b.size() , vector<float> (b[0].size()));

	for(int l=0;l<b[0].size();l++){
		for(int j=0;j<b.size();j++){
			output[j][l]=b_arr[l*b.size()+j];
		}
	}

	return output;
}
// Function for adding two matrices
vector<vector<float>> add_matrix_openblas(vector<vector<float>> a, vector<vector<float>> b){
	vector<vector<float>> c(a.size() , vector<float> (a[0].size()));
	for(int i=0;i<a.size();i++){
		for(int j=0;j<a[0].size();j++){
			c[i][j]=a[i][j]+b[i][j];
		}
	}
	return c;
}


// Function for multiplying two matrices
vector<vector<float>> mul_matrix_openblas(vector<vector<float>> a, vector<vector<float>> b){
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
bool compare_matrices_openblas(vector<vector<float>> truth, vector<vector<float>> output){
	bool a=true;
	for(int i=0;i<truth.size();i++){
		for(int j=0;j<truth[0].size();j++){
			if(fabs(truth[i][j]-output[i][j])>1e-5){
				cout<<truth[i][j]<<", "<<output[i][j]<<" "<<fabs(truth[i][j]-output[i][j])<<"\n";
				a=false;
				return a;
			}
		}
	}
	return a;
}
void create_plot_files_openblas(int matrix_size, int num_runs, string outputfile){
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
		float i_arr[input.size()*input[0].size()];
			for(int m=0;m<input[0].size();m++){
				for(int n=0;n<input.size();n++){
					//cout<<m<<","<<n<<"\n";
					i_arr[m*input.size()+n]=input[n][m];
					//cout<<m*i.size()+n<<","<<i[n][m]<<"\n";
				}
			}

			float w_arr[weights.size()*weights[0].size()];
				for(int m=0;m<weights[0].size();m++){
					for(int n=0;n<weights.size();n++){
						w_arr[m*weights.size()+n]=weights[n][m];
				}
			}
			float b_arr[bias.size()*bias[0].size()];
			for(int m=0;m<bias[0].size();m++){
				for(int n=0;n<bias.size();n++){
					b_arr[m*bias.size()+n]=bias[n][m];
				}
			}
		//	for(int p=0;p<i.size()*i[0].size();p++){
		//		cout<<i_arr[p]<<'\n';
		//	}
			cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, bias.size(), bias[0].size(), input[0].size(),
					1, i_arr, input.size(), w_arr, weights.size(),1, b_arr, bias.size());

			vector<vector<float>> output( bias.size() , vector<float> (bias[0].size()));

			for(int l=0;l<bias[0].size();l++){
				for(int j=0;j<bias.size();j++){
					output[j][l]=b_arr[l*bias.size()+j];
				}
			}
			auto end_time = chrono::high_resolution_clock::now();
			auto elapsed_time =chrono::duration_cast<chrono::microseconds>(end_time - start_time);
//			if(!compare_matrices_openblas(add_matrix_openblas(mul_matrix_openblas(input, weights), bias),output)){
//				cout<<"Wrong Answer \n";
//				//exit(0);
//			}
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

void create_all_plot_files_openblas(int num_runs){
	for(int i=10;i<=100;i+=10){
		create_plot_files_openblas(i, num_runs, "plot_openblas_"+to_string(i)+"_"+to_string(num_runs)+".txt");
	}
	for(int i=150;i<=750;i+=50){
			create_plot_files_openblas(i, num_runs, "plot_openblas_"+to_string(i)+"_"+to_string(num_runs)+".txt");
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
//		vector<vector<double>> output=fc_output(argv[2],argv[3],argv[4]);
////		print_matrix(output);
//		write_matrix(argv[5], output);
//		}
//	return 0;
//}










