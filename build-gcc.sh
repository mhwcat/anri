#!/bin/sh

CXX_FLAGS="-Wall -pedantic -Werror -Wno-variadic-macros -Wno-long-long -Wno-shadow"
CMAKE_C_COMPILER="/usr/local/Cellar/gcc/7.3.0_1/bin/gcc-7"
CMAKE_CXX_COMPILER="/usr/local/Cellar/gcc/7.3.0_1/bin/g++-7"

cd cmake-build-debug-gcc
cmake -DCMAKE_C_COMPILER=$CMAKE_C_COMPILER -DCMAKE_CXX_COMPILER=$CMAKE_CXX_COMPILER -DCMAKE_CXX_FLAGS=$CXX_FLAGS -DCMAKE_BUILD_TYPE=Debug ..
make
