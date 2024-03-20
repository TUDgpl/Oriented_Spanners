import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import math
from enum import Enum
from fractions import Fraction
import glob
import os
import re
import numpy as np



sizes = ["16", "32", "64", "128", "256", "512"]

def get_ori(file_path):
    o = str(file_path).split("/")[-1]
    if(o.endswith("dp.txt")):
        solver = Solver.DP
        length = Length.l_u.value
    if(o.endswith("sat.txt")):
        solver = Solver.SAT2
        length = Length.l_u.value
    if(o.endswith("sat_2.txt")):
        solver = Solver.SAT2
        length = Length.l_2.value
    if(o.endswith("sat_3.txt")):
        solver = Solver.SAT2
        length = Length.l_3.value
    if(o.endswith("sat_4.txt")):
        solver = Solver.SAT2
        length = Length.l_4.value
    if(o.endswith("sat_5.txt")):
        solver = Solver.SAT2
        length = Length.l_5.value
    if(o.endswith("sat_6.txt")):
        solver = Solver.SAT2
        length = Length.l_6.value
    if(o.endswith("sat_7.txt")):
        solver = Solver.SAT2
        length = Length.l_7.value
    if(o.endswith("sat_8.txt")):
        solver = Solver.SAT2
        length = Length.l_8.value
    if(o.endswith("sat_9.txt")):
        solver = Solver.SAT2
        length = Length.l_9.value
    if(o.endswith("sat_10.txt")):
        solver = Solver.SAT2
        length = Length.l_10.value
    if(o.endswith("sat_11.txt")):
        solver = Solver.SAT2
        length = Length.l_11.value
    if(o.endswith("sat_12.txt")):
        solver = Solver.SAT2
        length = Length.l_12.value
    if(o.endswith("sat_13.txt")):
        solver = Solver.SAT2
        length = Length.l_13.value
    if(o.endswith("sat_14.txt")):
        solver = Solver.SAT2
        length = Length.l_14.value
    if(o.endswith("sat_15.txt")):
        solver = Solver.SAT2
        length = Length.l_15.value
    if(o.endswith("sat_16.txt")):
        solver = Solver.SAT2
        length = Length.l_16.value
    if(o.endswith("sat_17.txt")):
        solver = Solver.SAT2
        length = Length.l_17.value
    if(o.endswith("sat_18.txt")):
        solver = Solver.SAT2
        length = Length.l_18.value
    if(o.endswith("sat_19.txt")):
        solver = Solver.SAT2
        length = Length.l_19.value
    if(o.endswith("sat_20.txt")):
        solver = Solver.SAT2
        length = Length.l_20.value
    if(o.startswith("uniform_16")):
        size = Sizes.S_16.value
    if(o.startswith("uniform_32")):
        size = Sizes.S_32.value
    if(o.startswith("uniform_64")):
        size = Sizes.S_64.value
    if(o.startswith("uniform_128")):
        size = Sizes.S_128.value
    if(o.startswith("uniform_256")):
        size = Sizes.S_256.value
    if(o.startswith("uniform_512")):
        size = Sizes.S_512.value
    with open(file_path) as my_file:
        F = my_file.read()
        if 'error' in F:
            return False, solver, length, Fraction(6,1), size    
        num = F.split(" ")
        i = 0
        for ph in num:
            if "with" in ph:
                break
            i+= 1
        n =int(num[i+1].split(",")[0])
        d = int(num[i+2].split("{")[0].split("H")[0])
    

    #length
    #solver, length, dilation, size
    #return float(o[-1].replace('\'', ''))

    return True, solver, length, Fraction(n,d), size

def parse(r):
    x = r.split("_")
    return  x[2]
def round_down(v):
    return math.floor(v * 1000)/1000.0


def draw_short_edges(results):
    df = pd.DataFrame(columns=['number of points (n)', 'dilation', 'length'])
    i = 2
    results_f = [resukts_2p_2l, resukts_2p_3l, resukts_2p_4l, resukts_2p_5l]
    for res in results:
        for r in res:
            b = parse(r)
            c = results.get(r)
            df.loc[i] = b, c, i
        i = i+1
    sns.set_style("whitegrid")
    fg =sns.boxplot(data=df, x="number of points (n)", y="dilation", hue="length")
    ax = plt.gca()
    plt.close()

def get_table(df):
    means = []
    maxes_f = []
    maxes = []
    for size in Sizes:
        df_one_s = df[df['Size'] == size.value]
        maxes_f.append(df_one_s['Dilation'].max())
        maxes.append(round_down(df_one_s['Dilation'].max()))
        means.append(round_down(df_one_s['Dilation'].mean()))
    print(means)
    print( maxes_f)
    print(maxes)

def get_box_plot(df, x_label, y_label, file_name, y_col, x_col, order_list):
    font = {'family' : 'Times New Roman',
            'weight' : 'normal',
            'size'   : 18}
    plt.rc('font', **font)
    df = df[[x_col, y_col]]
    Col_dilation_floating = df['Dilation']
    Col_dilation_floating = Col_dilation_floating.apply(round_down)
    df['Dilation'] = Col_dilation_floating
    sns.set_style("whitegrid")   
    fg =sns.boxplot(data=df, x=x_col, y=y_col, order=order_list)
    ax = plt.gca()
    ax.set(xlabel=x_label, ylabel=y_label)
    plt.tight_layout()
    plt.savefig(file_name, dpi=600)
    plt.close()

def draw_maxes(df, file_name,  x_label, y_label,x_col, y_col,order_list):
    get_table(df)
    get_box_plot(df, x_label, y_label, file_name, x_col, y_col, order_list)





class Solver( Enum ):
    DP = "uniform"
    SAT2 = "sat_2"

class Sizes( Enum ):
    S_16 = 16
    S_32 = 32
    S_64 = 64
    S_128 = 128
    S_256 = 256
    S_512 = 512

class Length(Enum):
    l_2 = 2
    l_3 = 3
    l_4 = 4
    l_5 = 5
    l_6 = 6
    l_7 = 7
    l_8 = 8
    l_9 = 9
    l_10 = 10
    l_11 = 11
    l_12 = 12
    l_13 = 13
    l_14 = 14
    l_15 = 15
    l_16 = 16
    l_17 = 17
    l_18 = 18
    l_19 = 19
    l_20 = 20
    l_u = "ul"

solution_path  = "D:/GIT/OriSpanner/solutions/"
def test_hyp(df_sat_single, s):
    c_list = ['File', 'Dilation_21']
    cc_list = []
    df_sat_single_unlimited = df_sat_single[ df_sat_single["Length"] == Length.l_u.value]
    df_sat_single_unlimited = df_sat_single_unlimited[['File', 'Dilation']]
    df_sat_single_unlimited = df_sat_single_unlimited.rename(columns={"File": "File", "Dilation":"Dilation_21"})
    for l in range(20,1, -1):
        df_sat_single_short = df_sat_single[ df_sat_single["Length"] == l]
        df_sat_single_short = df_sat_single_short[['File', 'Dilation']]
        dilation_l = "Dilation_" + str(l)
        df_sat_single_short = df_sat_single_short.rename(columns={"File": "File", "Dilation": dilation_l})
        df_sat_single_unlimited = pd.merge(df_sat_single_unlimited, df_sat_single_short, on="File")

    # add
        # add
    for i in range(2, 21):
        col_name  = "count_"+ str(i)     
        c_list.append(col_name)
        dilation_l = "Dilation_" + str(i)
        dilation_ll = "Dilation_" + str(i+1)
        print(dilation_l)
        df_sat_single_unlimited[col_name] = np.where(df_sat_single_unlimited[dilation_ll] <= df_sat_single_unlimited[dilation_l], 
                                              df_sat_single_unlimited[dilation_l] ==df_sat_single_unlimited["Dilation_21"], "Error")
        col_name_count = col_name+"_c"
        cc_list.append(col_name_count)
        df_sat_single_unlimited[col_name_count] = df_sat_single_unlimited[col_name].apply(lambda x: 1 if x == "True" else 0)
    file_name = "debug" + str(s)+".csv"
    c_list.extend(cc_list)
    print(c_list)
    df_sat_single_unlimited.to_csv(file_name, columns=c_list)
    

def get_plots(df):
    df_sat_all = df[df["Solver"] == Solver.SAT2]
    df_sat = df_sat_all[ df_sat_all["Length"] == Length.l_u.value ]

    # 1-page data
    df_dp = df[df["Solver"] == Solver.DP]
    print("The values of 1-Page:")
    #draw_maxes(df_dp, "D:/GIT/OriSpannerP/plots/1page_random_lowerbound_box.pdf", "number of points (n)", "dilations" , 'Dilation', 'Size',[16,32,64,128,256,512])
    # 2-page data

    print("The values of 2-Page:")
    #draw_maxes(df_sat, "D:/GIT/OriSpannerP/plots/2page_random_lowerbound_box.pdf", "number of points (n)", "dilations", 'Dilation', 'Size', [16,32,64,128,256,512])
    
    # sat short
    for s in [16,32,64,128,256,512]:
        df_sat_single = df_sat_all[ df_sat_all["Size"] == s ]
        test_hyp(df_sat_single, s)
        plot_file = "D:/GIT/OriSpannerP/plots/short_edges_" + str(s) + ".pdf"
        get_box_plot(df_sat_single, "edge distance", "dilations", plot_file, 'Dilation', 'Length', [3,4,5,6,7,8,"ul"])
  

from matplotlib.font_manager import findfont, FontProperties


def get_max(df_one):
    df = df_one
    Col_dilation_floating = df['Dilation']
    Col_dilation_floating = Col_dilation_floating.apply(round_down)
    df['Dilation'] = Col_dilation_floating
    print(df.loc[df['Dilation'].idxmax()])
def get_filies(df):
    df_sat1= df[df["Solver"] == Solver.DP]
    get_max(df_sat1)
    df_sat_all = df[df["Solver"] == Solver.SAT2]
    df_sat = df_sat_all[ df_sat_all["Length"] == Length.l_u.value ]
    get_max(df_sat)

def test():
    font = findfont(FontProperties(family=['serif']))
    solvers = []
    lengths = []
    dilations = []
    sizes = []
    file_names = []
    for item in os.listdir(solution_path):
        item = os.path.join(solution_path, item)
        if os.path.isdir(item):
            for solution in os.listdir(item):
                file_path = os.path.join(item, solution)
                real_solution, solver, length, dilation, size = get_ori(file_path)
                if(real_solution):
                    file_names.append(solution.split(".")[0])
                    solvers.append(solver)
                    lengths.append(length)
                    dilations.append(dilation)
                    sizes.append(size)
    dict ={'Solver':solvers, 'Length': lengths, 'Dilation':dilations, "Size":sizes, "File": file_names}            
    # full data
    df = pd.DataFrame(dict)
    get_plots(df)
    get_filies(df)

import pandas as pd
if __name__ == "__main__":  

    r1 =[2,0.01,	0,	0,	0,	0,	0]
    r2= [3,0.91,	0.93, 0.83,	0.72, 0.7,	0.468]
    r3 =[4,1,	1,	1,	1, 0.99,	0.962]
    r4=[5,1,	1,	1,	1, 0.99,	0.974]
    r5 =[6,1,	1,	1,	1, 0.99,	0.987]
    r6 =[7, 1,	1,	1,1,	1,	1,]
    r = [ r1, r2,r3,r4,r5, r6]
    df = pd.DataFrame(r ,columns = ['x', '16', '32', '64', '128', '256', '512'])
    print(df)
    #test()

    '''
    df = pd.read_csv('unlimited.csv')
    matched_values = df['Dilation'][df['Dilation']==df['Dilation']].values
    print(matched_values)
    '''

    
    # Make a data frame
    #df=pd.DataFrame({'x': range(1,11), 'y1': np.random.randn(10), 'y2': np.random.randn(10)+range(1,11), 'y3': np.random.randn(10)+range(11,21), 'y4': np.random.randn(10)+range(6,16), 'y5': np.random.randn(10)+range(4,14)+(0,0,0,0,0,0,0,-3,-8,-6), 'y6': np.random.randn(10)+range(2,12), 'y7': np.random.randn(10)+range(5,15), 'y8': np.random.randn(10)+range(4,14), 'y9': np.random.randn(10)+range(4,14), 'y10': np.random.randn(10)+range(2,12) })
    
    print(df)
    
    # Create a color palette
    palette = plt.get_cmap('Dark2')
    
    # Plot multiple lines
    num=0
    for column in df.drop('x', axis=1):
        num+=1
        plt.plot(df['x'], df[column], marker='', color=palette(num), linewidth=1, alpha=0.9, label=column)

    # Add legend
    plt.legend(loc=4)
    
    # Add titles
    plt.xlabel("Edge Distance")
    plt.ylabel("Optimality Ration")

    # Show the graph
    plt.show()


