from re import match
import tools
import numpy.random as random
import os

def generate_branch(mod:tools.Model, dim, folder_s, instance_size, instance_num, width, height,alpha= 0):
    folder_s.mkdir( parents=True, exist_ok=True )
    for seed in range( 0, instance_num):
        random.seed(seed)
        file_s = "{0}_{1}_{2}_{3}.txt".format(mod.value,dim, str(instance_size), str(seed))
        generate_instance(mod, dim, folder_s, file_s, instance_size, width, height,alpha)


def generate_instance(mod:tools.Model, dim, folder_s, file_s, instance_size, width, height,alpha=0):
    folder_name = "uniform_"+str(instance_size) 
    file_path = folder_s/folder_name/ file_s
    print(file_path)
    with file_path.open("w") as f:
        f.write( "c This is a {0} distributed  {1}-D DIMACS file \n".format(mod.value, str(dim)) )
        f.write( "c width height point_number\n" )
        f.write( f"p {width} {height} {instance_size}\n" )
        match mod: 
            case tools.Model.UNIT:
                points_x = tools. unit_list(1, instance_size+1, instance_size)
            case tools.Model.UNIFORM:
                points_x = tools. uniform_list(1,width , instance_size)
            case tools.Model.MIXED:
                points_x = tools. mixed_list(1,width , instance_size)    
            case tools.Model.EXP:
                points_x = tools. expo_list(1,width , instance_size,alpha)
            case tools.Model.UNIT_FRAC:
                points_x = tools.unit_list_frac(1, instance_size+1, instance_size)
            case tools.Model.UNIFORM_FRAC:
                points_x = tools.uniform_list_frac(1,width , instance_size)
            case tools.Model.MIXED_FRAC:
                points_x = tools.mixed_list_frac(1,width , instance_size)          
            case tools.Model.EXP_FRAC:
                points_x = tools.expo_list_frac(1,width , instance_size,alpha)        
        if mod == tools.Model.UNIT_FRAC or mod == tools.Model.UNIFORM_FRAC or mod == tools.Model.MIXED_FRAC or mod == tools.Model.EXP_FRAC:
            for i in range( instance_size ):
                f.write( f"{points_x[i].numerator}  {points_x[i].denominator}  0\n" )
        else:
            for i in range( instance_size ):
                f.write( f"{points_x[i]} 0\n" )
    f.close()
    '''
    plot_s = folder_s / (file_s+"_plot.png")
    Y = [height/2.0] * instance_size
    tools.draw_points(points_x, Y, width, height, plot_s)
    '''