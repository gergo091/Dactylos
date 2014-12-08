#include <fann.h>
#include "floatfann.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{

	const unsigned int num_input = 25;
	const unsigned int num_output = 3;
	const unsigned int num_layers = 4;
	const unsigned int num_neurons_hidden1 = 15;
	const unsigned int num_neurons_hidden2 = 10;
	const float desired_error = (const float) 0.001;
	const unsigned int max_epochs = 500000;
	const unsigned int epochs_between_reports = 1;

	struct fann *ann = fann_create_standard(num_layers, num_input,
		num_neurons_hidden1, num_neurons_hidden2, num_output);

	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);
	//fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

	fann_train_on_file(ann, "sample.data", max_epochs,
		epochs_between_reports, desired_error);

	fann_save(ann, "sample_float.net");

	fann_destroy(ann);

	system("PAUSE");

	fstream myfile("data1.txt", ios_base::in);
	vector<fann_type> fileInput;

	
	float a;
	while (myfile >> a)
	{
		fileInput.push_back(a);
	}
	fann_type input[25];
	for (int i = 0; i < fileInput.size(); i++)
		input[i] = fileInput.at(i);

	struct fann *test_ann = fann_create_from_file("sample_float.net");
	float *output = fann_run(test_ann, input);
	//for (int i = 0; i < 10; i++)
	cout << "1: " << output[0] << "2: " << output[1] << "3: " << output[2] << endl;
	

	fann_destroy(test_ann);


	system("PAUSE");
	return 1;
}
