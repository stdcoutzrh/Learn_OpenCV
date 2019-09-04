#include<iostream>
#include<cmath>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{

	/*
	完整的Canny边缘检测算法包括以下步骤：
	1. 彩色图像转换为灰度图像
	2. 对图像进行高斯模糊
	3. 计算图像梯度，根据梯度计算图像边缘幅值与角度
	4. 非最大信号压制处理（边缘细化）
	5. 双阈值边缘连接处理
	6. 二值化图像输出结果
	*/

	Mat input = imread("./test_images/car.jpg");
	if (input.empty())
	{
		cout << "read image failed!" << endl;
		return -1;
	}
	imshow("input", input);

	Mat gray,canny;

	//bgr 2 gray
	cvtColor(input, gray, CV_BGR2GRAY);

	//canny
	Canny(gray, canny, 100, 300, 3, false);
	imshow("canny", canny);

	waitKey(0);

	return 0;
}