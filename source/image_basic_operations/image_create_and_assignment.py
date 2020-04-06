import cv2 as cv
import numpy as np 

# 以单通道方式读取图片
input = cv.imread("./test_images/opencv.jpg",0)

# 克隆图像
clone_image = np.copy(input)

# 赋值
ass_image = input

# 创建空白图像
em_image = np.zeros(input.shape,input.dtype)

# 创建矩阵

kernel = np.array([[0, -1, 0],[-1, 5, -1],[0, -1, 0]])
print(kernel.shape)