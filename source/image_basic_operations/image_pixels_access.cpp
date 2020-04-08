/*
	指定坐标像素值OP
*/

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main(int argc, char**argv)
{
	Mat input_image = imread("test_images/opencv.jpg", 1);
	if (input_image.empty())
	{
		cout << "read input error!" << endl;
		return -1;
	}
	imshow("input", input_image);

	int height = input_image.rows;
	int width = input_image.cols;
	int channel = input_image.channels();

#if 1
	Mat array_image = input_image.clone();
	double start1 = static_cast<double>(getTickCount());
	//数组方法遍历
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			if (channel == 3)//彩色图像
			{
				//bgr 是一个vector，包含三个通道的值
				Vec3b bgr = array_image.at<Vec3b>(h, w);
				bgr[0] = 255 - bgr[0];
				bgr[1] = 255 - bgr[1];
				bgr[2] = 255 - bgr[2];
				array_image.at<Vec3b>(h, w) = bgr;
			}
			else if (channel == 1)//灰度图像
			{
				int value = array_image.at<uchar>(h, w);
				array_image.at<uchar>(h, w) = 255 - value;
			}
		}
	}

	double end1 = ((double)getTickCount() - start1) / getTickFrequency();
	cout << "array time: " << end1 / 1000 << "ms" << endl;
	imshow("array_image", array_image);

#endif

#if 1
	Mat pointer_image = input_image.clone();
	double start2 = static_cast<double>(getTickCount());
	//指针方法遍历
	for (int h = 0; h < height; h++)
	{
		uchar* current_row = pointer_image.ptr<uchar>(h);
		uchar* flag_row = current_row;
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

	double end2 = ((double)getTickCount() - start2) / getTickFrequency();
	cout << "pointer time: " << end2 / 1000 << "ms" << endl;
	imshow("pointer_image", pointer_image);
#endif

	
#if 1
	Mat iterator_image = input_image.clone();
	double start3 = static_cast<double>(getTickCount());
	//迭代器方法	
	if (channel == 3)
	{
		Mat_<Vec3b>::iterator ite = iterator_image.begin<Vec3b>(),
			end = iterator_image.end<Vec3b>();

		for (; ite != end; ++ite)
		{
			(*ite)[0] = 255 - (*ite)[0];
			(*ite)[1] = 255 - (*ite)[1];
			(*ite)[2] = 255 - (*ite)[2];
		}
	}
	else if (channel == 1)
	{
		Mat_<uchar>::iterator ite = iterator_image.begin<uchar>(),
			end = iterator_image.end<uchar>();
		for (; ite != end; ++ite)
		{
			*ite = 255 - *ite;
		}
	}

	imshow("iterator_image", iterator_image);
	double end3 = ((double)getTickCount() - start3) / getTickFrequency();
	cout<<"iterator time: "<< end3 / 1000 << "ms" << endl;
#endif

	waitKey(0);
	destroyAllWindows();

	return 0;
}