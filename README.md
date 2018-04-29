# Anri
Development: [![Build Status](https://travis-ci.org/mhwcat/anri.svg?branch=development)](https://travis-ci.org/mhwcat/anri)
## What is it? 
Simple 2D game engine developed after hours for fun.

## Build
CMake is used to generate makefiles, it should be pretty straightforward to build on any system.
Tested on macOS 10.13.2, Windows 10 and Ubuntu 14.04 (used for Travis build).  
### Dependencies
Anri needs CMake, g++/clang, SDL2, SDL2-TTF, SDL2-Mixer and SDL2-Image to build.

Ubuntu:
```
sudo apt update
sudo apt install cmake3 gcc-7 g++-7 libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev libsdl2-image-dev
```
macOS (assuming you're using brew):
```
brew update
brew install cmake gcc sdl2 sdl2_ttf sdl2_mixer sdl2_image
```
Windows:
* Download CMake 
* Download TDM-GCC MinGW compiler (It comes with 64bit toolchain so I found it more suitable)
* Download SDL2-devel, SDL2-TTF-devel, SDL2-Mixer-devel, SDL2-Image-devel for Windows
* Copy .lib files and headers into MinGW `lib` and `include` directories
### Building
It should be similar on all systems (on Windows you can you CMake GUI). On Unix systems you can use prepared shell script (remember to set correct paths to gcc and g++):
```
cd [anri-sources-root]
mkdir cmake-build-debug-gcc
./build-gcc.sh
```
CMake will also copy `anri.conf` configuration file and `assets` directory to build directory.