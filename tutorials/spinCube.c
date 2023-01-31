#include <math.h>
#include <GL/glut.h>
#define PI M_PI


static GLfloat spin[] = {0.0f, 0.0f, 0.0f} ;

void init(void)
{
  glEnable(GL_DEPTH_TEST);
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel(GL_FLAT);
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT) ;

  glPushMatrix();
  glRotatef(spin[0], 0.0, 1.0, 0.0);

  glColor3f(0.0, 1.0, 0.0);
  glutWireCube(3);

  GLfloat inner_vertices[] = {
                          1.5, 1.5, 1.5,
                          1.5, 1.5, -1.5,
                          1.5, -1.5, 1.5,
                          -1.5, 1.5, 1.5,
                          -1.5, -1.5, 1.5,
                          1.5, -1.5, -1.5,
                          -1.5, 1.5, -1.5,
                          -1.5, -1.5, -1.5
                      };

  glColor3f(0.0,0.5,0.5);
  GLUquadric *quad_inner[9];
  for(int i = 0; i < 24; i+=3){
    glPushMatrix();
    quad_inner[i] = gluNewQuadric();
    glTranslatef(inner_vertices[i], inner_vertices[i+1], inner_vertices[i+2]);
    gluSphere(quad_inner[i],0.2,50,10);
    glPopMatrix();
  }


  glPopMatrix(); 


  glPushMatrix() ;
  glRotatef(spin[1], 0.0, 0.0, 1.0) ;

  glColor3f(1.0, 0.0, 0.0);
  glutWireCube(5);

  GLfloat outer_vertices[] = {
                          2.5, 2.5, 2.5,
                          2.5, 2.5, -2.5,
                          2.5, -2.5, 2.5,
                          -2.5, 2.5, 2.5,
                          -2.5, -2.5, 2.5,
                          2.5, -2.5, -2.5,
                          -2.5, 2.5, -2.5,
                          -2.5, -2.5, -2.5
                      };

  glColor3f(0.5,0.35,0.0);
  GLUquadric *quad_outer[9];
  for(int i = 0; i < 24; i+=3){
    glPushMatrix();
    quad_outer[i] = gluNewQuadric();
    glTranslatef(outer_vertices[i], outer_vertices[i+1], outer_vertices[i+2]);
    gluSphere(quad_outer[i],0.3,50,10);
    glPopMatrix();
  }

  
  glPopMatrix();

  glPushMatrix() ;
  glRotatef(spin[2], 1.0, 0.0, 0.0) ;

  glColor3f(0.0, 0.0, 1.0);
  glutWireCube(7);

  GLfloat orbit_vertices[] = {
                          3.5, 3.5, 3.5,
                          3.5, 3.5, -3.5,
                          3.5, -3.5, 3.5,
                          -3.5, 3.5, 3.5,
                          -3.5, -3.5, 3.5,
                          3.5, -3.5, -3.5,
                          -3.5, 3.5, -3.5,
                          -3.5, -3.5, -3.5
                      };

  glColor3f(0.5,0.0,0.5);
  GLUquadric *quad_orbit[9];
  for(int i = 0; i < 24; i+=3){
    glPushMatrix();
    quad_orbit[i] = gluNewQuadric();
    glTranslatef(orbit_vertices[i], orbit_vertices[i+1], orbit_vertices[i+2]);
    gluSphere(quad_orbit[i],0.4,50,10);
    glPopMatrix();
  }

  // glColor3f(0.0, 0.0, 1.0);
  // glutWireCube(7);

  glPopMatrix();




  glutSwapBuffers() ;

}

void spinDisplay(void)
{
  for(int i = 0; i < 3; i++){
    spin[i] = spin[i] + 0.4*(i+1) ;
    if (spin[i] > 360.0)
      spin[i] = spin[i] - 360.0 ;
  }
  glutPostRedisplay() ;
}

void reshape(int w, int h)
{
  glViewport(0,0,(GLsizei) w,(GLsizei) h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, 1, 0, 100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(10.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void mouse(int button, int state, int x, int y)
{
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN)
        glutIdleFunc(spinDisplay) ;
      break ;
    case GLUT_RIGHT_BUTTON:
      if (state == GLUT_DOWN)
        glutIdleFunc(NULL) ;
      break ;
    default:
    break ;
  }
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv) ;
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB) ;
  glutInitWindowSize(500,500) ;
  glutInitWindowPosition(100,100) ;
  glutCreateWindow("Spinning Cube") ;
  init() ;
  glutDisplayFunc(display) ;
  glutReshapeFunc(reshape) ;
  glutMouseFunc(mouse) ;
  glutMainLoop() ;
}