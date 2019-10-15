/*
	OpenCV中像素算术操作与逻辑操作
*/

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(int argc, char**argv)
{
	Mat input1 = imread("test_images/opencv.jpg", 1);
	if (input1.empty())
	{
		cout << "read input failed!" << endl;
		return -1;
	}
	Mat input2 = imread("test_images/objs.jpg", 1);
	if (input2.empty())
	{
		cout << "read input failed!" << endl;
		return -1;
	}
	
	//将两个图片resize到同样大小
	resize(input1, input1, Size(400, 300));
	resize(input2, input2, Size(400, 300));
	imshow("input1", input1);
	imshow("input2", input2);

	Mat add_result = Mat::zeros(input1.size(), input1.type());
	Mat sub_result = Mat::zeros(input1.size(), input1.type());
	Mat	mul_result = Mat::zeros(input1.size(), input1.type());
	Mat	div_result = Mat::zeros(input1.size(), input1.type());
	
	//算数操作： 加add、减subtract、乘multiply、除divide

	/*
		饱和运算，即大于等于255的时候取255，小于等于0的时候取0
		saturate_cast<uchar>(a)； 对a进行上述的溢出保护
	*/

	add(input1, input2, add_result);
	subtract(input1, input2, sub_result);
	multiply(input1, input2, mul_result);
	divide(input1, input2, div_result);

	/*
	 像素的逻辑操作
		对两张图像的操作：
			与操作：bitwise_and
			异或操作：bitwise_xor
			或操作：bitwise_or
		针对输入图像的操作：
			取非操作：bitwise_not
	*/

	Mat and, xor, or, not;
	bitwise_and(input1, input2, and);
	bitwise_xor(input1, input2, xor);
	bitwise_or(input1, input2, or);
	bitwise_not(input1, not);

	imshow("and", and);
	imshow("xor", xor);
	imshow("or", or);
	imshow("not", not);

	waitKey(0);
	destroyAllWindows();

	return 0;
}
