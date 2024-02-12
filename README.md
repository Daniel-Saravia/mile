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
Replace opengl_door.cpp with the name of your source file. For Windows or other operating systems, ensure you have the appropriate compiler and link against the OpenGL and GLUT libraries as required.

How It Works
Initialization: Sets up the rendering context, including the viewport, projection mode, and clear color.
Drawing Functions: Includes functions to draw the grid (optional and commented out by default), door, door frame, knob, and additional decorative elements.
Transformation Functions: Applies translations, rotations, and scaling to animate and position elements.
Interactive Keyboard Control: Listens for the space bar press to rotate the door.
Project Structure
init(): Initializes OpenGL settings.
drawGrid(): Draws a grid on the screen (commented out by default).
drawCircle(): Draws a circle, used for the door knob.
drawTriangleFlagWithRectangle(): Draws a decorative flag on the door.
drawStrokeText(): Renders custom text next to the flag.
drawDoor(): Draws the main door with the knob and flag.
drawDoorFrame(): Draws the door frame around the door.
drawRectangle(): Utility function to draw rectangles with borders, used for various structural elements.
display(): Main rendering function that clears the screen and draws all elements.
update(): Callback function to update the animation state and trigger a redraw.
keyboard(): Handles keyboard input for interactivity.
main(): Entry point of the program, sets up GLUT and enters the main event loop.
Customizing
Feel free to modify the drawing functions or add new elements to the scene. Adjusting the transformation parameters or adding new keyboard controls can also enhance the interactivity and visual appeal of the project.

Conclusion
This project provides a foundational understanding of using OpenGL and GLUT for simple 2D animations. It showcases how to work with basic geometric primitives, apply transformations, and handle user input for interactive graphics applications.


