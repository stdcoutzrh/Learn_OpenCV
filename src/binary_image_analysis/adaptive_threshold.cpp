#include<iostream>
#include<cmath>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat input = imread("./test_images/text.png");
	if (input.empty())
	{
		cout << "read image failed!" << endl;
		return -1;
	}

	imshow("input", input);

	Mat gray, bin,ostu_bin;

	//bgr 2 gray
	cvtColor(input, gray, CV_BGR2GRAY);

	Mat adaptive;
	/*
		ADAPTIVE_THRESH_GAUSSIAN_C = 1
		ADAPTIVE_THRESH_MEAN_C = 0
	*/
	adaptiveThreshold(gray, adaptive, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 35, 10);

	imshow("adaptive", adaptive);

	/*
		THRESH_BINARY = 0  二值分割		大于阈值的像素赋为255，小于赋为0
		THRESH_BINARY_INV = 1 反向二值分割		大于阈值的像素赋为0，小于阈值为255
		THRESH_TRUNC = 2 截断	高于阈值的像素全赋值为该阈值，低于阈值的赋0
		THRESH_TOZERO = 3 取零		高于阈值的像素保留，低的值赋为零
		THRESH_TOZERO_INV = 4 反向取零	高于阈值的像素赋为零，低的保留
	*/

	//threshold是有一个double类型的返回值的，可以返回OSTU算法得到的阈值
	threshold(gray, ostu_bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("ostu_bin", ostu_bin);

	waitKey(0);

	return 0;
}