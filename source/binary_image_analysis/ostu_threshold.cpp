/*
  OSTU阈值二值化
*/

#include<iostream>
#include<cmath>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat input = imread("./test_images/connect.png");
	if (input.empty())
	{
		cout << "read image failed!" << endl;
		return -1;
	}

	namedWindow("input", CV_WINDOW_NORMAL);
	namedWindow("basic_bin", CV_WINDOW_NORMAL);
	namedWindow("ostu_bin", CV_WINDOW_NORMAL);
	imshow("input", input);

	Mat blur,gray, bin,ostu_bin;

	//blur
	//pyrMeanShiftFiltering(input_img, input_img, 10, 100);
	GaussianBlur(input, blur, Size(7, 7), 10);

	//bgr 2 gray
	cvtColor(blur, gray, CV_BGR2GRAY);

	/*
	THRESH_BINARY = 0  二值分割		大于阈值的像素赋为255，小于赋为0
	THRESH_BINARY_INV = 1 反向二值分割		大于阈值的像素赋为0，小于阈值为255
	THRESH_TRUNC = 2 截断	高于阈值的像素全赋值为该阈值，低于阈值的赋0
	THRESH_TOZERO = 3 取零		高于阈值的像素保留，低的值赋为零
	THRESH_TOZERO_INV = 4 反向取零	高于阈值的像素赋为零，低的保留
	*/
	
	//gray 2 binary
	threshold(gray, bin, 0, 255, THRESH_BINARY );
	//threshold是有一个double类型的返回值的，可以返回OSTU算法得到的阈值
	threshold(gray, ostu_bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("basic_bin", bin);
	imshow("ostu_bin", ostu_bin);

	waitKey(0);

	return 0;
}