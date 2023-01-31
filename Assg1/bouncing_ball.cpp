#include <bits/stdc++.h>
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>
#include "bresenham_circle.h"

using namespace std;


// GLOBAL VARIABLES
GLfloat ball_radius = 30.0;   // size of the ball
vector<pair<GLfloat, GLfloat>> centers;   // positions of the center of the ball


// GLOBAL VARIABLES FOR MOTION OF BALL
GLfloat horizontal_velocity = 10.0;     // constant throughout the motion

float h0 = 700;             // initial height of the ball
float v = 0;                // m/s, current velocity
const float g = 10;         // m/s^2, accelaration due to gravity
float t = 0;                // starting time

float rho = 0.85;           // coefficient of restitution
float tau = 0.10;           // contact time for bounce
float dt = 0.3;             // time step

float hmax;
float h;
float hstop;
int freefall;
float t_last;
float vmax;


void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel(GL_FLAT);
}


void bouncingBall (void){

  // update the position of the center 
  // following the equation of motion
  if(hmax > hstop){
    if(freefall){
        float hnew = h + v*dt - 0.5*g*dt*dt;
        if (hnew < 0){
            t = t_last + 2*sqrt(2*hmax/g);
            freefall = 0;
            t_last = t + tau;
            h = 0;
        }
        else
        {
            t = t + dt;
            v = v - g*dt;
            h = hnew;
        }
    }
    else
    {
        t = t + tau;
        vmax = vmax * rho;
        v = vmax;
        freefall = 1;
        h = 0;
    }
    hmax = 0.5*vmax*vmax/g;
      
    // push the position of center 
    centers.push_back(make_pair(horizontal_velocity*t, h));
  }


  sleep(0.01);  // wait before redrawing to make the animation visible 
  glutPostRedisplay() ; // update and repaint with new position included
}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    // draw all the centers that have been pushed in the vector till now
    for(auto itr: centers){
      bresenhamCircle(itr.first, itr.second, ball_radius);
    }

    glutSwapBuffers() ;
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei) w,(GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // make so that the ball touches the lower boundary
    gluOrtho2D(0.0-ball_radius, 1600.0-ball_radius, 0.0-ball_radius, 900.0-ball_radius);

}


void mouse(int button, int state, int x, int y)
{
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN)
        glutIdleFunc(bouncingBall) ;
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

  // clear the vector
  centers.clear();


  // initialize motion variables
  hmax = h0;                // keep track of the maximum height
  h = h0;                   // initialize height to h0
  hstop = 1;                // stop when bounce is less than 1
  freefall = 1;             // state: freefall or in contact
  t_last = -sqrt(2*h0/g);   // time we would have launched to get to h0 at t=0
  vmax = sqrt(2 * hmax * g);

  // first position
  centers.push_back(make_pair(0.0, h0));

  glutInit(&argc, argv) ;
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB) ;
  glutInitWindowSize(1000,562.5) ;
  glutInitWindowPosition(100,100) ;
  glutCreateWindow("Bouncing ball") ;
  init() ;
  glutDisplayFunc(display) ;
  glutReshapeFunc(reshape) ;
  glutMouseFunc(mouse) ;
  glutMainLoop() ;
}