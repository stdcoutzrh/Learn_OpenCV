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
	Mat input2 = imread("test_images/cat.jpg", 1);
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

# if 0
	Mat add_result = Mat::zeros(input1.size(), input1.type());
	Mat sub_result = Mat::zeros(input1.size(), input1.type());
	Mat mul_result = Mat::zeros(input1.size(), input1.type());
	Mat div_result = Mat::zeros(input1.size(), input1.type());

	add(input1, input2, add_result);
	subtract(input1, input2, sub_result);
	multiply(input1, input2, mul_result);
	divide(input1, input2, div_result);

	imshow("add_result", add_result);
	imshow("sub_result", sub_result);
	imshow("mul_result", mul_result);
	imshow("div_result", div_result);

#endif

#if 1

	Mat and_, xor_, or_ , not_;
	bitwise_and(input1, input2, and_);
	bitwise_xor(input1, input2, xor_);
	bitwise_or(input1, input2, or_ );
	bitwise_not(input1, not_);

	imshow("and", and_);
	imshow("xor", xor_);
	imshow("or", or_ );
	imshow("not", not_);

#endif

	waitKey(0);
	destroyAllWindows();

	return 0;
}