#!/bin/sh

set -ex

mkdir sdl2gfx-workdir && cd sdl2gfx-workdir 
git clone https://github.com/svn2github/sdl2_gfx.git
cd sdl2_gfx/
./autogen.sh
./configure
make
sudo make install