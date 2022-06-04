/*
 * a1task2_naive.h
 *
 *  Created on: 12-Feb-2022
 *      Author: shubham
 */

#ifndef TASK2_A1TASK2_NAIVE_H_
#define TASK2_A1TASK2_NAIVE_H_
//#include <math.h>

#include <vector>
#include <string.h>
#include <iostream>

using namespace std;

vector<vector<float>> read_matrix(string file);
void write_matrix(string file, vector<vector<float>> matrix);
void write_vector(string file, vector<float> vec);
void print_matrix(vector<vector<float>> m);
void print_vector(vector<float> v);
vector<float> read_vector(string file);
vector<vector<float>> add_matrix(vector<vector<float>> a, vector<vector<float>> b);
vector<vector<float>> mul_matrix(vector<vector<float>> a, vector<vector<float>> b);
float tanh_float(float a);
float sigmoid_float(float a);
float relu_float(float a);
vector<vector<float>> average_pool(string input,int stride);
vector<vector<float>> max_pool(string input,int stride);
vector<float> sigmoid(string file);
vector<float> softmax(string file);
vector<vector<float>> tanh(string input);
vector<vector<float>> relu(string input);
vector<vector<float>> fc_output_naive(string input, string weights,string bias);
void create_plot_files_naive(int matrix_size, int num_runs, string outputfile);
void create_all_plot_files_naive(int num_runs);



#endif /* TASK2_A1TASK2_NAIVE_H_ */
