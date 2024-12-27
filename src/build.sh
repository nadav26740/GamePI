#!/bin/bash
set -e # stop on error

# output file
OUTFILE="sfml-app.out"

# for macro flags 
COMPILING_MODE_HEADER="CurrentMode.hpp"

if [ "$*" == "--release" ]
then
    echo buliding on Release Mode
    echo "#define RELEASE" > $COMPILING_MODE_HEADER
    mkdir -p release
    
    # Creating the object files
    g++ -std=c++17 -c main.cpp -o release/main.o
    
    sleep 0.5
    g++ release/main.o -O3 "release/$OUTFILE" -lsfml-graphics -lsfml-window -lsfml-system
    
else
    echo Building on debug mode
    echo "#define DEBUG" > $COMPILING_MODE_HEADER
    mkdir -p debug
    
    # Creating the object files
    g++ -std=c++17 -c main.cpp -o debug/main.o
    
    sleep 0.5
    g++ debug/main.o -o "debug/$OUTFILE" -lsfml-graphics -lsfml-window -lsfml-system
fi

echo Compiled into sfml-app.out
