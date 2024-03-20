import subprocess
import glob
import tempfile
def run_solver(file_name):
    comd = "D:\\GIT\\Page2SAT\\x64\\Debug\\Page2SAT.exe "
    proc = subprocess.Popen([comd, file_name], stdout=subprocess.PIPE,  stdin=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = proc.communicate()
    if err.decode('latin-1').__contains__("error"):
        assert(False)
    print(out.splitlines()[-1])

    #comd += file_name
    #subprocess.call([comd, "-f", file_name])
solutions = {}
if __name__ == "__main__":
    for f in glob.glob('D:/GIT/OriSpannerP/instances/1D/Uniform/uniform_1_128*.txt', recursive=True):
        print(f)
        output = run_solver(f)


