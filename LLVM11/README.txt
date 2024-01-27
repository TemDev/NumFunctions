Commands to run

mkdir build
cd build

export LLVM_DIR=/usr/local/Cellar/llvm@11/11.1.0_4/include/llvm

cmake -G Ninja -DLT_LLVM_INSTALL_DIR=$LLVM_DIR ../

ninja

clang -c -emit-llvm ../program.c

Run this:

on MacOs:
opt -load libFunctionCounter.dylib -function-counter -disable-output program.bc

on Linux:
opt -load ./libFunctionCounter.so -function-counter -enable-new-pm=0 < program.bc > /dev/null