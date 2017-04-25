#!/bin/bash
cd libraries/Build/
make
cd ../..
qmake -makefile
make
