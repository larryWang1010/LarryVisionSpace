# -*- coding: utf-8 -*-
"""
Created on Fri Sep 14 14:02:44 2018

@author: zy
"""

'''
特征描述符匹配算法 暴力匹配 KNN匹配 FLANN匹配
'''

import cv2 
import numpy as np

def match_test():
    '''
    暴力匹配 KNN最近邻匹配
    '''
    img1 = cv2.imread('../data/1.png',0)    
    img2 = cv2.imread('../data/2.png',0)
    # img2 = cv2.resize(img2,dsize=(752,480))
    

    '''
    1.使用SIFT算法检测特征点、描述符
    '''
    orb_detector = cv2.ORB_create()
    kp1, des1 = orb_detector.detectAndCompute(img1,None)
    kp2, des2 = orb_detector.detectAndCompute(img2,None)
    #在图像上绘制关键点
    img1 = cv2.drawKeypoints(image=img1,keypoints = kp1,outImage=img1,color=(255,0,255),flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    img2 = cv2.drawKeypoints(image=img2,keypoints = kp2,outImage=img2,color=(255,0,255),flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    #显示图像
    #cv2.imshow('sift_keypoints1',img1)
    #cv2.imshow('sift_keypoints2',img2)
    cv2.waitKey(20)
    
    '''
    2、匹配
    '''
    bf = cv2.BFMatcher()
    knnMatches = bf.knnMatch(des1,des2, k=2) 
    print(type(knnMatches),len(knnMatches),knnMatches[0])
    #获取img1中的第一个描述符在img2中最匹配的一个描述符  距离最小
    dMatch0 = knnMatches[0][0]
    #获取img1中的第一个描述符在img2中次匹配的一个描述符  距离次之
    dMatch1 = knnMatches[0][1]
    print('knnMatches',dMatch0.distance,dMatch0.queryIdx,dMatch0.trainIdx)
    print('knnMatches',dMatch1.distance,dMatch1.queryIdx,dMatch1.trainIdx)
    #将不满足的最近邻的匹配之间距离比率大于设定的阈值匹配剔除。 
    goodMatches = []
    minRatio = 1/3
    for m,n in knnMatches:
        if m.distance / n.distance < minRatio:   
            goodMatches.append([m])
            
    print(len(goodMatches))
    sorted(goodMatches,key=lambda x:x[0].distance)
    #绘制最优匹配点
    outImg = None
    outImg = cv2.drawMatchesKnn(img1,kp1,img2,kp2,goodMatches,outImg,flags=cv2.DRAW_MATCHES_FLAGS_DEFAULT)
    cv2.imshow('matche',outImg)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
    
if __name__ == '__main__':
    match_test()