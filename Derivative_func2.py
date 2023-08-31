#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Aug 30 15:37:17 2023

@author: student
"""

import numpy as np
import scipy

def find_slope(point,row):
        diff_y = point[row][1] - point[row+1][1]
        diff_x = point[row][0] - point[row+1][0]
        slope = diff_y/diff_x
        print(slope)
        return slope
        
check_zero = 1
check_true = 0

data = np.genfromtxt('DPV_test(2).csv', delimiter=',', skip_header=1)
num_rows = data.shape[0]
print('Num of rows: ', num_rows)
# Print the loaded data
print(data)


