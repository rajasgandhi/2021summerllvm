# llvm-pass-skeleton

Build:

    $ cd llvm-pass-skeleton
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run:

    $ clang -Xclang -disable-O0-optnone -S -emit-llvm input.c -o input.ll
    $ opt -enable-new-pm=0 -load build/skeleton/libSkeletonPass.so -hello1 -S input.ll -o output.ll

To run automated creation, run:
    
    $ python3 completegen.py [input c file] [src directory of react project] 