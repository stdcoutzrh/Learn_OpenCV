/*
  常用滤波算法
*/

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(int argc, char**argv)
{
	Mat input_image = imread("./flower.jpg", 1);
	if (input_image.empty())
	{
		cout << "read input error!" << endl;
		return -1;
	}
	imshow("input", input_image);
	Mat result;
	//blur(input_image, result, Size(5, 5), Point(-1, -1), 4);
	//GaussianBlur(input_image, result, Size(15,15),15,0, 4);
	medianBlur(input_image, result, 3);
	imshow("result", result);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
