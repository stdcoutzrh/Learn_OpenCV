#include<opencv2/opencv.hpp>
#include<iostream>
//#include<Windows.h>

using namespace cv;
using namespace std;

int main(int argc, char**argv)
{
	//get gray input image
	Mat input_image = imread("./whisper.jpg", 1);
	if (input_image.empty())
	{
		cout << "read input error!" << endl;
		return -1;
	}
	//imshow("input", input_image);

	int height = input_image.rows;
	int width = input_image.cols;

	//中心点坐标
	int cy = height / 2, cx = width / 2;
	Rect rect(cx - 100, cy - 100, 200, 200);


	//直接赋值与原图中该区域占有同一块内存
	Mat roi_rect = input_image(rect);
	imshow("roi", roi_rect);

#if 0
	//改变ROI则原图也会改变
	roi_rect.setTo(Scalar(0, 0, 255));
	imshow("input", input_image);
	imshow("roi rect", roi_rect);
#endif

#if 1
	//克隆
	Mat roi_rect_copy = roi_rect.clone();
	//改变ROI则原图不会改变
	roi_rect_copy.setTo(Scalar(0, 0, 255));
	imshow("input", input_image);
	imshow("roi rect copy", roi_rect_copy);
#endif


	waitKey(0);
	destroyAllWindows();
	return 0;
}