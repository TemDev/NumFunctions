# LLVM file based on file produced by llvmtutor

cmake_minimum_required(VERSION 3.20)
project(FunctionCounter)

# Load LLVM configuration
set(LT_LLVM_INSTALL_DIR "" CACHE PATH "LLVM installation directory")

# Add location of LLVMConfig.cmake to CMake search paths (so that find_package can locate it)
list(APPEND CMAKE_PREFIX_PATH "${LT_LLVM_INSTALL_DIR}/lib/cmake/llvm/")

find_package(LLVM 11.1.0 CONFIG)


# FunctionCounter includes headers from LLVM - update the include paths accordingly
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})

# LLVM Build configuration
set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

# LLVM is normally built without RTTI. Be consistent with that.
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

# Add the target
add_library(FunctionCounter SHARED FunctionCounter.cpp)

# Allow undefined symbols in shared objects on Darwin (this is the default behaviour on Linux)
target_link_libraries(FunctionCounter
  "$<$<PLATFORM_ID:Darwin>:-undefined dynamic_lookup>")