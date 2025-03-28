#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>

const float PI = 3.14159265f;

GLfloat ballRadius = 0.1f;
GLfloat ballX = 0.0f;
GLfloat ballY = 0.0f;
GLfloat ballXMax, ballXMin, ballYMax, ballYMin;
GLfloat xSpeed = 0.008f;
GLfloat ySpeed = 0.01f;
GLfloat xAcceleration = 0.0000f;
GLfloat yAcceleration = -0.0005f;
bool isPaused = false;
int refreshMillis = 16;

GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display()
{
    if (isPaused) return;
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(ballX, ballY, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    int numSegments = 100;
    GLfloat angle;
    for (int i = 0; i <= numSegments; i++)
    {
      angle = i * 2.0f * PI / numSegments;
      glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
    }
    glEnd();

    glutSwapBuffers();
    xSpeed += xAcceleration;
    ySpeed += yAcceleration;
    ballX += xSpeed;
    ballY += ySpeed;
    if (ballX > ballXMax)
    {
      ballX = ballXMax;
      xSpeed = -xSpeed;
    }
    else if (ballX < ballXMin)
    {
      ballX = ballXMin;
      xSpeed = -xSpeed;
    }
    if (ballY > ballYMax)
    {
      ballY = ballYMax;
      ySpeed = -ySpeed;
    }
    else if (ballY < ballYMin)
    {
      ballY = ballYMin;
      ySpeed = -ySpeed;
    }
}

void reshape(GLsizei width, GLsizei height)
{
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height)
    {
      clipAreaXLeft = -1.0 * aspect;
      clipAreaXRight = 1.0 * aspect;
      clipAreaYBottom = -1.0;
      clipAreaYTop = 1.0;
    }
    else
    {
      clipAreaXLeft = -1.0;
      clipAreaXRight = 1.0;
      clipAreaYBottom = -1.0 / aspect;
      clipAreaYTop = 1.0 / aspect;
    }
    gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
    ballXMin = clipAreaXLeft + ballRadius;
    ballXMax = clipAreaXRight - ballRadius;
    ballYMin = clipAreaYBottom + ballRadius;
    ballYMax = clipAreaYTop - ballRadius;
}

void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(refreshMillis, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key)
    {
    case 32:
        isPaused = !isPaused; break;
    default: break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("bouncing-ball");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    init();
    glutMainLoop();
    return 0;
}

// Build & Run:
// cmake --build .\build\ --config Debug; .\build\Debug\bounce.exe