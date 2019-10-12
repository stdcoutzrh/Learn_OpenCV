#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	/* 相关API介绍：
		CV_EXPORTS_W void cvtColor( InputArray src, OutputArray dst, int code, int dstCn=0 );
			* src是源图像，可以是8位无符号或16位无符号数或单精度浮点数
			* dst是输出图像，与src具有相同大小和深度
			* code是色彩空间转换类型，常用参数如下：
				COLOR_BGR2GRAY = 6 彩色到灰度
				COLOR_GRAY2BGR = 8 灰度到彩色
				COLOR_BGR2HSV = 40 BGR到HSV
				COLOR_HSV2BGR = 54 HSV到 BGR
				更加详细的色彩空间转换类型见：	https://docs.opencv.org/4.1.2/d8/d01/group__imgproc__color__conversions.html#ga4e0972be5de079fed4e3a10e24ef5ef0
	*/

	Mat input = imread("test_images/opencv.jpg",1);
	namedWindow("input", CV_WINDOW_NORMAL);
	imshow("input", input);

	Mat gray, hsv;
	cvtColor(input, gray, COLOR_BGR2GRAY);
	cvtColor(input, hsv, COLOR_BGR2HSV);

	imshow("gray", gray);
	imshow("hsv", hsv);

	waitKey(0);
	return 0;
}