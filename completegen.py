import os
import subprocess
import sys

compileCFile = "clang -Xclang -disable-O0-optnone -S -emit-llvm " + sys.argv[1] + " -o input.ll"
file = os.getcwd() + "/outputtransformed.json"
copyJSON = "cp " + file + " " + sys.argv[2]

subprocess.run([compileCFile], shell=True)
subprocess.run(["make"], cwd="build/", shell=True)
subprocess.run(["opt -enable-new-pm=0 -load build/skeleton/libSkeletonPass.so -hello1 -S input.ll -o output.ll"], shell=True)
subprocess.run(["python3 transformjson.py"], shell=True)
subprocess.run([copyJSON], shell=True)
subprocess.run(["npm start"], cwd="/home/rajas/Documents/GitHub/2021summervistool", shell=True)