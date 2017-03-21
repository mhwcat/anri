#!/bin/sh

make clean

mkdir -p build/engine/render/SDL
mkdir -p build/engine/input/SDL
mkdir -p build/engine/event/SDL
mkdir -p build/game/objects
mkdir -p build/game/levels

make -j 4

bin/dot
