# generate point set instances for the Ospanner project
# DIMACS-style format 
# c command line, human-readable information, generation configuration
# p problem line, specifying the type and the size   
# Description lines <x> <y> <w> 
#models:
## unit distance
## exp. distance
## mixed 
import pathlib

import matplotlib as mpl
import matplotlib.pyplot as plt


import tools
import os
import numpy as np
import branch_gen
import networkx as nx
import re
nt_data_path = 'D:/GIT/2Page/tmp'
valid_combine = set()
valid_combine_final = set([68, 71, 135, 167, 236, 266, 268, 332, 399, 400, 530, 596, 662, 728, 827, 894, 926, 1026, 1027, 1126, 1128, 1129, 1389, 1393, 1455, 1587, 1653, 1719, 1786, 1818, 1884, 1983])
def get_combines(line):
     numbers = [int(s) for s in line.split()]
     assert(numbers[0] < 0)
     if(numbers[1] < 0):
        return
     numbers[0] = -numbers[0]
     if valid_combine_final.__contains__(numbers[1]) or valid_combine_final.__contains__(numbers[2]) :
        if valid_combine.__contains__(numbers[0]):
            valid_combine_final.add(numbers[0])
        valid_combine.add(numbers[0])
def check_valid(line):
    numbers = [int(s) for s in line.split()]
    for n in numbers:
        if valid_combine_final.__contains__(n):
            return True
    print(line)
    return False

    '''
    with  open('D:/GIT/2Page/tmp/uniform_1_32_8.txt_1.338235_DIMACS.txt') as f:
    '''
if __name__ == "__main__":
    with  open('D:/GIT/2Page/tmp/uniform_1_32_8.txt_1.337662_DIMACS.txt') as f:
        Lines = f.readlines()
        for line in Lines:
            if line.startswith("c"):
                continue
            if line.startswith("-"):
                get_combines(line)
                continue
        print(valid_combine_final)
        for line in Lines:
            if line.startswith("c") or line.startswith("-"):
                continue
            assert(check_valid(line))

