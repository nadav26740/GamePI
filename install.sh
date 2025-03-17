#!/bin/bash
set -e # stop on error

echo Installing dependencies

sudo apt update
sudo apt upgrade
sudo apt install g++
sudo apt-get install libsfml-dev

echo Creating Config file (Todo)

echo Moving assets to place (TODO)

echo Creating needed directories (TODO)

echo compiling...
cd ./src
./build --release

echo Add system to autostart (TODO)