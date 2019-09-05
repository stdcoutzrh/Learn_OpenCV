#include<opencv2/opencv.hpp>
#include<iostream>
//#include<Windows.h>

using namespace cv;
using namespace std;

int main(int argc, char**argv)
{
	//get input image
	Mat input_image = imread("./whisper.jpg", 1);
	if (input_image.empty())
	{
		cout << "read input error!" << endl;
		return -1;
	}
	imshow("input", input_image);
#if 0
	Mat result_x, result_y, result_xy;

	//沿x轴翻转
	flip(input_image, result_x, 0);
	imshow("result_x", result_x);

	//沿y轴翻转
	flip(input_image, result_y, 1);
	imshow("result_y", result_y);

	//沿xy对角线翻转
	flip(input_image, result_xy, -1);
	imshow("result_xy", result_xy);
#endif

	int height = input_image.rows;
	int width = input_image.cols;
	float fx = 0.0, fy = 0.0;

	Mat result = Mat::zeros(input_image.size(), input_image.type());

	resize(input_image, result, Size(width * 2, height * 2), fx = 0, fy = 0, INTER_NEAREST);
	imshow("INTER_NEAREST", result);

	resize(input_image, result, Size(width * 2, height * 2), fx = 0, fy = 0, INTER_LINEAR);
	imshow("INTER_LINEAR", result);

	resize(input_image, result, Size(width * 2, height * 2), fx = 0, fy = 0, INTER_CUBIC);
	imshow("INTER_CUBIC", result);

	resize(input_image, result, Size(width * 2, height * 2), fx = 0, fy = 0, INTER_LANCZOS4);
	imshow("INTER_LANCZOS4", result);


	waitKey(0);
	destroyAllWindows();
	//system("pause");
	return 0;
}