#include "doublefann.h"
#include "fann_cpp.h"
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace FANN;

//Remember: fann_type is double!
int main(int argc, char** argv) {
	//create a test network: [1,2,1] MLP
	neural_net * net = new neural_net;
	const unsigned int layers[3] = { 1, 3, 1 };
	net->create_standard_array(3, layers);

	//net->create_standard(num_layers, num_input, num_hidden, num_output);

	net->set_learning_rate(0.7f);

	net->set_activation_steepness_hidden(0.7);
	net->set_activation_steepness_output(0.7);

	net->set_activation_function_hidden(SIGMOID_SYMMETRIC_STEPWISE);
	net->set_activation_function_output(SIGMOID_SYMMETRIC_STEPWISE);
	net->set_training_algorithm(TRAIN_QUICKPROP);

	//cout<<net->get_train_error_function()
	//exit(0);
	//test the number 2
	fann_type * testinput = new fann_type;
	*testinput = 2;
	fann_type * testoutput = new fann_type;
	*testoutput = *(net->run(testinput));
	double outputasdouble = (double)*testoutput;
	cout << "Test output: " << outputasdouble << endl;

	//make a training set of x->x^2
	training_data * squaredata = new training_data;
	squaredata->read_train_from_file("trainingdata.txt");

	net->train_on_data(*squaredata, 1000, 100, 0.001);

	net->save("training_float.data");

	cout << endl << "Easy!";

	getchar();
	return 0;
}