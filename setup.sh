#!/bin/bash

git --version 2>&1 >/dev/null
GIT_IS_AVAILABLE=$?

if [ $GIT_IS_AVAILABLE -eq 0 ]; then
	echo "Git is installed.."
else
	echo "ERROR: git not found, please install before continuing"
	exit
fi
if [ -f include/CImg.h ]; then
	echo "CImg.h already in include/"
	echo "If you're having trouble, make sure you install libx11-dev!"
	exit
else
        git clone https://framagit.org/dtschump/CImg.git
        cp CImg/CImg.h include
        rm -rf CImg
fi
