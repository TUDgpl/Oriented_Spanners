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
nt_data_path = 'D:/GIT/OriSpannerP/instances_32'
#instance_sizes = [4, 8, 16,32,64,128,256,512,1024,2048]
instance_sizes = [32]
#instance_sizes = [9, 17]
alpha = 1.3803
W = 100000
H = 100000

instance_number = 1
instance_number_random = 50000

# main function







if __name__ == "__main__":    
    if os.name == 'nt':
        data_path = pathlib.Path( nt_data_path )
        uniform_1d_folder = data_path
        unit_1d_folder = data_path/'1D'/'Unit'
        mixed_1d_folder = data_path/'1D'/'Mixed'
        exp_1d_folder = data_path/'1D'/'Exp'
        # the frac folder
        uniform_1d_folder_frac = data_path/'1D'/'Uniform_Frac'
        unit_1d_folder_frac = data_path/'1D'/'Unit_Frac'
        mixed_1d_folder_frac = data_path/'1D'/'Mixed_Frac'
        exp_1d_folder_frac = data_path/'1D'/'Exp_Frac'



    for instance_size in instance_sizes:
            branch_gen.generate_branch( tools.Model.UNIFORM, 1,  uniform_1d_folder, instance_size, instance_number_random, W, H)
            #branch_gen.generate_branch( tools.Model.UNIT,1, unit_1d_folder, instance_size, instance_number, W, H)
            #branch_gen.generate_branch( tools.Model.MIXED, 1,  mixed_1d_folder, instance_size, instance_number, W, H)
            #branch_gen.generate_branch( tools.Model.EXP, 1,  exp_1d_folder, instance_size, instance_number, W, H,alpha)

        # the frac folder
            '''
            branch_gen.generate_branch( tools.Model.UNIFORM_FRAC, 1,  uniform_1d_folder_frac, instance_size, instance_number, W, H)
            branch_gen.generate_branch( tools.Model.UNIT_FRAC,1, unit_1d_folder_frac, instance_size, instance_number, W, H)
            branch_gen.generate_branch( tools.Model.MIXED_FRAC, 1,  mixed_1d_folder_frac, instance_size, instance_number, W, H)
            branch_gen.generate_branch( tools.Model.EXP_FRAC, 1,  exp_1d_folder_frac, instance_size, instance_number, W, H,alpha)
            '''