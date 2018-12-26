# Anri
Development: [![Build Status](https://travis-ci.org/mhwcat/anri.svg?branch=development)](https://travis-ci.org/mhwcat/anri)
## What is it? 
Simple 2D game engine developed after hours for fun.

## Build
CMake is used to generate makefiles, it should be pretty straightforward to build on any system.
Tested on macOS 10.14, Windows 10 and Ubuntu 18.04/14.04 (used for Travis build).  
### Dependencies
Anri needs CMake, g++, SDL2, SDL2-TTF, SDL2-Mixer, SDL2-Image, SDL2_gfx and Box2D to build.

Ubuntu:
```
sudo apt update
sudo apt install cmake3 gcc-7 g++-7 libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev libsdl2-image-dev libsdl2-gfx-dev
```
macOS (assuming you're using brew):
```
brew update
brew install cmake gcc sdl2 sdl2_ttf sdl2_mixer sdl2_image sdl2_gfx
```
Windows:
* Download CMake 
* Download SDL2-devel, SDL2-TTF-devel, SDL2-Mixer-devel, SDL2-Image-devel, SDL2_gfx for Windows
* Copy libraries and headers some directory
* Use provided VS2017 solution file or generate one yourself using CMake  

**SDL2_gfx on Windows**:  
There is no prebuilt binary of SDL2_gfx for Windows afaik, so you have to build one yourself.  
*TODO: Add build instructions or fork repository and add VS solution.*

**Box2D**:  
Use my fork of Box2D with CMake support restored: https://github.com/mhwcat/Box2D  
On Windows you can use CMake GUI to generate VS2017 solution.  
*TODO: Update fork with prepared solution.*

### Building
It should be similar on all systems (on Windows use VS MSBuild). On Unix systems you can use prepared shell script (remember to set correct paths to gcc and g++):
```
cd [anri-sources-root]
mkdir cmake-build-debug-gcc
./build-gcc.sh
```
CMake will also copy `anri.conf` configuration file and `assets` directory to build directory.