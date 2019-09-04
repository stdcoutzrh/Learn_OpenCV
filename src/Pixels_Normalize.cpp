#include<opencv2/opencv.hpp>
#include<iostream>
#include<Windows.h>

using namespace cv;
using namespace std;

int main(int argc, char**argv)
{
#if 0
	//get gray input image
	Mat gray_input_image = imread("./whisper.jpg", 0);
	if (gray_input_image.empty())
	{
		cout << "read input error!" << endl;
		return -1;
	}
	imshow("gary_input", gray_input_image);

	//转为32位浮点型
	gray_input_image.convertTo(gray_input_image, CV_32F);

	Mat result = Mat::zeros(gray_input_image.size(), CV_32FC1);
	normalize(gray_input_image, result, 1.0, 0.0, NORM_MINMAX);
	result = result * 255;
	result.convertTo(result, CV_8UC1);
	imshow("result", result);

	waitKey(0);
	destroyAllWindows();
#endif 

	vector<double>a = {20,80,100};
	vector<double>a1(3);
	vector<double>a2(3);
	vector<double>a3(3);
	vector<double>a4(3);
	cv::normalize(a, a1, 1, 0, NORM_L1);
	cv::normalize(a, a2, 1, 0, NORM_L2);
	cv::normalize(a, a3, 1, 0, NORM_INF);
	cv::normalize(a, a4, 1, 0, NORM_MINMAX);

	cout << "L1 normal:" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		cout << a1[i]<<" ";
	}
	cout << endl;

	cout << "L2 normal:" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		cout << a2[i] << " ";
	}
	cout << endl;

	cout << "INF normal:" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		cout << a3[i] << " ";
	}
	cout << endl;

	cout << "MINMAX normal:" << endl;
	for (int i = 0; i < a.size(); i++)
	{
		cout << a4[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}