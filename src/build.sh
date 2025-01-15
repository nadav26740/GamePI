#!/bin/bash
set -e # stop on error

# files to compile
CODE_FILES=(
    "Demo_main.cpp"
    "libs/SFMLBoost/BoostSFML.cpp"
    "libs/SFMLBoost/ObjectsGroup.cpp"
    "Core/AssetsCacheManager.cpp"
)

# To link an SFML library, you must add "-lsfml-xxx"
SFML_FLAGS=(
    "-lsfml-audio"
    "-lsfml-graphics"
    "-lsfml-window"
    "-lsfml-system"
)

OBJECTS_PATH=()

# output file
OUTFILE="sfml-app.out"

# bin paths
DEBUG_BIN_FOLDER="bin/debug"
RELEASE_BIN_FOLDER="bin/release"

# for macro flags 
COMPILING_MODE_HEADER="MacroFlags.hpp"

# assembling all the code files to object files
AssembleAllFiles()
{
    folder_location=$1
    for code_file in ${CODE_FILES[@]}
    do
        echo Assembling $code_file
        g++ -std=c++17 -c $code_file -o ${folder_location}/${code_file//"/"/"."}.obj -I.
        OBJECTS_PATH+=(${folder_location}/${code_file//"/"/"."}.obj) # saving the asmbled files
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

if [[ "$*" == *"--release"* ]]
then
    echo buliding on Release Mode
    echo "#define RELEASE" > $COMPILING_MODE_HEADER
    mkdir -p $RELEASE_BIN_FOLDER
    
    # Creating the object files
    AssembleAllFiles ${RELEASE_BIN_FOLDER}
    
    sleep 0.5
    
    # compiling to bin file
    g++ ${OBJECTS_PATH[@]} -std=c++17 -O3 ${SFML_FLAGS[@]} -o "${RELEASE_BIN_FOLDER}/$OUTFILE" 
    echo Compiled into ${RELEASE_BIN_FOLDER}/$OUTFILE
    Output_path=${RELEASE_BIN_FOLDER}/$OUTFILE

    
else
    echo Building on Debug mode
    echo "#define DEBUG" > $COMPILING_MODE_HEADER
    mkdir -p ${DEBUG_BIN_FOLDER}
    
    # Creating the object files
    AssembleAllFiles ${DEBUG_BIN_FOLDER}
    
    sleep 0.5

    # compiling to bin file
    g++ ${OBJECTS_PATH[@]} -std=c++17 ${SFML_FLAGS[@]} -o "${DEBUG_BIN_FOLDER}/$OUTFILE" 
    echo Compiled into ${DEBUG_BIN_FOLDER}/$OUTFILE
    Output_path=${DEBUG_BIN_FOLDER}/$OUTFILE
fi

if [[ "$*" == *"run"* ]]
then
    ./${Output_path}
fi