# Function, basic block and instruction counter

## Features

1. Counts number of functions in program
2. Counts number of basic blocks in program
3. Counts number of instructions in each block
4. Outputs a map of instructions and how many basic blocks have that amount of instructions

## Installation

Two different versions for llvm-11 and llvm-17, this was done because I could not install the deprecated version of llvm on my ubuntu virtual machine. Hence the version for LLVM-11 is untested on a linux distribution, it works on Mac OS with dylib files.
Mostly differ by their respective CMakeLists.txt files.

Requires Clang, LLVM and ninja:

To install Clang, simply use your package manager, or use a pre-built
binary from http://llvm.org/releases/download.html.

To install LLVM, you can again use your package manager or download
the LLVM source code from http://llvm.org/releases/download.html and
follow the instructions on the website to build it.

Depending on system install ninja.

Clone/fork the repository.

cd into any of the LLVM directories.

To keep the build separate to the code, create a new directory and cd into it:

mkdir build
cd build

This is followed by setting the environment LLVM_DIR variable based on which version off llvm you want to use.

export LLVM_DIR= /path/to/your/llvm11.1.0

examples:

export LLVM_DIR=/usr/local/Cellar/llvm@11/11.1.0_4/include/llvm

export LLVM_DIR=/usr/include/llvm-17

Make the directory and run ninja.

cmake -G Ninja -DLT_LLVM_INSTALL_DIR=$LLVM_DIR ../

ninja

Compile your program, in this case there is already an example program called program.c.

clang -c -emit-llvm ../program.c

Run:

For Mac OS:
opt -load libFunctionCounter.dylib -function-counter -disable-output program.bc

or for Linux:
opt -load ./libFunctionCounter.so -function-counter -enable-new-pm=0 < program.bc > /dev/null

