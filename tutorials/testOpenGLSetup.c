#include <GL/glut.h>

void display ()
{
  glClearColor(0.0, 0.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  // glutSolidTeapot(.5);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 2.0, -1.0, 2.0, -1.0, 1.0);

  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex2f(0.25, 0.25);
  glVertex2f(0.75, 0.25);
  glVertex2f(0.75, 0.75);
  glVertex2f(0.25, 0.75);
  glEnd();

  glFlush();
}

int main ( int argc, char * argv[] )
{
  glutInit(&argc,argv);
  glutInitWindowSize(500,500);
  glutInitWindowPosition(0,0);
  glutInitDisplayMode(GLUT_RGB);
  glutCreateWindow("My first openGL program!");
  glutDisplayFunc(display);
  glutMainLoop();
}