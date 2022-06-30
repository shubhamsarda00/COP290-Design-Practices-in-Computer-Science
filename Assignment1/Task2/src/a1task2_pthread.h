/*
 * a1task2_pthread.h
 *
 *  Created on: 12-Feb-2022
 *      Author: shubham
 */

#ifndef TASK2_A1TASK2_PTHREAD_H_
#define TASK2_A1TASK2_PTHREAD_H_

#include <vector>
#include <string.h>
#include <iostream>


using namespace std;

 void* mul_fn(void*arg);
 void fc_layer_fn_with_p_threads();
 //vector<vector<float>> read_matrix_pthread(string file);
 vector<vector<float>> fc_output_pthread(string inputfile,string weightsfile, string biasfile);
 void write_matrix_pthread(string file, vector<vector<float>> matrix);
 void create_plot_files_pthread(int matrix_size, int num_runs, string outputfile);
 void create_plot_files_pthread(int matrix_size, int num_runs, string outputfile);
void create_all_plot_files_pthread(int num_runs);

#endif /* TASK2_A1TASK2_PTHREAD_H_ */
