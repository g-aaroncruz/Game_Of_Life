# Conway's Game_of_Life (C++)

This is my rendition of Conway's game of life, currently still in process.

I'm using CImg (http://cimg.eu/) for my GUI, it's simpler to use than OpenGL or Vulcan and to my knowledge it's the fastest rendering library that is easy to use.

# Installation
This program is dependent on Xorg's X11 dev package.
`sudo apt install libx11-dev`

Now run the setup.sh script I've provided. This will use git to clone the CImg repo, copy over the header for the library and then remove the CImg directory.
`./setup.sh`

`mkdir build && cd build`
This project uses CMake to compile the project, so use the following commands to compile.
`cmake ..`, 
`make`
