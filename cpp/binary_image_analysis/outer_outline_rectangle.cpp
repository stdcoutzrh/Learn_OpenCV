/*
  轮廓外接矩形
*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	Mat input = imread("./test_images/tubao.png");
	if (input.empty())
	{
		cout << "read image failed." << endl;
		return -1;
	}

	namedWindow("binary", CV_WINDOW_NORMAL);
	namedWindow("rect", CV_WINDOW_NORMAL);

	Mat gray,binary;
	cvtColor(input, gray, CV_BGR2GRAY);
	threshold(gray,binary,0,255,THRESH_BINARY);
	imshow("binary", binary);


	/*
		void cv::findContours(
					InputOutputArray image,
					OutputArrayOfArrays contours,
					OutputArray hierarchy,
					int mode,
					int method,
					Point offset = Point())

		其中Image是输入图像，必须是二值图像（二值图像可以threshold输出、Canny输出、inRange输出、自适应阈值输出等）
			Contours获取的轮廓，每个轮廓是一系列的点集合
			Hierarchy轮廓的层次信息，每个轮廓有四个相关信息，分别是同层下一个、前一个、第一个子节点、父节点
			mode 表示轮廓寻找时候的拓扑结构返回
				-RETR_EXTERNAL表示只返回最外层轮廓
				-RETR_TREE表示返回轮廓树结构
			Method表示轮廓点集合取得是基于什么算法，常见的是基于CHAIN_APPROX_SIMPLE链式编码方法
	*/

	vector<vector<Point>> contours;
	vector<Vec4i>hierarchy;	
	findContours(binary, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	
	for (int i = 0; i < contours.size(); ++i)
	{

		/*
		对于得到轮廓，可以通过下面的API绘制每个轮廓
			void cv::drawContours(
						InputOutputArray image,
						InputArrayOfArrays contours,
						int contourIdx,
						const Scalar & 	color,
						int thickness = 1,
						int lineType = LINE_8,
						InputArray 	hierarchy = noArray(),
						int maxLevel = INT_MAX,
						Point offset = Point())

			当thickness为正数的时候表示绘制该轮廓
			当thickness为-1表示填充该轮廓
		*/

		drawContours(input, contours, i, Scalar(0, 0, 255), 3, 8);
		
		//最大外接轮廓
		Rect rect = boundingRect(contours[i]);
		rectangle(input, rect, Scalar(255, 0, 0), 3, 8);

		//最小外接轮廓
		RotatedRect rrt = minAreaRect(contours[i]);
		Point2f pt[4];
		rrt.points(pt);
		for (int j = 0; j < 4; ++j)
		{
			line(input, pt[j % 4], pt[(j + 1) % 4], Scalar(0, 255, 0), 3, 8, 0);
		}
		
		//轮廓重心
		Point2f center = rrt.center;
		circle(input, center, 2, Scalar(0, 255, 0), 2, 8, 0);	
	}

	imshow("rect", input);
	waitKey(0);
	return 0;
}