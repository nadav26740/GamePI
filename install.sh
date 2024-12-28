#!/bin/bash
set -e # stop on error

echo Installing dependencies

sudo apt upgrade
sudo apt-get install libsfml-dev