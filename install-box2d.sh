#!/bin/sh

set -ex

mkdir box2d-workdir && cd box2d-workdir 
git clone https://github.com/mhwcat/Box2D.git
cd Box2D/ && mkdir build/ && cd build/
cmake ..
make
sudo make install