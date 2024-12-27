#!/bin/bash
set -e # stop on error
OUTFILE="sfml-app.out"
COMPILING_MODE_HEADER="CurrentMode.hpp"

g++ -std=c++17 -c main.cpp

if [ "$*" == "--release" ]
then
    echo "#define RELEASE" > $COMPILING_MODE_HEADER
    echo buliding on Release Mode
    sleep 0.5
    g++ main.o -O3 $OUTFILE -lsfml-graphics -lsfml-window -lsfml-system
else
    echo "#define DEBUG" > $COMPILING_MODE_HEADER
    echo Building on debug mode
    sleep 0.5
    g++ main.o -o $OUTFILE -lsfml-graphics -lsfml-window -lsfml-system
fi

echo Compiled into sfml-app.out
