/*
 * a1task2_openblas.h
 *
 *  Created on: 09-Feb-2022
 *      Author: shubham
 */

#ifndef TASK2_A1TASK2_OPENBLAS_H_
#define TASK2_A1TASK2_OPENBLAS_H_


//#include <math.h>
#include <vector>
#include <string.h>
//#include <fstream>
#include <iostream>
//#include <cblas.h>
//#include <pthread.h>
//#include "mkl/mkl.h"

using namespace std;

// Function for reading a matrix from an input file
vector<vector<float>> read_matrix_openblas(string file);

//Function for writing a matrix to an output file
void write_matrix_openblas(string file, vector<vector<float>> matrix);
//double* matrix_to_array( vector<vector<double>> matrix,double* arr);

//Function for writing a vector to an output file
void write_vector_openblas(string file, vector<float> vec);

//Function for printing a matrix on the console in a readable manner
void print_matrix_openblas(vector<vector<float>> m);

//Function for printing a vector on the console in a readable manner
void print_vector_openblas(vector<float> v);

// Function for reading a vector from an input file
vector<float> read_vector_openblas(string file);
vector<vector<float>> fc_output_openblas(string input, string weights,string bias);
void create_plot_files_openblas(int matrix_size, int num_runs, string outputfile);
void create_all_plot_files_openblas(int num_runs);
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







#endif /* TASK2_A1TASK2_OPENBLAS_H_ */
