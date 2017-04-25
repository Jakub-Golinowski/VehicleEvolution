#!/bin/bash
cd libraries/Build/
cmake ..
make
cd ../..
qmake -makefile
make
