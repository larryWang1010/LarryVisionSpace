#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt

import argparse
import pandas as pd
import os.path as path
import sys

def argParser():
    parser = argparse.ArgumentParser(
        description="Be used to analyse result slam result."
    )
    parser.add_argument("--path_csv", help="csv path", default=" ")
    parser.add_argument("--path_txt", help="txt path", default=" ")
    parser.add_argument("--save_dir", help="save result dir", default="./result")
    parser.add_argument("--show", help="visualization", default=True)

    args = parser.parse_args()
    return args

def read_csv(path_csv, save_dir, show=True):
    first_line = True
    v_xyz = []
    with open(path_csv) as file:
        lines = file.readlines()
        for line in lines:
            if first_line == True:
                first_line = False
                continue
            v_xyz.append(line.split(',')[1:4])
    file.close()
    # draw
    v_float = np.array(v_xyz, dtype=float)
    if len(v_float) == 0:
        return 0
    x_time = []
    for i in range(len(v_float[:,0])):
        x_time.append(i)
    
    fig1, ax1 = plt.subplots(3,1)
    ax1[0].plot(x_time, v_float[:,0],label='vx')
    ax1[1].plot(x_time, v_float[:,1],label='vy')
    ax1[2].plot(x_time, v_float[:,2],label='vz')

    ax1[0].set_title('v_x_y_z')

    plt.legend()
    plt.grid()
    plt.draw()

    if save_dir != ' ':
        save_file = path.join(save_dir, 'result_csv.png')
        plt.savefig(save_file)
    if(show):
        plt.show()
# orb_traj
def read_txt(path_txt,save_dir,show=True):
    v_xyz = []
    with open(path_txt) as file:
        lines = file.readlines()
        for line in lines:
            v_xyz.append(line.split(' ')[1:4])
    file.close()
    # draw
    v_float = np.array(v_xyz, dtype=float)
    if len(v_float) == 0:
        return 0
    x_time = []
    for i in range(len(v_float[:,0])):
        x_time.append(i)
    
    fig1, ax1 = plt.subplots(3,1)
    ax1[0].plot(x_time, v_float[:,0],label='vx')
    ax1[1].plot(x_time, v_float[:,1],label='vy')
    ax1[2].plot(x_time, v_float[:,2],label='vz')

    ax1[0].set_title('v_x_y_z')

    plt.legend()
    plt.grid()
    plt.draw()

    if save_dir != ' ':
        save_file = path.join(save_dir, 'result_txt.png')
        plt.savefig(save_file)
    if(show):
        plt.show()

if __name__ == "__main__":
    args = argParser()
    if not (path.exists(args.path_csv)):
        print("Error,", args.path_csv, "doesn't exists!")
        sys.exit(1)
    read_txt(args.path_txt, args.save_dir)
    read_csv(args.path_csv, args.save_dir)
