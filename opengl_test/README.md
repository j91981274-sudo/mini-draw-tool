# Mini Draw Tool

A simple desktop drawing application built using C++ and OpenGL.

## Features
- Draw with mouse
- Change colors using keyboard
- Change brush size
- Save drawing as an image
- Lightweight and fast

## Controls
- Mouse Left Click: Draw
- 1 / 2 / 3 / 4: Change colors
- [ and ]: Decrease / Increase brush size
- ESC: Save image and exit

## Build Instructions
### Requirements
- Ubuntu / Linux
- g++
- GLFW
- OpenGL

### Compile
```bash
g++ main.cpp -o draw -lglfw -lGL
