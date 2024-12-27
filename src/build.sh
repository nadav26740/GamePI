#!/bin/bash
set -e # stop on error

# files to compile
CODE_FILES=(
    "main.cpp"
)

OBJECTS_PATH=()

# output file
OUTFILE="sfml-app.out"

# for macro flags 
COMPILING_MODE_HEADER="CurrentMode.hpp"

# assembling all the code files to object files
AssembleAllFiles()
{
    folder_location=$1
    for code_file in ${CODE_FILES[@]}
    do
        echo Assembling $code_file
        g++ -std=c++17 -c $code_file -o ${folder_location}/${code_file}.obj
        OBJECTS_PATH+=(${folder_location}/${code_file}.obj) # saving the asmbled files
    done
    echo Object Files Created: ${OBJECTS_PATH[@]}
}

# checking that all files exists
Integrity_check()
{
    echo Integrity Check
    for file_path in ${CODE_FILES[@]}
    do
        if [ ! -e $file_path ]
        then
            echo \[ERROR\] $file_path Not Exists! 
            exit -1
        fi
    done
}

Integrity_check

if [ "$*" == "--release" ]
then
    echo buliding on Release Mode
    echo "#define RELEASE" > $COMPILING_MODE_HEADER
    mkdir -p release
    
    # Creating the object files
    AssembleAllFiles release
    
    sleep 0.5
    g++ ${OBJECTS_PATH[@]} -O3 -lsfml-graphics -lsfml-window -lsfml-system -o "release/$OUTFILE" 
    echo Compiled into release/$OUTFILE
    
else
    echo Building on Debug mode
    echo "#define DEBUG" > $COMPILING_MODE_HEADER
    mkdir -p debug
    
    # Creating the object files
    AssembleAllFiles debug
    
    sleep 0.5
    g++ ${OBJECTS_PATH[@]} -lsfml-graphics -lsfml-window -lsfml-system -o "debug/$OUTFILE" 
    echo Compiled into debug/$OUTFILE
fi
