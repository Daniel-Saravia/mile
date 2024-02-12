#include <GL/glut.h> // Include OpenGL Utility Toolkit library
#include <cstdio>
#include <math.h>

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
void drawGrid()
{
    int i;
    glColor3f(0.8f, 0.8f, 0.8f); // Set grid color to light grey
    glBegin(GL_LINES);

    // Draw vertical grid lines
    for (i = -10; i <= 10; i++)
    {
        glVertex2f((float)i, -10.0f);
        glVertex2f((float)i, 10.0f);
    }
    // Draw horizontal grid lines
    for (i = -10; i <= 10; i++)
    {
        glVertex2f(-10.0f, (float)i);
        glVertex2f(10.0f, (float)i);
    }

    glEnd();

    // Draw a red dot at the center
    glPointSize(5.0f);           // Set point size to make the dot larger
    glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
    glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f); // Center point
    glEnd();
}

// Function to draw a circle for the door knob ---------------------------------------------
void drawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_POLYGON); // Can use GL_LINE_LOOP for a hollow circle
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); // get the current angle
        float x = r * cosf(theta);                                         // calculate the x component
        float y = r * sinf(theta);                                         // calculate the y component
        glVertex2f(x + cx, y + cy);                                        // output vertex
    }
    glEnd();
}

// Function to draw an isosceles triangle flag with a rectangle at the base, with rotation ---------------------------
void drawTriangleFlagWithRectangle(float baseX, float baseY, float baseWidth, float height, float rectHeight, float angle)
{
    glPushMatrix(); // Save the current transformation state

    // Move the flag to the origin, rotate, and move it back
    glTranslatef(baseX + baseWidth / 2.0f, baseY + rectHeight, 0.0f);       // Translate to the rotation point (base of the triangle)
    glRotatef(angle, 0.0f, 0.0f, 1.0f);                                     // Rotate the flag around its base
    glTranslatef(-(baseX + baseWidth / 2.0f), -(baseY + rectHeight), 0.0f); // Translate back

    // Draw the isosceles triangle
    glBegin(GL_TRIANGLES);                 // Start drawing a triangle
    glColor3f(1.0, 0.0, 1.0);              // Set color to red for the flag
    glVertex2f(baseX, baseY + rectHeight); // Adjusted for rectangle height
    glVertex2f(baseX + baseWidth, baseY + rectHeight);
    glVertex2f(baseX + baseWidth / 2.0f, baseY + rectHeight + height); // Top vertex
    glEnd();

    // Draw the white rectangle at the base of the triangle
    glColor3f(1.0, 1.0, 1.0); // Set color to white for the rectangle
    glBegin(GL_QUADS);
    glVertex2f(baseX, baseY);                          // Bottom left
    glVertex2f(baseX + baseWidth, baseY);              // Bottom right
    glVertex2f(baseX + baseWidth, baseY + rectHeight); // Top right
    glVertex2f(baseX, baseY + rectHeight);             // Top left
    glEnd();

    glPopMatrix(); // Restore the previous transformation state
}

void drawStrokeText(const char *text, float x, float y, float z, float scale, float angle)
{
    glPushMatrix(); // Save the current transformation state

    // Position and scale the text
    glTranslatef(x, y, z);
    glScalef(scale, scale, scale); // Scale the text to desired size

    // Rotate the text
    glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around the Z-axis

    // Render the text
    for (const char *c = text; *c != '\0'; c++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
    }

    glPopMatrix(); // Restore the previous transformation state
}

void drawDoor()
{
    glPushMatrix();                      // Push the current matrix onto the stack
    glColor3f(0.78, 0.74, 0.66);         // Set door color to brown
    glTranslatef(-3.0, 0.0, 0.0);        // Translate to the position where the door will be drawn
    glRotatef(doorAngle, 0.0, 1.0, 0.0); // Rotate the door around the y-axis
    glBegin(GL_POLYGON);                 // Begin drawing a polygon for the door
    glVertex2f(-4.0, -7.0);              // Define vertex 1
    glVertex2f(-4.0, 8.0);               // Define vertex 2
    glVertex2f(5.0, 8.0);                // Define vertex 3
    glVertex2f(5.0, -7.0);               // Define vertex 4
    glEnd();                             // End drawing the polygon for the door

    // Draw the door knob
    glColor3f(0.5, 0.5, 0.5);      // Set knob color to grey
    drawCircle(3.5, 0.5, 0.5, 32); // Draw the knob with center (3.5, 0.5), radius 0.5, and 32 segments for smoothness

    // Draw the isosceles triangle flag with a white rectangle at the base
    drawTriangleFlagWithRectangle(0, 3.0, 1.5, 4.0, 0.5, 235.0); // Parameters include rectangle height

    // Now, set the color for the stroke text
    glColor3f(0.0, 0.0, 0.0); // Black color text

    // Assuming the text needs to be rotated to match the flag's angle and scaled to fit
    // Note: You'll likely need to adjust these values based on your flag's actual orientation and desired text appearance
    drawStrokeText("GCU LOPES", 0.8, 3.5, 0.0, 0.0025, -40.0);

    glPopMatrix(); // Pop the current matrix from the stack
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

    // Draw middle vertical part of the frame as a rectangle
    glBegin(GL_QUADS);
    // Calculate the middle X position between the left and right sides of the door frame
    float middleX = 2; // Average of the left X and right X values to find the middle
    // Draw the bar from bottom to top
    glVertex2f(middleX - thickness, -7.4); // Bottom-left
    glVertex2f(middleX + thickness, -7.4); // Bottom-right
    glVertex2f(middleX + thickness, 8.15); // Top-right
    glVertex2f(middleX - thickness, 8.15); // Top-left
    glEnd();
}

// Function to draw a simple rectangle with color parameters and a simulated thicker black border
void drawRectangle(float x, float y, float width, float height, float red, float green, float blue)
{
    // Offset for the border thickness
    float borderThickness = 0.1f; // Adjust this value to change the border thickness

    // Draw the black border as a larger rectangle behind the main rectangle
    glColor3f(0.0f, 0.0f, 0.0f); // Set color to black for the border
    glBegin(GL_QUADS);           // Start drawing a rectangle for the border
    // Calculate and draw vertices for the border, offsetting by the border thickness
    glVertex2f(x - borderThickness, y - borderThickness);
    glVertex2f(x + width + borderThickness, y - borderThickness);
    glVertex2f(x + width + borderThickness, y + height + borderThickness);
    glVertex2f(x - borderThickness, y + height + borderThickness);
    glEnd(); // End drawing the border rectangle

    // Draw the main filled rectangle
    glColor3f(red, green, blue);       // Set the color for the main rectangle
    glBegin(GL_QUADS);                 // Start drawing the main rectangle
    glVertex2f(x, y);                  // Bottom left corner
    glVertex2f(x + width, y);          // Bottom right corner
    glVertex2f(x + width, y + height); // Top right corner
    glVertex2f(x, y + height);         // Top left corner
    glEnd();                           // End drawing the filled rectangle
}

// display ---------------------------------------------------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glLoadIdentity();             // Load the identity matrix
    
    // roof
    drawRectangle(-10, 8.0, 20.0, 5, 0.0f, 0.1f, 0.1f);

    // side light
    drawRectangle(2.5, -7, 3.5, 15, 0.0f, 0.1f, 0.1f);

    // floor
    drawRectangle(-10, -12.0, 20.0, 5, 0.1f, 0.0f, 0.0f);  // Draw a blue rectangle
    
    //trim left
    drawRectangle(-10, -7.4, 3.0, 1, 0.0f, 0.0f, 0.0f);  // Draw a blue rectangle
    
    //trim right
    drawRectangle(6, -7.4, 5.0, 1, 0.0f, 0.0f, 0.0f);  // Draw a blue rectangle

    
    drawDoor();      // Draw the door
    drawDoorFrame(); // Draw the door frame
    // drawGrid();      // Draw the grid

    // Example call to drawRectangle with color parameters
    // Parameters: X, Y, Width, Height, Red, Green, Blue
    drawRectangle(2.5, 2.0, 3.0, 1.5, 1.0f, 1.0f, 1.0f);  // Draw a blue rectangle
    drawRectangle(2.5, -1.0, 3.0, 1.5, 1.0f, 1.0f, 1.0f); // Draw a blue rectangle
    drawRectangle(2.5, -3.0, 3.0, 1.5, 1.0f, 1.0f, 1.0f); // Draw a blue rectangle
    drawRectangle(2.5, -6.0, 3.0, 2.0, 1.0f, 1.0f, 1.0f); // Draw a blue rectangle
    drawRectangle(6.8, 3.0, 3.0, 1.5, 1.0f, 1.0f, 1.0f);  // Draw a blue rectangle
    
    glFlush();                                            // Flush OpenGL pipeline
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
    glutInitWindowSize(800, 900);                // Set window size
    glutCreateWindow("OpenGL Door");             // Create a window with the specified title
    init();                                      // Call initialization function
    glutDisplayFunc(display);                    // Set display callback function
    glutTimerFunc(16, update, 0);                // Call update function
    glutKeyboardFunc(keyboard);                  // Set keyboard callback function
    glutMainLoop();                              // Enter the GLUT event processing loop
    return 0;                                    // Return success
}
