#include <math.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
#include "a1task2_mkl.h"
#include "a1task2_openblas.h"
#include "a1task2_naive.h"
#include "a1task2_pthread.h"
using namespace std;

int main(int argc, char **argv) {
	string function=argv[1];
	if(function.compare("fullyconnected")==0){
		//Checking if number of arguments are correct
		if(argc<7){
			cout<<"Only "<<argc<<" command line arguments have been provided (including executable name). 7"
					" are required for correct functioning.\nSample cmd line arguments:"
					" './yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt implementation_type'"
					" \n\n";
			return 0;
		}
		string implementation=argv[6];
		if(implementation.compare("mkl")==0){
			vector<vector<float>> output=fc_output_mkl(argv[2],argv[3],argv[4]);
			//print_matrix(output);
			write_matrix_mkl(argv[5], output);
		}
		else if(implementation.compare("openblas")==0){
			vector<vector<float>> output=fc_output_openblas(argv[2],argv[3],argv[4]);
			//print_matrix(output);
			write_matrix_openblas(argv[5], output);
		}

		else if(implementation.compare("pthread")==0){
				vector<vector<float>> output=fc_output_pthread(argv[2],argv[3],argv[4]);
				//print_matrix(output);
				write_matrix_pthread(argv[5], output);
				}
		else if(implementation.compare("naive")==0){
				vector<vector<float>> output=fc_output_naive(argv[2],argv[3],argv[4]);
				//print_matrix(output);
				write_matrix(argv[5], output);
				}
		else{
			cout<<"Implementation type specified in last argument must be one of {'mkl', 'openblas', 'pthread', 'naive'}."
							"Try again with a correct function."<<'\n';
		}
	}
	//Sample cmd line: /.yourcode.out plot matrix_size num_runs outputfile implementation
	else if(function.compare("plot")==0){
		string implementation=argv[5];
		if(implementation.compare("mkl")==0){
			int matrix_size=stoi(argv[2]);
			int num_runs=stoi(argv[3]);
			create_plot_files_mkl(matrix_size, num_runs, argv[4]);
		}
		else if(implementation.compare("openblas")==0){
			int matrix_size=stoi(argv[2]);
			int num_runs=stoi(argv[3]);
			create_plot_files_openblas(matrix_size, num_runs, argv[4]);
		}

		else if(implementation.compare("pthread")==0){
			int matrix_size=stoi(argv[2]);
			int num_runs=stoi(argv[3]);
			create_plot_files_pthread(matrix_size, num_runs, argv[4]);
		}
		else if(implementation.compare("naive")==0){
			int matrix_size=stoi(argv[2]);
			int num_runs=stoi(argv[3]);
			create_plot_files_naive(matrix_size, num_runs, argv[4]);
		}
		else{
			cout<<"Implementation type specified in last argument must be one of {'mkl', 'openblas', 'pthread', 'naive'}."
							"Try again with a correct function."<<'\n';
		}

	}
	//Sample cmd line: /.yourcode.out plot_all num_runs implementation
	else if(function.compare("plot_all")==0){
		string implementation=argv[3];
		if(implementation.compare("mkl")==0){
			int num_runs=stoi(argv[2]);
			create_all_plot_files_mkl(num_runs);
		}
		else if(implementation.compare("openblas")==0){
			int num_runs=stoi(argv[2]);
			create_all_plot_files_openblas(num_runs);
		}

		else if(implementation.compare("pthread")==0){
			int num_runs=stoi(argv[2]);
			create_all_plot_files_pthread(num_runs);
		}
		else if(implementation.compare("naive")==0){
			int num_runs=stoi(argv[2]);
			create_all_plot_files_naive(num_runs);
		}
		else{
			cout<<"Implementation type specified in last argument must be one of {'mkl', 'openblas', 'pthread', 'naive'}."
							"Try again with a correct function."<<'\n';
		}

	}
	else if(function.compare("activation")==0){
			//Checking if number of arguments are correct
			if(argc<5){
				cout<<"Only "<<argc<<" command line arguments have been provided (including executable name). 5"
						" are required for correct functioning.\nSample cmd line arguments:"
						" './yourcode.out activation relu inputmatrix.txt outputmatrix.txt'"
						" \n\n";
				return 0;
					}
			string activation=argv[2];
			if(activation.compare("relu")==0){
				vector<vector<float>> output=relu(argv[3]);
				write_matrix(argv[4], output);
			}
			else if(activation.compare("tanh")==0){
				vector<vector<float>> output=tanh(argv[3]);
				write_matrix(argv[4], output);
			}
			//Printing Error Message in case of wrong command line argument
			else{
				cout<<"Activation function specified in argument 3 is neither 'relu' nor 'tanh'."<<'\n';
			}
		}
		else if(function.compare("pooling")==0){
			//Checking if number of arguments are correct
				if(argc<6){
					cout<<"Only "<<argc<<" command line arguments have been provided (including executable name). 6"
							" are required for correct functioning.\nSample cmd line arguments:"
							" './yourcode.out pooling max inputmatrix.txt stride outputmatrix.txt'"
							" \n\n";
					return 0;
				}
				string type=argv[2];

				string temp=argv[4];
				int j=0;
				//Checking if stride given in arguments is an integer
				for(int i=0;i<temp.length();i++){
					if(isdigit(temp[i])==0){
						cout<<"Stride:'"<<argv[4]<<"' - given in arguments is not an integer. \n\n";
						return 0;
					}
				}

				int stride=stoi(argv[4]);
				if(type.compare("max")==0){
					vector<vector<float>> output=max_pool(argv[3], stride);
					write_matrix(argv[5], output);

				}
				else if(type.compare("average")==0){
					vector<vector<float>> output=average_pool(argv[3], stride);
					write_matrix(argv[5], output);
				}
				//Printing Error Message in case of wrong command line argument
				else{
					cout<<"Type of stride mentioned in 3rd argument is neither 'max' nor 'average'."<<'\n';
				}
		}
		else if(function.compare("probability")==0){
			//Checking if number of arguments are correct
			if(argc<5){
				cout<<"Only "<<argc<<" command line arguments have been provided (including executable name). 5"
						" are required for correct functioning.\nSample cmd line arguments:"
						" './yourcode.out probability softmax inputvector.txt outputvector.txt'"
						" \n\n";
				return 0;
			}
			string type=argv[2];
			if(type.compare("sigmoid")==0){
				vector<float> output=sigmoid(argv[3]);
				write_vector(argv[4], output);
			}
			else if(type.compare("softmax")==0){
				vector<float> output=softmax(argv[3]);
				write_vector(argv[4], output);
			}
			//Printing Error Message in case of wrong command line argument
			else{
				cout<<"Type of probability specified in argument 3 is neither 'softmax' nor 'sigmoid'."<<'\n';
			}
		}
		//Printing Error Message in case of wrong command line argument

	else{
		cout<<"Second argument must be one of {fullyconnected, probability,pooling,activation,plot,plot_all}. Try again with correct command. Sample command line\n"
				"'./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt implementation_type' "
				"\n\n";
	}
	return 0;
}





