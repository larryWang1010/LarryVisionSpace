"""
Description: 
Author: larry.wang
Date: 2023-07-19 15:20:00
"""
import os
import numpy as np
import pandas as pd

data = pd.read_csv("11.csv", encoding="utf-8")  # 读取csv文件
data_234 = data.iloc[:, 1:3]  # 前3列
data_234 = np.array(data_234)
data_new = data_234


# 传入点云对象
def pointsTopcd(points):
    # 存放路径
    PCD_DIR_PATH = os.path.join(os.path.abspath("."))
    PCD_FILE_PATH = os.path.join(PCD_DIR_PATH, "from_csv.pcd")
    if os.path.exists(PCD_FILE_PATH):
        os.remove(PCD_FILE_PATH)

    # 写文件句柄
    handle = open(PCD_FILE_PATH, "a")

    # 得到点云点数
    point_num = len(data)

    # pcd头部
    handle.write(
        "# .PCD v0.7 - Point Cloud Data file format\nVERSION 0.7\nFIELDS x y z\nSIZE 4 4 4\nTYPE F F F\nCOUNT 1 1 1"
    )
    string = "\nWIDTH " + str(point_num)
    handle.write(string)
    handle.write("\nHEIGHT 1\nVIEWPOINT 0 0 0 1 0 0 0")
    string = "\nPOINTS " + str(point_num)
    handle.write(string)
    handle.write("\nDATA ascii")

    # 依次写入点
    for i in range(point_num):
        # row_data = points[i]
        # print("row data: ",row_data)
        string = (
            "\n" + str(points[i, 1]) + " " + str(points[i, 1]) + " " + str(points[i, 1])
        )
        print("row data: ", string)
        # handle.write(string)
        if i == 10:
            break
    handle.close()


pointsTopcd(data_new)
