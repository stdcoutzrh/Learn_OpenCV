/*
  凸包检测
*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat src = imread("./test_images/tubao.png");
	//imshow("src", src);

	Mat gray,bin; 
	cvtColor(src, gray, CV_BGR2GRAY);
	threshold(gray, bin, 0, 255, THRESH_BINARY);

	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;

	findContours(bin, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	for (size_t i = 0; i < contours.size(); ++i)
	{
		drawContours(src, contours, i, Scalar(0, 255, 0), 2, 8);

		/*
		OpenCV中的凸包寻找算法基于Graham’s扫描法:
			void cv::convexHull(
				InputArray points,
				OutputArray hull,
				bool clockwise = false,
				bool returnPoints = true)

				其中points是输入的轮廓点集
				   hull凸包检测的输出结果
				   当returnPoints为ture的时候返回凸包的顶点坐标是个点集
				     returnPoints为false的是返回的是一个integer的vector里面是凸包各个顶点在轮廓点集对应的index
				   clockwise 表示顺时针方向或者逆时针方向
				   returnPoints表示是否返回点集

		OpenCV中还提供了另外一个API函数用来判断一个轮廓是否为凸包：
			bool cv::isContourConvex(
				InputArray contour)
			只有一个输入参数就是轮廓点集
		*/

		vector<Point> hull;
		convexHull(contours[i], hull);
		bool isHull = isContourConvex(contours[i]);
		cout << isHull << endl;
		
		int len = hull.size();
		for (int j = 0; j < hull.size(); ++j)
		{
			circle(src, hull[j], 4, Scalar(255, 0, 0), 2, 8,0);
			line(src, hull[j%len], hull[(j + 1) % len], Scalar(0, 0, 255), 2, 8, 0);

		}
	}

	imshow("tubao", src);
	waitKey(0);

	return 0;
}