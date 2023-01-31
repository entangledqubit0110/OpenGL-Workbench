#include<GL/glut.h>

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel(GL_FLAT);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(20, 20);
    glVertex2f(400, 20);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(20, 20);
    glVertex2f(20, 400);
    glEnd();

    glPointSize(7);
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(100, 50); 
    glVertex2f(100, 150); 
    glVertex2f(200, 200);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(200, 100); 
    glVertex2f(300, 100); 
    glVertex2f(250, 200);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glRectf(250, 250, 350, 350);
    


    glFlush();

}

int main(int argc, char** argv)
{
  glutInit(&argc, argv) ;
  glutInitDisplayMode(GLUT_RGB) ;
  glutInitWindowSize(500,500) ;
  glutInitWindowPosition(100,100) ;
  glutCreateWindow("Tutorial 2") ;
  init() ;
  glutDisplayFunc(display) ;
  glutMainLoop() ;
}