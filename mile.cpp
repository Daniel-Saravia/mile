#include <GL/glut.h> // Include OpenGL Utility Toolkit library
#include <cstdio>
// Defines the initial angle of the door, used to rotate the door around the y-axis
float doorAngle = 0.0f;

// init ---------------------------------------------------------------------------------
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white
    glMatrixMode(GL_PROJECTION);      // Set the current matrix mode to projection
    glLoadIdentity();                 // Load the identity matrix
    gluOrtho2D(-10, 10, -10, 10);     // Set up a 2D orthographic projection
    glMatrixMode(GL_MODELVIEW);       // Set the current matrix mode to modelview
}

// drawGrid ---------------------------------------------------------------------------------
void drawGrid() {
    int i;
    glColor3f(0.8f, 0.8f, 0.8f); // Set grid color to light grey
    glBegin(GL_LINES);

    // Draw vertical grid lines
    for (i = -10; i <= 10; i++) {
        glVertex2f((float)i, -10.0f);
        glVertex2f((float)i, 10.0f);
    }
    // Draw horizontal grid lines
    for (i = -10; i <= 10; i++) {
        glVertex2f(-10.0f, (float)i);
        glVertex2f(10.0f, (float)i);
    }

    glEnd();

    // Draw a red dot at the center
    glPointSize(5.0f); // Set point size to make the dot larger
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
    glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f); // Center point
    glEnd();
}

// drawDoor ---------------------------------------------------------------------------------
void drawDoor()
{
    glPushMatrix();                      // Push the current matrix onto the stack
    glColor3f(0.78, 0.74, 0.66);         // Set color to brown https://keiwando.com/color-picker/
    glTranslatef(-3.0, 0.0, 0.0);        // Translate to the position where the door will be drawn
    glRotatef(doorAngle, 0.0, 1.0, 0.0); // Rotate the door around the y-axis
    glBegin(GL_POLYGON);                 // Begin drawing a polygon
    glVertex2f(-4.0, -7.0);              // Define vertex 1
    glVertex2f(-4.0, 8.0);               // Define vertex 2
    glVertex2f(5.0, 8.0);                // Define vertex 3
    glVertex2f(5.0, -7.0);               // Define vertex 4
    glEnd();                             // End drawing the polygon
    glPopMatrix();                       // Pop the current matrix from the stack
}

// drawDoorFrame ---------------------------------------------------------------------------------
void drawDoorFrame()
{
    glColor3f(0.65, 0.65, 0.65); // Set color to light grey

    // Define the thickness of the frame
    float thickness = 0.5f; // Adjust this value to make the frame thicker or thinner

    // Draw vertical parts of the frame as rectangles
    glBegin(GL_QUADS);
    // Left vertical part
    glVertex2f(-7.3 - thickness, -7.4);
    glVertex2f(-7.3 + thickness, -7.4);
    glVertex2f(-7.3 + thickness, 8.15);
    glVertex2f(-7.3 - thickness, 8.15);
    // Right vertical part
    glVertex2f(6.0 - thickness, -7.0);
    glVertex2f(6.0 + thickness, -7.0);
    glVertex2f(6.0 + thickness, 8.0);
    glVertex2f(6.0 - thickness, 8.0);
    glEnd();

    // Draw horizontal parts of the frame as rectangles
    glBegin(GL_QUADS);
    // Top horizontal part
    glVertex2f(-7.5, 7.8 + thickness);
    glVertex2f(6.4, 7.8 + thickness);
    glVertex2f(6.4, 7.8 - thickness);
    glVertex2f(-7.5, 7.8 - thickness);
    // Bottom horizontal part
    glVertex2f(1.6, -7.0 - thickness);
    glVertex2f(6.4, -7.0 - thickness);
    glVertex2f(6.4, -7.0 + thickness);
    glVertex2f(1.6, -7.0 + thickness);
    glEnd();
}

// display ---------------------------------------------------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glLoadIdentity();             // Load the identity matrix

    
    //drawDoor();      // Draw the door
    //drawDoorFrame(); // Draw the door frame
    drawGrid();      // Draw the grid

    glFlush(); // Flush OpenGL pipeline
}

// update ---------------------------------------------------------------------------------
void update(int value)
{
    glutPostRedisplay();          // Post a redraw request
    glutTimerFunc(16, update, 0); // Call update function after 16 milliseconds
}

// keyboard ---------------------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y)
{
    if (key == ' ')
    {                      // If spacebar is pressed
        doorAngle += 5.0f; // Increase door angle
        if (doorAngle > 90.0f)
            doorAngle = 0.0f; // Reset angle if it exceeds 90 degrees
    }
}

// main ---------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);                       // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Set display mode
    glutInitWindowSize(700, 800);                // Set window size
    glutCreateWindow("OpenGL Door");             // Create a window with the specified title
    init();                                      // Call initialization function
    glutDisplayFunc(display);                    // Set display callback function
    glutTimerFunc(16, update, 0);                // Call update function
    glutKeyboardFunc(keyboard);                  // Set keyboard callback function
    glutMainLoop();                              // Enter the GLUT event processing loop
    return 0;                                    // Return success
}
