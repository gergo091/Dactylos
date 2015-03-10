#include <iostream>
#include <fstream>
#include "preprocessing.hpp"
#include "processing.hpp"
#include <sstream>
#include <ctime>

#include <math.h>
using namespace std;

int main(){
	srand(0);
	stringstream ss;
	cv::Mat image;
	image = cv::imread("fingerprint.bmp");

	int block = 39;
	int sigma = 8;
	float lambda = 9.0;
	float gamma = 0.75;
	int count = 1;


	Robo::Preprocessing preprocessing(image);
	preprocessing.Segmentation(preprocessing.Get_gray_image());
	preprocessing.OrientationMap(preprocessing.Get_segmentation());

	//	testovanie 1 obrazka
	/*preprocessing.GaborFilter(preprocessing.Get_segmentation(), block, sigma, lambda, gamma);
	cout << "Gabor\n";
	cv::imwrite("Gabor.bmp", preprocessing.Get_gabor_filter());*/
	//	testovanie vela vela obrazkov
	
	//for (int j = 0; j < 4; j++){
		for (int i = 0; i < 16; i++){
			for (int k = 0; k < 15; k++){
				preprocessing.GaborFilter(preprocessing.Get_segmentation(), block, sigma, lambda, gamma);
				ss << "test\\GABOR(sigma=" << sigma << ",lambda=" << lambda << ",gamma=" << gamma << ").bmp";
				cv::imwrite(ss.str(), preprocessing.Get_gabor_filter());
				ss.str("");
				cout << count++ << "test\n";
				sigma++;
			}
			sigma = 8;
			lambda += 0.5;
		}
		//lambda = 8.0;
	//	gamma += 0.25;
	//}
	


	


	//	ostane metody
/*	preprocessing.Binarization(preprocessing.Get_gabor_filter());
	preprocessing.ThinningImage(preprocessing.Get_binarization());
	//preprocessing.CrossingNumber(preprocessing.Get_thinning_image());
	//Robo::Processing processing(preprocessing.Get_thinning_image());
	Robo::Processing processing;

	processing.CrossinNumber(preprocessing.Get_thinning_image());
	processing.Show_markant(preprocessing.Get_thinning_image());
*/
	system("PAUSE");

	cv::waitKey(0);
}