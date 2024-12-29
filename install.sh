#!/bin/bash
set -e # stop on error

echo Installing dependencies

sudo apt update
sudo apt upgrade
sudo apt install g++
sudo apt-get install libsfml-dev
