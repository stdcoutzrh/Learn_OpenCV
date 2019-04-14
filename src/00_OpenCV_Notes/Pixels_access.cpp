#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(int argc, char**argv)
{
#if 1
	Mat input_image = imread("./whisper.jpg", 1);
	if (input_image.empty())
	{
		cout << "read input error!" << endl;
		return -1;
	}
	imshow("input", input_image);

	int height = input_image.rows;
	int width = input_image.cols;
	int channel = input_image.channels();

#if 0
	//数组方法遍历
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			if (channel == 3)//彩色图像
			{
				//bgr 是一个vector，包含三个通道的值
				Vec3b bgr = input_image.at<Vec3b>(h, w);
				bgr[0] = 255 - bgr[0];
				bgr[1] = 255 - bgr[1];
				bgr[2] = 255 - bgr[2];
				input_image.at<Vec3b>(h, w) = bgr;
			}
			else if (channel == 1)//灰度图像
			{
				int value = input_image.at<uchar>(h, w);
				input_image.at<uchar>(h, w) = 255 - value;
			}
		}
	}
	imshow("result", input_image);

#endif

#if 0
	//指针方法遍历
	for (int h = 0; h < height; h++)
	{
		uchar* current_row = input_image.ptr<uchar>(h);
		uchar* flag_row =current_row;
		for (int w = 0; w < width; w++)
		{
			int b = 0, g = 0, r = 0;
			if (channel == 3)
			{
				b = *current_row++;
				g = *current_row++;
				r = *current_row++;

				*flag_row++ = 255 - b;
				*flag_row++ = 255 - g;
				*flag_row++ = 255 - r;
			}
			else if (channel == 1)
			{
				int value = *current_row++;
				*flag_row++ = 255 - value;
			}
		}
	}
	imshow("result", input_image);
#endif

#if 1
	//迭代器方法	
	if (channel == 3)
	{
		Mat_<Vec3b>::iterator ite = input_image.begin<Vec3b>(),
			end = input_image.end<Vec3b>();
		
		for (; ite != end; ++ite)
		{
			(*ite)[0] = 255 - (*ite)[0];
			(*ite)[1] = 255 - (*ite)[1];
			(*ite)[2] = 255 - (*ite)[2];
		}
	}
	else if (channel == 1)
	{
		Mat_<uchar>::iterator ite = input_image.begin<uchar>(),
			end = input_image.end<uchar>();
		for (; ite != end; ++ite)
		{
			*ite = 255 - *ite;
		}		
	}

	imshow("result", input_image);

#endif
	
	waitKey(0);
	destroyAllWindows();
#endif

	return 0;
}
