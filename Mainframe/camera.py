# -*- coding:utf-8 -*-

import cv2
import numpy as np
from urllib import request

url = "http://192.168.3.170:8080/?action=snapshot"

def downloadImg():
    global url
    with request.urlopen(url) as f:
        data = f.read()
        img1 = np.frombuffer(data, np.uint8)
        #print("img1 shape ", img1.shape) # (83653,)
        img_cv = cv2.imdecode(img1, cv2.IMREAD_ANYCOLOR)
        return img_cv

while True:
    # image = downloadImg() 
    image = downloadImg() #cv2.imread('1.jpg') # 根据路径读取一张图片
    #cv2.imshow("frame", image)
    #dst = cv2.cvtColor(image, cv2.COLOR_BGR2HSV) # BGR转HSV
    cv2.imshow('output', image)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    
cv2.destroyAllWindows()
