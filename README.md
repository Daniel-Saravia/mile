# OpenGL Door Animation Project README

This project demonstrates a simple 2D door animation using the OpenGL Utility Toolkit (GLUT). It's a great starting point for beginners to learn about basic OpenGL concepts such as drawing geometric shapes, applying transformations, and handling keyboard inputs for interactivity.

## Features

- **Dynamic Door Animation**: Rotate the door around the y-axis using the space bar.
- **Geometric Drawing**: Utilizes OpenGL primitives to draw shapes including a door, door frame, knob, and decorative flag.
- **Custom Text Rendering**: Displays stroke text on the screen.
- **Interactive Control**: Uses keyboard input to control the animation.

## Requirements

- OpenGL
- GLUT library

Ensure you have both OpenGL and the GLUT library installed on your system. These are available on most operating systems, including Windows, macOS, and Linux.

## Compilation and Running

The method of compilation depends on your operating system and installed compiler. Here's an example using `g++` on Linux:

```sh
g++ -o opengl_door opengl_door.cpp -lGL -lGLU -lglut
And to run the program:

```sh
./opengl_door
