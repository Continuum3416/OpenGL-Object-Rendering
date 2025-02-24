#include <GL/freeglut.h>

void display() 
{
    // Clear screen with a black background
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f); // Red

    // Draw a triangle
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.6f, -0.6f);
        glVertex2f( 0.6f, -0.6f);
        glVertex2f( 0.0f,  0.6f);
    glEnd();

    // Swap the buffers (display the rendered image)
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // Initialize FreeGLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Double-buffered window with RGB color mode

    // Create a window with a title
    glutCreateWindow("FreeGLUT Test");

    // Set the display callback function
    glutDisplayFunc(display);

    // Start the FreeGLUT main loop
    glutMainLoop();

    return 0;
}

// Build & Run:
// cmake --build .\build\ --config Debug; .\build\Debug\glut.exe