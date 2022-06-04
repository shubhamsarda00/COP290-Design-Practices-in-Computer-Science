#include<pthread.h>
#include<iostream>
#include <vector>
#include <fstream>
//#include <iomanip>
#include <chrono>
#include <math.h>
#include "a1task2_naive.h"
using namespace std;


//vector<vector<float>> input(2000,vector<float>(2000));
//vector<vector<float>> weights(2000,vector<float>(2000));
//vector<vector<float>> bias(2000,vector<float>(2000));
//vector<vector<float>> output(2000,vector<float>(2000));
float input[2000][2000];//{{3 ,7 ,3, 6},{9 ,2 ,0 ,3},{0 ,2, 1 ,7 },{2 ,2 ,7 ,9 }};
float weights[2000][2000];//{{6 ,5 ,5 ,2 },{1 ,7 ,9 ,6 },{6 ,6 ,8 ,9 },{0 ,3 ,5 ,2 }};
float bias[2000][2000];//{{5,5,5,5},{5,5,5,5},{5,5,5,5},{5,5,5,5}};
float output[2000][2000];
int input_rows,input_columns,weights_rows,weights_columns,bias_rows,bias_columns;

int number_of_row_of_the_resultant_matrix=0;


pthread_mutex_t lock;


 void* mul_fn(void*arg)
{    pthread_mutex_lock(&lock);
    int row_number = number_of_row_of_the_resultant_matrix; //i denotes row number of resultant matC

     for (int i = 0; i < input_columns; i++)
      {  int sum=0;

          for (int j = 0; j < weights_rows; j++)
        {
           output[row_number][i]+=input[row_number][j]*weights[j][i];

       }
   // d[row_number][i]+=c[row_number][i];
    }
  number_of_row_of_the_resultant_matrix++;
   pthread_mutex_unlock(&lock);
   return NULL;
}

void fc_layer_fn_with_p_threads()
{

//cout<<input_rows<<endl;
//cout<<weights_columns<<endl;

//
//for(int i=0;i<input_rows;i++)
//{
//  for(int j=0;j<input_columns;j++)
//  {                          //transferring the data from the array to  inputmatrix_vector i.e a
//cout<<input[i][j]<<" ";
//  }
//cout<<endl;}
//
//
//for(int i=0;i<weights_rows;i++)
//{
//  for(int j=0;j<weights_columns;j++)
//  {                      //pushing elements from array3 to weightmatrix vector}
//   cout<<weights[i][j]<<" ";
//  }
//cout<<endl;}
//
//
//for(int i=0;i<bias_rows;i++)
//{
//     for(int j=0;j<bias_columns;j++)   //pushing elements from array3 to bias vector
//  {
//       cout<<bias[i][j]<<" ";
//  }
//cout<<endl;
//}

for(int i=0;i<bias_rows;i++)
{
  for(int j=0;j<bias_columns;j++)
  {
    output[i][j]=0;
  }
}
pthread_mutex_init(&lock,NULL);
pthread_attr_t attr;
pthread_attr_init(&attr);


pthread_t number_of_threads[input_rows];

for(int i=0;i<input_rows;i++)
{  int*p;
    pthread_create(&number_of_threads[i],&attr,mul_fn,(void*)p);

}

for (int i = 0; i <input_rows; i++)
  pthread_join(number_of_threads[i], NULL);

  pthread_mutex_destroy(&lock);

for(int i=0;i<input_rows;i++)
{
  for(int j=0;j<weights_columns;j++)
  output[i][j]+=bias[i][j];
}


// ofstream file;
//file.open(temp);
//
//file<<weights_columns<<endl;                   //writing to the file
//
//file<<input_rows<<endl;                   //writing to the file
//
//
//
//     setprecision(5);
//
//
// for(int i=0;i<input_rows;i++)
//   {
//       for(int j=0;j<weights_columns;j++)
//       {
//         file<<output[j][i]<<endl;
//
//       }
//
//   }

return;
}


















//cout<<input_rows<<endl;
//cout<<weights_columns<<endl;

//
//for(int i=0;i<input_rows;i++)
//{
//  for(int j=0;j<input_columns;j++)
//  {                          //transferring the data from the array to  inputmatrix_vector i.e a
//cout<<input[i][j]<<" ";
//  }
//cout<<endl;}
//
//
//for(int i=0;i<weights_rows;i++)
//{
//  for(int j=0;j<weights_columns;j++)
//  {                      //pushing elements from array3 to weightmatrix vector}
//   cout<<weights[i][j]<<" ";
//  }
//cout<<endl;}
//
//
//for(int i=0;i<bias_rows;i++)
//{
//     for(int j=0;j<bias_columns;j++)   //pushing elements from array3 to bias vector
//  {
//       cout<<bias[i][j]<<" ";
//  }
//cout<<endl;
//}



























void write_matrix_pthread(string file, vector<vector<float>> matrix){
	ofstream stream(file);
	int c=bias_columns;
	int r=bias_rows;
	stream<<c<<'\n';
	stream<<r<<'\n';

	for(int i=0;i<c;i++){
		for(int j=0;j<r;j++){
			stream<<matrix[j][i]<<'\n';
		}
	}
	stream.close();
}

//vector<vector<float>> read_matrix_pthread(string file){
//	fstream stream;
//	try {
//		stream.open(file);
//		//Catching error if input file is not present
//		if(stream.fail()){
//			throw file;
//		}
//	}
//	catch(string& s){
//		cout<<"File with the name '"<<s<< "' doesn't exist."<<"\n\n";
//		exception e;
//		throw e;
//		//exit(0);
//	}
//	string line;
//	getline(stream,line);
//	int c=stoi(line);
//	getline(stream,line);
//	int r=stoi(line);
//	vector<vector<float>> matrix( r , vector<float> (c));
//	for(int i=0;i<c;i++){
//		for(int j=0;j<r;j++){
//			getline(stream,line);
//			matrix[j][i]=stof(line);
//		}
//	}
//
//	return matrix;
//}





vector<vector<float>> fc_output_pthread(string inputfile,string weightsfile, string biasfile){
	ifstream myfile;
	ifstream myfile1;
	ifstream myfile2;
	myfile.open(inputfile);      //opening the file of inputmatrix

	if(!myfile)
	  {
		 cout<<"File with name = " <<inputfile<<" does not Exists"<<endl;
		exit(1);                                                    //if file not present then throw file not found error and exit the program
	  }
	else if(myfile.eof()==true)
	  {
		 cout<<"File with name = "<<inputfile<<"is empty"<<endl;  //if file is empty then throw empty file  error
		 exit(1);
	  }
									//column of inputmatrix
		myfile>>input_columns;


		myfile>>input_rows;               //row of input matrix

	//vector<vector<float>>to_be_returned;  //vector whose values will be written to the targeted output file

	int j=0;
	int i=0;
	vector<float> array[input_rows];        // array of vectors with number of  elements equal to row1
	float l=0;
	while(myfile>>l)
	{
	if(i==input_rows-1)
	{                                            //writing the data into the array
	  array[i].push_back(l);
		i=0;
	  continue;
	}
	array[i].push_back(l);
	i++;

	}
	//input=vector<vector<float>>( input_rows, vector<float> (input_columns));
	for(int i=0;i<input_rows;i++)
	{
	for(int j=0;j<array[i].size();j++)
	{ input[i][j]=array[i].at(j);       //transferring the data from the array to  inputmatrix_vector i.e a
	//cout<<input[i][j]<<" ";
	}
	//cout<<endl;
	}
	myfile.close();


	myfile1.open(weightsfile);

	if(!myfile1)     ////opening the file of weightmatrix

	{
			cout<<"File with name = " <<weightsfile<<" does not Exists"<<endl;     //if file of weightmatrix is not presesnt then throw file not found error and exit the program
						exit(1);
		  }
	 else if(myfile1.eof()==true)
	  {
		 cout<<"File with name = "<<weightsfile<<"is empty"<<endl; //if file of weightmatrix is empty then throw empty error and exit the program
		 exit(1);
	  }

		myfile1>>weights_columns;                          //column of biasmatrix

		myfile1>>weights_rows;                           //row of biasmatrix

	  i=0;
	  j=0;


	vector<float> array2[weights_rows];                         //array with row2 elements of vector
	l=0;
	while(myfile1>>l)
	{
	if(i==weights_rows-1)
	{
													 //loop to fill the array2 from myfile1
	  array2[i].push_back(l);
		i=0;
	  continue;
	}

	array2[i].push_back(l);
	i++;

	}

	//weights=vector<vector<float>>( weights_rows, vector<float>(weights_columns));
	for(int i=0;i<weights_rows;i++)
	{
	for(int j=0;j<array2[i].size();j++)
	{ weights[i][j]=array2[i][j];                         //pushing elements from array3 to weightmatrix vector}
	//cout<<weights[i][j]<<" ";
	}
	//cout<<endl;
	}
	myfile1.close();

	myfile2.open(biasfile);           //opening the file of biasmatrix


	if(!myfile2)
		  {
			cout<<"File with name =" <<biasfile<<" does not Exists"<<endl;  //if file of biasmatrix is not presesnt then throw file not found error and exit the program
			exit(1);
		  }
	 else if(myfile2.eof()==true)
	  {
		 cout<<"File with name = "<<biasfile<<"is empty"<<endl;     //if file of biasmatrix is empty then throw empty error and exit the program
		 exit(1);
	  }
												 //column of biasmatrix
		myfile2>>bias_columns;

									 //row of biasmatrix
		myfile2>>bias_rows;

	  i=0;
	  j=0;


	vector<float> array3[bias_rows];                        //array with row3 elements of vector
	l=0;
	while(myfile2>>l)
	{
	if(i==bias_rows-1)
	{
											 //loop to fill the array3 from myfile2
	  array3[i].push_back(l);
		i=0;
	  continue;
	}

	array3[i].push_back(l);
	i++;

	}

	//bias=vector<vector<float>>( bias_rows, vector<float>(bias_columns));
	for(int i=0;i<bias_rows;i++)
	{
	 for(int j=0;j<array3[i].size();j++)        //pushing elements from array3 to bias vector
	{ bias[i][j]=array3[i][j];
	 //  cout<<bias[i][j]<<" ";
	}
	//cout<<endl;
	}

	//fully_connected_layer(a,weight_matrix,bias_matrix);  //calling fullyconnectedlayer fn
//		cout<<input_rows<<endl;
//		cout<<input_columns<<endl;
//		cout<<weights_rows<<endl;
//		cout<<weights_columns<<endl;
//		cout<<bias_rows<<endl;
//		cout<<bias_columns<<endl;

	fc_layer_fn_with_p_threads();
	//cout<<"DONE";
//	bool c=compare_matrices(add_matrix(mul_matrix(input, weights), bias),output);
//	cout<<c<<endl;

vector<vector<float>>to_be_returned;
	for(int i=0;i<bias_rows;i++)
	{	vector<float>temp;
		for(int j=0;j<bias_columns;j++)
		{
                       temp.push_back(output[i][j]);
		}
	to_be_returned.push_back(temp);
	temp.clear();
	}
	
	
	print_matrix(to_be_returned);
	
	return to_be_returned;
	
}

void create_plot_files_pthread(int matrix_size, int num_runs, string outputfile){
	float runtime[num_runs];
	int count=0;
	input_columns=input_rows=weights_columns=weights_rows=bias_columns=bias_rows= matrix_size;
	for(int t=0;t<num_runs;t++){
//		input=vector<vector<float>>( input_rows, vector<float> (input_columns));
//		for(int i=0;i<matrix_size;i++){
//			for(int j=0;j<matrix_size;j++){
//				input[j][i]=rand()/rand();
//			}
//		}
//		vector<vector<float>> weights( weights_rows, vector<float> (weights_columns));
//		for(int i=0;i<matrix_size;i++){
//			for(int j=0;j<matrix_size;j++){
//				weights[j][i]=rand()/rand();
//			}
//		}
//		vector<vector<float>> bias( bias_rows, vector<float> (bias_columns));
//		for(int i=0;i<matrix_size;i++){
//			for(int j=0;j<matrix_size;j++){
//				bias[j][i]=rand()/rand();
//			}
//		}
//Input
		int j=0;
		int i=0;
		vector<float> array[input_rows];        // array of vectors with number of  elements equal to row1
		float l=0;
		int k=0;
		while(k<matrix_size)
		{
		if(i==input_rows-1)
		{                                            //writing the data into the array
		l=rand()*1.0/rand();
		array[i].push_back(l);
		i=0;
		k++;
		continue;
		}
		l=rand()*1.0/rand();
		array[i].push_back(l);
		i++;
		}
	
		//cout<<"Size<<"<<input.size()<<"\n";
		for(int i=0;i<input_rows;i++)
		{
		for(int j=0;j<array[i].size();j++)
		{ input[i][j]=array[i].at(j);       //transferring the data from the array to  inputmatrix_vector i.e a
		//cout<<input[i][j]<<" ";
		}
		//cout<<endl;
		}
//Weights
		i=0;
		j=0;
		vector<float> array2[weights_rows];                         //array with row2 elements of vector
		l=0;
		k=0;
		while(k<matrix_size)
		{
			if(i==weights_rows-1)
			{
					//loop to fill the array2 from myfile1
				l=rand()*1.0/rand();
				array2[i].push_back(l);
				i=0;
				k++;
				continue;
			}
		l=rand()*1.0/rand();
		array2[i].push_back(l);
		i++;
		}

		for(int i=0;i<weights_rows;i++)
		{
		for(int j=0;j<array2[i].size();j++)
		{ weights[i][j]=array2[i][j];                         //pushing elements from array3 to weightmatrix vector}
		//cout<<weights[i][j]<<" ";
		}
		//cout<<endl;
		}
//Bias
		i=0;
		j=0;


		vector<float> array3[bias_rows];                        //array with row3 elements of vector
		l=0;
		k=0;
		while(k<matrix_size)
		{
		if(i==bias_rows-1)
		{
								 //loop to fill the array3 from myfile2
			l=rand()*1.0/rand();
			k++;
			array3[i].push_back(l);
			i=0;
		  continue;
		}
		l=rand()*1.0/rand();
		array3[i].push_back(l);
		i++;
		}


		for(int i=0;i<bias_rows;i++)
		{
		 for(int j=0;j<array3[i].size();j++)        //pushing elements from array3 to bias vector
		{ bias[i][j]=array3[i][j];
		 //  cout<<bias[i][j]<<" ";
		}
		//cout<<endl;
		}
	/*		cout<<input_rows<<endl;
			cout<<input_columns<<endl;
			cout<<weights_rows<<endl;
			cout<<weights_columns<<endl;
			cout<<bias_rows<<endl;
			cout<<bias_columns<<endl;  */

		//cout<<"yes2 \n";
		auto start_time = chrono::high_resolution_clock::now();
	//	cout<<"yes3 \n";
		fc_layer_fn_with_p_threads();
	

		//cout<<"yes4 \n";
		//cout<<24;
		auto end_time = chrono::high_resolution_clock::now();

float temp[matrix_size][matrix_size];
for(int i=0;i<matrix_size;i++)
{
  for(int j=0;j<matrix_size;j++)
  temp[i][j]=0;
}

for(int i=0;i<matrix_size;i++)
{

     for(int j=0;j<matrix_size;j++)
     {
       for(int k=0;k<matrix_size;k++)
       {
         temp[i][j]+=input[i][k]*weights[k][j];
       }
    temp[i][j]=temp[i][j]+bias[i][j];
     }


}



		auto elapsed_time =chrono::duration_cast<chrono::microseconds>(end_time - start_time);



bool flag=true;
for(int i=0;i<matrix_size;i++)
{
  for(int j=0;j<matrix_size;j++)
  {   if(temp[i][j]!=output[i][j])
        {
          flag=false;
          break;
        }
   
   // cout<<output[i][j]<<" ";
  }
if(flag==false)
  break;

//cout<<endl;
}
if(flag==true)
count++;
else
{//cout<<"TEST WITH MATRIX SIZE "<<matrix_size<<" NOT PASSED"<<endl;
   break;
   }





//		print_matrix(add_matrix(mul_matrix(input, weights), bias));
//		print_matrix(output);


		runtime[t]=elapsed_time.count();
number_of_row_of_the_resultant_matrix=0;

	}
	if(count==num_runs)
	cout<<"All "<<num_runs<<" runtime tests with matrix size "<<matrix_size<<" passed"<<endl;
	else
	cout<<"All "<<num_runs <<" runtime tests with matrix size "<<matrix_size<<" not  passed"<<endl;
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


void create_all_plot_files_pthread(int num_runs)
{

for(int i=10;i<=100;i+=10)
{ string temp="plot_"+to_string(i)+"_pthread.txt";
	create_plot_files_pthread(i, num_runs, "plot_pthread_"+to_string(i)+"_"+to_string(num_runs)+".txt");
}
for(int i=150;i<=750;i+=50)
{ string temp="plot_"+to_string(i)+"_pthread.txt";
	create_plot_files_pthread(i, num_runs, "plot_pthread_"+to_string(i)+"_"+to_string(num_runs)+".txt");
}


}



//int main(int argc,char **argv){
//
//	string argue(argv[1]);
//
//	if(argue=="fullyconnected")
//		fc_output_pthread(argv[2], argv[3], argv[4], argv[5]);
//			 {// vector<vector<float>>a;
//			 // vector<vector<float>>weight_matrix;
//			 // vector<vector<float>>bias_matrix;
//
////			   fstream input_stream;
////			   string input_file=argv[2];
////			   	try {
////			   		input_stream.open(input_file);
////			   		//Catching error if input file is not present
////			   		if(input_stream.fail()){
////			   			throw input_file;
////			   		}
////			   	}
////			   	catch(string& s){
////			   		cout<<"File with the name '"<<s<< "' doesn't exist."<<"\n\n";
////			   		exception e;
////			   		throw e;
////			   		//exit(0);
////			   	}
////			   	string line;
////			   	getline(input_stream,line);
////			   	int c=stoi(line);
////			   	input_columns=c;
////			   	getline(input_stream,line);
////			   	int r=stoi(line);
////			   	input_rows=r;
////			   	vector<vector<float>> input( r , vector<float> (c));
////			   	for(int i=0;i<c;i++){
////			   		for(int j=0;j<r;j++){
////			   			getline(input_stream,line);
////			   			input[j][i]=stof(line);
////			   			cout<<input[j][i]<<" ";
////			   		}
////			   		cout<<"\n";
////			   	}
////			   input_stream.close();
////			   fstream weights_stream;
////			   string weights_file=argv[3];
////				try {
////					weights_stream.open(weights_file);
////					//Catching error if input file is not present
////					if(weights_stream.fail()){
////						throw weights_file;
////					}
////				}
////				catch(string& s){
////					cout<<"File with the name '"<<s<< "' doesn't exist."<<"\n\n";
////					exception e;
////					throw e;
////					//exit(0);
////				}
////				//string line;
////				getline(weights_stream,line);
////				c=stoi(line);
////				weights_columns=c;
////				getline(weights_stream,line);
////				r=stoi(line);
////				weights_rows=r;
////
////				vector<vector<float>> weights( r , vector<float> (c));
////				for(int i=0;i<c;i++){
////					for(int j=0;j<r;j++){
////						getline(weights_stream,line);
////						weights[j][i]=stof(line);
////						cout<<weights[j][i]<<" ";
////					}
////					cout<<"\n";
////				}
////				weights_stream.close();
////
////				fstream bias_stream;
////				string bias_file=argv[4];
////				try {
////					bias_stream.open(bias_file);
////					//Catching error if input file is not present
////					if(bias_stream.fail()){
////						throw bias_file;
////					}
////				}
////				catch(string& s){
////					cout<<"File with the name '"<<s<< "' doesn't exist."<<"\n\n";
////					exception e;
////					throw e;
////					//exit(0);
////				}
////				//string line;
////				getline(bias_stream,line);
////				c=stoi(line);
////				bias_columns=c;
////				getline(bias_stream,line);
////				r=stoi(line);
////				bias_rows=r;
////				vector<vector<float>> bias( r , vector<float> (c));
////				for(int i=0;i<c;i++){
////					for(int j=0;j<r;j++){
////						getline(bias_stream,line);
////						bias[j][i]=stof(line);
////					}
////				}
////				bias_stream.close();
//
//
//
////			ifstream myfile;
////			ifstream myfile1;
////			ifstream myfile2;
////			myfile.open(argv[2]);      //opening the file of inputmatrix
////
////			if(!myfile)
////			  {
////				 cout<<"File with name = " <<argv[2]<<" does not Exists"<<endl;
////				exit(1);                                                    //if file not present then throw file not found error and exit the program
////			  }
////	else if(myfile.eof()==true)
////		  {
////			 cout<<"File with name = "<<argv[2]<<"is empty"<<endl;  //if file is empty then throw empty file  error
////			 exit(1);
////		  }
////										//column of inputmatrix
////			myfile>>input_columns;
////
////
////			myfile>>input_rows;               //row of input matrix
////
////	//vector<vector<float>>to_be_returned;  //vector whose values will be written to the targeted output file
////
////	int j=0;
////	int i=0;
////	vector<float> array[input_rows];        // array of vectors with number of  elements equal to row1
////	 float l=0;
////	while(myfile>>l)
////	{
////	   if(i==input_rows-1)
////		{                                            //writing the data into the array
////		  array[i].push_back(l);
////			i=0;
////		  continue;
////	   }
////	array[i].push_back(l);
////	i++;
////
////	}
////	input=vector<vector<float>>( input_rows, vector<float> (input_columns));
////	for(int i=0;i<input_rows;i++)
////	{
////	  for(int j=0;j<array[i].size();j++)
////	  { input[i][j]=array[i].at(j);       //transferring the data from the array to  inputmatrix_vector i.e a
////	cout<<input[i][j]<<" ";
////	  }
////	cout<<endl;}
////	myfile.close();
////
////
////	myfile1.open(argv[3]);
////
////	 if(!myfile1)     ////opening the file of weightmatrix
////
////	  {
////				cout<<"File with name = " <<argv[3]<<" does not Exists"<<endl;                     //if file of weightmatrix is not presesnt then throw file not found error and exit the program
////							exit(1);
////			  }
////		 else if(myfile1.eof()==true)
////		  {
////			 cout<<"File with name = "<<argv[3]<<"is empty"<<endl;                        //if file of weightmatrix is empty then throw empty error and exit the program
////			 exit(1);
////		  }
////
////			myfile1>>weights_columns;                          //column of biasmatrix
////
////			myfile1>>weights_rows;                           //row of biasmatrix
////
////		  i=0;
////		  j=0;
////
////
////	vector<float> array2[weights_rows];                         //array with row2 elements of vector
////	  l=0;
////	while(myfile1>>l)
////	{
////	   if(i==weights_rows-1)
////		{
////														 //loop to fill the array2 from myfile1
////		  array2[i].push_back(l);
////			i=0;
////		  continue;
////	   }
////
////	array2[i].push_back(l);
////	i++;
////
////	}
////
////	weights=vector<vector<float>>( weights_rows, vector<float>(weights_columns));
////	for(int i=0;i<weights_rows;i++)
////	{
////	  for(int j=0;j<array2[i].size();j++)
////	  { weights[i][j]=array2[i][j];                         //pushing elements from array3 to weightmatrix vector}
////	   cout<<weights[i][j]<<" ";
////	  }
////	cout<<endl;}
////	myfile1.close();
////
////	myfile2.open(argv[4]);           //opening the file of biasmatrix
////
////
////	 if(!myfile2)
////			  {
////				cout<<"File with name =" <<argv[4]<<" does not Exists"<<endl;  //if file of biasmatrix is not presesnt then throw file not found error and exit the program
////				exit(1);
////			  }
////		 else if(myfile2.eof()==true)
////		  {
////			 cout<<"File with name = "<<argv[4]<<"is empty"<<endl;     //if file of biasmatrix is empty then throw empty error and exit the program
////			 exit(1);
////		  }
////													 //column of biasmatrix
////			myfile2>>bias_columns;
////
////										 //row of biasmatrix
////			myfile2>>bias_rows;
////
////		  i=0;
////		  j=0;
////
////
////	vector<float> array3[bias_rows];                        //array with row3 elements of vector
////	  l=0;
////	while(myfile2>>l)
////	{
////	   if(i==bias_rows-1)
////		{
////												 //loop to fill the array3 from myfile2
////		  array3[i].push_back(l);
////			i=0;
////		  continue;
////	   }
////
////	array3[i].push_back(l);
////	i++;
////
////	}
////
////	bias=vector<vector<float>>( bias_rows, vector<float>(bias_columns));
////	for(int i=0;i<bias_rows;i++)
////	{
////		 for(int j=0;j<array3[i].size();j++)        //pushing elements from array3 to bias vector
////	  { bias[i][j]=array3[i][j];
////		   cout<<bias[i][j]<<" ";
////	  }
////	cout<<endl;
////	}
////	string v=argv[6];
////	//fully_connected_layer(a,weight_matrix,bias_matrix);  //calling fullyconnectedlayer fn
////	cout<<input_rows<<endl;
////	cout<<input_columns<<endl;
////	cout<<weights_rows<<endl;
////	cout<<weights_columns<<endl;
////	cout<<bias_rows<<endl;
////	cout<<bias_columns<<endl;
////
////	output=vector<vector<float>>( bias_rows, vector<float>(bias_columns));
////	if(v=="pthread")
////
////	{fc_layer_fn_with_p_threads(argv[5]);
////	cout<<"DONE";
////	}
//
//	//*********************************ofstream part*********************************************
//
//	}
//
//}


























