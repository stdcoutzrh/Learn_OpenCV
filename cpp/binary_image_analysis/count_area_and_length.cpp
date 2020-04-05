/*
  轮廓面积与周长计算
*/

#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{

	/*
		对图像二值图像的每个轮廓，我们可以计算轮廓的弧长与面积，
		然后根据轮廓的面积与弧长实现对不同大小对象的过滤，寻找到需要的ROI区域
	*/

	Mat input = imread("./test_images/count_area.png");
	if (input.empty())
	{
		cout << "read image failed." << endl;
		return -1;
	}

	namedWindow("canny", CV_WINDOW_NORMAL);
	namedWindow("contours", CV_WINDOW_NORMAL);

	Mat canny;
	Canny(input, canny, 80, 160, 3,false);
	Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	dilate(canny, canny, k);
	imshow("canny", canny);

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
	
	findContours(canny, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point());
	for (int i = 0; i < contours.size(); ++i)
	{
		/*
		double cv::contourArea(
		InputArray 	contour,
		bool oriented = false)

		基于格林公式计算轮廓的面积
		contour是轮廓点集
		oriented默认是false返回的面积是正数，
		如果方向参数为true表示会根据是顺时针或者逆时针方向
		来返回正值或者负值面积
		*/
		double area = contourArea(contours[i]);

		/*
		double cv::arcLength(
		InputArray curve,
		bool closed)
		计算轮廓曲线的弧长
		curve表示输入的轮廓点集
		closed默认表示是否闭合区域
		*/
		double len = arcLength(contours[i], true);
		if (area < 100 || len < 100)
		{
			continue;
		}

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

		drawContours(input, contours, i, Scalar(0, 0, 255), 2, 8);
	
		//画出最小外接矩形
		RotatedRect rrt = minAreaRect(contours[i]);
		Point2f pt[4];
		rrt.points(pt);

		for (int i = 0; i < 4; i++) {
			line(input,pt[i%4],pt[(i+1)%4], Scalar(255,0,0),2,8,0);
		}
		Point2f cpt = rrt.center;
		circle(input, cpt, 2, Scalar(0, 255, 0), 2, 8, 0);
	}

	imshow("contours", input);
	waitKey(0);
	return 0;
}