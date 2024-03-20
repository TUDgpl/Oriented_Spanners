import numpy as np
from enum import Enum
import numpy.random as random
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt
import os
from fractions import Fraction


import networkx as nx
deno_limit = 1000

# uniform model
# generate list of uniform random numbers of [low, high-1]
def uniform_list(low, high, instance_size):
    points_x = set()
    while len( points_x ) < instance_size:
        x_rand = random.randint( low, high)
        points_x.add(x_rand)
    list_x = sorted( points_x )
    return list_x 

def uniform_list_frac(low, high, instance_size):
    points_x = set()
    while len( points_x ) < instance_size:
        x_rand = random.randint( low, high)
        points_x.add(x_rand)
    list_x = sorted( points_x )
    list_x_frac = []
    for v in list_x:
        list_x_frac.append(Fraction(v, 1))
    return list_x_frac 


positions = []

def get_pk(base , k):
    pk = (pow(base, k+1)-1)/ (base -1)
    assert pk >= 0
    return round(pk, 4) 

def get_pk_frac(base , k):
    f = get_pk(base,k)
    return Fraction(f).limit_denominator(deno_limit)
def expo_list(low, high, instance_size,alpha):
    points_x = []
    for i in range(0,instance_size):
        points_x.append(get_pk(alpha,i))
    return points_x

def expo_list_frac(low, high, instance_size,alpha):
    points_x = []
    for i in range(0,instance_size):
        points_x.append(get_pk_frac(alpha,i))
    return points_x

def mixed_list(low, high, instance_size):
    points_x = set()
    x_inc = 10001;
    points_x = [10001]
    i = 0;
    while len( points_x ) < instance_size:
        x_inc = x_inc + (10000+ pow(2,i))
        i = i + 1 
        points_x.append(x_inc)
    return points_x     


def mixed_list_frac(low, high, instance_size):
    points_x = mixed_list(low, high, instance_size)
    points_x_frac = []
    for v in points_x:
        points_x_frac.append(Fraction(v, 1))
    return points_x_frac

# generate list  [low, +1...., high-1]
def unit_list(low, high, instance_size):
    return list(range(low,high,1))

def unit_list_frac(low, high, instance_size):
    t = list(range(low,high,1))
    t_frac = []
    for v in t:
        t_frac.append(Fraction(v, 1))
    return t_frac

class Model( Enum ):
    UNIFORM = "uniform"
    UNIT = "unit"
    MIXED = "mixed"
    EXP = "exp"
    UNIFORM_FRAC = "uniform_frac"
    UNIT_FRAC = "unit_frac"
    MIXED_FRAC = "mixed_frac"
    EXP_FRAC = "exp_frac"

def str_gen(list_str):
    name = ""
    for e in list_str:
        name += str( e )
        name += "_"
    name += "0"
    return name


# draw the instance point set
def draw_points(X, Y, width,height, file_name):
    if os.name == 'nt':
        df = pd.DataFrame(dict(x=X, y=Y))
        print(df.head())
        lm =sns.scatterplot(data=df, x="x", y="y")
        #lm.set(xlim=(0, width))
        #lm.set(ylim=(0, height))
        #plt.show()
        plt.savefig(file_name)
        plt.clf()



        


