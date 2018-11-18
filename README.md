# Conway's Game of Life (C++)

This is my rendition of Conway's game of life.

I'm using CImg (http://cimg.eu/) for my GUI, it's simpler to use than OpenGL or Vulcan and it's pretty fast to render images.

# Installation
This program is dependent on Xorg's X11 dev package.  
`sudo apt install libx11-dev`
  
Now run the setup.sh script I've provided. This will use git to clone the CImg repo, copy over the header for the library and then remove the CImg directory.  
`./setup.sh`  
  
`mkdir build && cd build`  
This project uses CMake to compile the project, so use the following commands to compile.  

`cmake ..`  

`make`  

# How do I use this thing?
Once the window opens, you can click on each individual block to change it's state.  
After you have an initialization you would like to keep, press `SPACE` to start the simulation.  
Press `SPACE` again to stop the simulation

