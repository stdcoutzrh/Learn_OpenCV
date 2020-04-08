import cv2 as cv
import numpy as np 

# 以单通道方式读取图片
input = cv.imread("./test_images/opencv.jpg",1)

shape = input.shape
print(shape)

for row in range(shape[0]):
    for col in range(shape[1]):
        if len(shape)==3 and shape[2]==3: #RGB
            b,g,r = input[row,col]
            b = 255-b
            g = 255-g 
            r = 255-r
            input[row,col] = [b,g,r]
        elif len(shape)==2 : #灰度图
            input[row,col] = 255-input[row,col]

cv.imshow("access",input)
cv.waitKey(0)
cv.destroyAllWindows()