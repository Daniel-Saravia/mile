#include <GL/glut.h> // Include OpenGL Utility Toolkit library
#include <cstdio>
#include <math.h>
#include <GL/glext.h>



// Defines the initial angle of the door, used to rotate the door around the y-axis
float doorAngle = 0.0f;

// init ---------------------------------------------------------------------------------
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set clear color to white

    glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling

    glMatrixMode(GL_PROJECTION); // Set the current matrix mode to projection
    glLoadIdentity(); // Load the identity matrix

    // Set up a perspective projection matrix
    gluPerspective(45.0, // Field of view angle
                   1.0, // Aspect ratio (you might want to make this dynamic)
                   0.1, // Near clipping plane
                   100.0); // Far clipping plane

    glMatrixMode(GL_MODELVIEW); // Set the current matrix mode to modelview
    glLoadIdentity(); // Load the identity matrix

    // Set the camera position and orientation
    gluLookAt(0.0, 0.0, 10.0, // Eye position (x, y, z)
              0.0, 0.0, 0.0, // Center of the scene (x, y, z)
              0.0, 1.0, 0.0); // Up vector (x, y, z)
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
    glPushMatrix(); // Push the current matrix onto the stack

    glColor3f(0.78, 0.74, 0.66); // Set door color to brown

    // Translate to the position where the door will be drawn
    glTranslatef(-3.0, 0.0, 0.0); 

    // Rotate the door around the y-axis
    glRotatef(doorAngle, 0.0, 1.0, 0.0);

    // Start drawing a 3D rectangular prism for the door
    glBegin(GL_QUADS);

    // Front face
    glVertex3f(-4.0, -7.0, 0.0);
    glVertex3f(-4.0, 8.0, 0.0);
    glVertex3f(5.0, 8.0, 0.0);
    glVertex3f(5.0, -7.0, 0.0);

    // Back face
    glVertex3f(-4.0, -7.0, -0.5);
    glVertex3f(-4.0, 8.0, -0.5);
    glVertex3f(5.0, 8.0, -0.5);
    glVertex3f(5.0, -7.0, -0.5);

    // Connect the sides
    // Left Side
    glVertex3f(-4.0, -7.0, 0.0);
    glVertex3f(-4.0, 8.0, 0.0);
    glVertex3f(-4.0, 8.0, -0.5);
    glVertex3f(-4.0, -7.0, -0.5);

    // Right Side
    glVertex3f(5.0, -7.0, 0.0);
    glVertex3f(5.0, 8.0, 0.0);
    glVertex3f(5.0, 8.0, -0.5);
    glVertex3f(5.0, -7.0, -0.5);

    // Top
    glVertex3f(-4.0, 8.0, 0.0);
    glVertex3f(5.0, 8.0, 0.0);
    glVertex3f(5.0, 8.0, -0.5);
    glVertex3f(-4.0, 8.0, -0.5);

    // Bottom
    glVertex3f(-4.0, -7.0, 0.0);
    glVertex3f(5.0, -7.0, 0.0);
    glVertex3f(5.0, -7.0, -0.5);
    glVertex3f(-4.0, -7.0, -0.5);

    glEnd(); // End drawing the door

    glPopMatrix(); // Pop the current matrix from the stack
}

// Function to draw a simple rectangle with color parameters and a simulated thicker black border
void drawRectangle(float x, float y, float z, float width, float height, float depth, float red, float green, float blue)
{
    // Offset for the border thickness
    float borderThickness = 0.1f; // Adjust this value to change the border thickness

    // Main rectangle color
    glColor3f(red, green, blue);

    // Draw the main filled box (rectangular prism)
    glBegin(GL_QUADS);

    // Front face
    glVertex3f(x, y, z);
    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y + height, z);
    glVertex3f(x, y + height, z);

    // Back face
    glVertex3f(x, y, z - depth);
    glVertex3f(x + width, y, z - depth);
    glVertex3f(x + width, y + height, z - depth);
    glVertex3f(x, y + height, z - depth);

    // Top face
    glVertex3f(x, y + height, z);
    glVertex3f(x + width, y + height, z);
    glVertex3f(x + width, y + height, z - depth);
    glVertex3f(x, y + height, z - depth);

    // Bottom face
    glVertex3f(x, y, z);
    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y, z - depth);
    glVertex3f(x, y, z - depth);

    // Right face
    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y + height, z);
    glVertex3f(x + width, y + height, z - depth);
    glVertex3f(x + width, y, z - depth);

    // Left face
    glVertex3f(x, y, z);
    glVertex3f(x, y + height, z);
    glVertex3f(x, y + height, z - depth);
    glVertex3f(x, y, z - depth);

    glEnd();

    // Draw the border
    glColor3f(0.0f, 0.0f, 0.0f); // Set color to black for the border

    // Draw border lines around the box to simulate a thicker border
    glLineWidth(borderThickness * 10); // Adjust line width for visible border

    glBegin(GL_LINES);

    // Front face borders
    glVertex3f(x, y, z);
    glVertex3f(x + width, y, z);

    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y + height, z);

    glVertex3f(x + width, y + height, z);
    glVertex3f(x, y + height, z);

    glVertex3f(x, y + height, z);
    glVertex3f(x, y, z);

    // Connect front face to back face
    glVertex3f(x, y, z);
    glVertex3f(x, y, z - depth);

    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y, z - depth);

    glVertex3f(x + width, y + height, z);
    glVertex3f(x + width, y + height, z - depth);

    glVertex3f(x, y + height, z);
    glVertex3f(x, y + height, z - depth);

    // Back face borders
    glVertex3f(x, y, z - depth);
    glVertex3f(x + width, y, z - depth);

    glVertex3f(x + width, y, z - depth);
    glVertex3f(x + width, y + height, z - depth);

    glVertex3f(x + width, y + height, z - depth);
    glVertex3f(x, y + height, z - depth);

    glVertex3f(x, y + height, z - depth);
    glVertex3f(x, y, z - depth);

    glEnd();
}


// display ---------------------------------------------------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
    glLoadIdentity(); // Reset the view

    // Set up the camera position, looking at the center of the scene
    gluLookAt(0.0, 0.0, 30.0, // Camera position in World Space
              0.0, 0.0, 0.0, // Looks at the origin
              0.0, 1.0, 0.0); // Head is up (set to 0,-1,0 to look upside-down)

    // Adjust the positions, sizes, and add the depth parameter for 3D rectangles
    // For the purpose of this example, I'll define a generic depth for all objects
    float depth = 0.5f; // Example depth

    // adjust x, y, z, width, height, and depth values for your scene

    // trim right
    drawRectangle(6, -7.4, 0, 5.0, 1, depth, 0.0f, 0.0f, 0.0f);

    // trim right
    drawRectangle(6, -7.4, 0, 5.0, 1, depth, 0.0f, 0.0f, 0.0f);

    // roof
     drawRectangle(-10, 8.0, 0, 20.0, 7, depth, 0.0f, 0.1f, 0.1f);

    // side light
    drawRectangle(2.5, -7, 0, 3.5, 15, depth, 0.0f, 0.1f, 0.1f);

    // wall Right side
    drawRectangle(6.1, -6.5, 0, 4, 14.5, depth, 1.0f, 1.0f, 1.0f);

    // wall left side
    drawRectangle(-10, -7, 0, 2.5, 15, depth, 1.0f, 1.0f, 1.0f);

    // steel left door frame
    drawRectangle(-7.6, -7, 0, 0.5, 15, depth, 0.5f, 0.5f, 0.5f);

    

    // steel center door frame
    drawRectangle(2, -7, 0, 0.5, 15, depth, 0.5f, 0.5f, 0.5f);

    // steel right door frame
    drawRectangle(6, -7, 0, 0.5, 15, depth, 0.5f, 0.5f, 0.5f);

    /// steel TOP door frame
    drawRectangle(-7.6, 8, 0, 14, 0.5, depth, 0.5f, 0.5f, 0.5f);



    // floor
    drawRectangle(-10, -12.0, 0, 20.0, 5, depth, 0.1f, 0.0f, 0.0f);

    // trim left
    drawRectangle(-10, -7.4, 0, 3.0, 1, depth, 0.0f, 0.0f, 0.0f);

    

    // Drawing 3D objects
    drawDoor(); // Draw the door in 3D

    // Windows or other rectangles (adjusting parameters to match 3D function signature)
    drawRectangle(2.5, 2.0, 0, 3.0, 1.5, depth, 1.0f, 1.0f, 1.0f);
    drawRectangle(2.5, -1.0, 0, 3.0, 1.5, depth, 1.0f, 1.0f, 1.0f);
    drawRectangle(2.5, -3.0, 0, 3.0, 1.5, depth, 1.0f, 1.0f, 1.0f);
    drawRectangle(2.5, -6.0, 0, 3.0, 2.0, depth, 1.0f, 1.0f, 1.0f);
    drawRectangle(6.8, 3.0, 0, 3.0, 1.5, depth, 1.0f, 1.0f, 1.0f);

    // If using double buffering, swap the buffers to display what just got rendered.
    // glFlush(); // Use this if single buffering
    glutSwapBuffers(); // Use this for double buffering
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
