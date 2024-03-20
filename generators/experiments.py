import shutil
import subprocess
import glob
import tempfile
from fractions import Fraction
solver_path = "D:\\GIT\\OriSpanner\\build\\src\\Debug\\OriSpanner.exe"
instances_path = "D:/GIT/OriSpannerP/instances"
example_path = "D:/GIT/OriSpanner/instances/uniform_512/uniform_1_512_23.txt"
idx = example_path.index(".txt")
example_path_reduced = example_path[:idx] + "_reduced" + example_path[idx:]
example_path_reduced_final = example_path[:idx] + "_reduced_final" + example_path[idx:]
example_path_tmp = example_path[:idx] + "_tmp" + example_path[idx:]
point_size = 26
solver_str = "sat"
def run_solver(file_name, solver_str):
    with tempfile.TemporaryFile() as tempf:
        comd = solver_path + " "
        proc = subprocess.Popen([comd, "-f", file_name, "-a", solver_str], stdout=tempf)
        proc.wait()
        tempf.seek(0)
        return tempf.read()

    #comd += file_name
    #subprocess.call([comd, "-f", file_name])
def get_ori(output):
    output = str(output).split("{")[0]
    num = str(output).split(" ")
    i = 0
    for ph in num:
        if "with" in ph:
            break
        i+= 1
    n =int(num[i+1].split(",")[0])
    d = int(num[i+2].split("{")[0].split("H")[0])
    return Fraction(n,d)

def run_experiments():
    solutions = {}
    for f in glob.glob(instances_path, recursive=True):
        with tempfile.TemporaryFile() as tempf:
            print(f)
            output = run_solver(tempf, f)
            print(f)
            solutions[f[f.rindex('\\')+1:]] = get_ori(output)
    return solutions
def run_batch():
    solutions = {}
    for f in glob.glob(instances_path, recursive=True):
        with tempfile.TemporaryFile() as tempf:
            print(f)
            output = run_solver(tempf, f)
            print(f)
            solutions[f[f.rindex('\\')+1:]] = get_ori(output)
    return solutions

def reduce_point(skip_line, solver_name, ori_d):
    ori_f = open(example_path_reduced, "r")
    copy = open(example_path_tmp, "wt")
    i = 0
    for line in ori_f:
        if i != skip_line:
            copy.write(line)
        i = i+1
    ori_f.close()
    copy.close()    
    output = run_solver(example_path_tmp,solver_name)        
    red_d = get_ori(output)
    if red_d == ori_d:
        return True
    else:
        return False
    # write to a tmp test file
    # if success, write back to the file_path

def reduction(ori_d, start_o, stop_o):
    start = start_o
    stop = stop_o
    i = start
    while i < stop and stop > 4:
        reducible = reduce_point(3+i, solver_str, ori_d)
        if reducible:
            shutil.copyfile(example_path_tmp, example_path_reduced)
            stop = stop -1
            print(stop)
            continue
        i = i +1
            # copy back to the temp
def extract_distances(point_list):
    p_new = [1]
    current = 1
    length = len(point_list)
    for i in range(length-1):
        dis = point_list[i+1]- point_list[i]
        current += dis
        p_new.append(current)
    return p_new
def sublocationse(filename):
    p = []
    with open(filename) as file:
        lines = [line.rstrip() for line in file]
        print(lines)
    length = len(lines)
    for i in range(3, length):
        print(lines[i])
        if(lines[i].endswith("0")):
            n = int(lines[i].split(" ")[0])
            p.append(n)
    p_new = extract_distances(p)
    with open(example_path_reduced_final, "w") as f:
        f.write( "c This is a uniform distributed  1-D DIMACS file \n" )
        f.write( "c width height point_number\n" )
        instance_size = len(p_new)
        f.write( f"p 100000 100000 {instance_size}\n" )
        for i in range( instance_size ):
            f.write( f"{p_new[i]} 0\n" )
    f.close()


if __name__ == "__main__":
        
        output = run_solver(example_path,solver_str)
        ori_d = get_ori(output)
        shutil.copyfile(example_path, example_path_reduced)
        reduction(ori_d, 0, point_size)
        sublocationse(example_path_reduced)
        output = run_solver(example_path_reduced_final,solver_str)
        ori_d_reduced = get_ori(output)
        assert(ori_d_reduced == ori_d)