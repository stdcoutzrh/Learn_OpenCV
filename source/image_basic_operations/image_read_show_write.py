import cv2 as cv
import numpy as np 

# 以单通道方式读取图片
input = cv.imread("./test_images/opencv.jpg",0)

#创建一个名为input的窗口并在其中显示读入的图片
cv.namedWindow("input",cv.WINDOW_NORMAL)
cv.imshow("input", input)
cv.waitKey(0)

#将读取到的图片保存成jpg格式
cv.imwrite("gray_input.jpg", input)

#销毁窗口
cv.destroyAllWindows()