/*
  画标签，本质就是像素值操作
*/

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

void draw_box_arr(Mat& image, Point p1, Point p2, int color[3], int width);
void draw_label(Mat& image, Point p1, int color[3],String s);

int main(int argc, char**argv)
{
	Mat input_image = imread("./whisper.jpg", 1);
	if (input_image.empty())
	{
		cout << "read input error!" << endl;
		return -1;
	}

	Point p1(90, 150);
	Point p2(250, 350);

	int color[3] = { 0,255,0 };
	draw_label(input_image,p1, color,"flower");
	draw_box_arr(input_image, p1, p2, color, 2);
	cv::imshow("result", input_image);
	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}

void draw_box_arr(Mat& image, Point p1, Point p2, int color[3], int width)
{
	if (image.channels() == 1)
	{
		cvtColor(image, image, COLOR_GRAY2BGR);
	}
	for (int h = p1.x; h <= p1.x + width; ++h)
	{
		for (int w = p1.y; w < p2.y; ++w)
		{
				Vec3b bgr = image.at<Vec3b>(h, w);
				bgr[0] = color[0];//b
				bgr[1] = color[1];//g
				bgr[2] = color[2];//r
				image.at<Vec3b>(h, w) = bgr;
		}
	}
	for (int h = p1.x+width; h <= p2.x-width; ++h)
	{
		for (int w = p1.y; w < p1.y+width; ++w)
		{
				Vec3b bgr = image.at<Vec3b>(h, w);
				bgr[0] = color[0];//b
				bgr[1] = color[1];//g
				bgr[2] = color[2];//r
				image.at<Vec3b>(h, w) = bgr;
		}
	}
	for (int h = p2.x-width; h <= p2.x ; ++h)
	{
		for (int w = p1.y; w < p2.y; ++w)
		{
				Vec3b bgr = image.at<Vec3b>(h, w);
				bgr[0] = color[0];//b
				bgr[1] = color[1];//g
				bgr[2] = color[2];//r
				image.at<Vec3b>(h, w) = bgr;
		}
	}
	for (int h = p1.x+width; h <= p2.x - width; ++h)
	{
		for (int w = p2.y-width; w < p2.y; ++w)
		{
				Vec3b bgr = image.at<Vec3b>(h, w);
				bgr[0] = color[0];//b
				bgr[1] = color[1];//g
				bgr[2] = color[2];//r
				image.at<Vec3b>(h, w) = bgr;
		}
	}
}

void draw_label(Mat& image, Point p, int color[3],String s)
{
	//lable size:30 x slen*20+5
	int l_w = s.length() * 20 + 5;
	int l_h = 30;
	for (int h = p.x - l_h; h < p.x; h++)
	{
		uchar* current_row = image.ptr<uchar>(h);
		int x = p.y;
		while (x--!=0)
		{
			current_row++;
			current_row++;
			current_row++;
		}
		for (int w = p.y; w < p.y + l_w; w++)
		{
			*current_row++ = color[0];
			*current_row++ = color[1];
			*current_row++ = color[2];
		}
	}
	putText(image, s, Point(p.y+5,p.x-5), 2, 1, (0, 0, 0), 1, 4);
}
