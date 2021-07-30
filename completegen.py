import os
import subprocess

list_files = subprocess.run(["clang -Xclang -disable-O0-optnone -S -emit-llvm input.c -o input.ll",
                             "cd build",
                             "make",
                             "cd ..",
                             "opt -enable-new-pm=0 -load build/skeleton/libSkeletonPass.so -hello1 -S input.ll -o output.ll",
                             "python3 transformjson.py"], shell=True)
