import subprocess
import sys
name = "inputs/inputNum"
command = "./" + sys.argv[1]
output = "railway_planner_output.txt"
string = ""
for i in range(500):
    input = name + str(i) + ".txt"
    subprocess.run([command, input])
    f = open(output, 'r')
    lst = f.readlines()
    file = ""
    for line in lst:
        file += line + "\n"
    string += file
    f.close()
f = open("output", 'w')
f.write(string)
f.close()
subprocess.run(["diff", "schooloutput", "output"])
