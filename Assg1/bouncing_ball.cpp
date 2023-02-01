#include <bits/stdc++.h>
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>
#include "bresenham_circle.h"
#include "midpoint_ellipse.h"

using namespace std;


// GLOBAL VARIABLES
int trajectory = 0;


GLfloat ball_radius = 30.0;   // size of the ball

vector<pair<GLfloat, GLfloat>> centers;   // positions of the center of the ball
vector<vector<GLfloat>> ellipses;         // position and measurements of the ellipses

int ellipse = 0;                          // flag for enabling elipse drawing at the bottom of the path
int num_ellipses = 7;                     // number of ellipses to be drawn during transition
int curr_ellipse_count = 0;               // number of ellipses that has been drawn during transition
GLfloat ellipse_deformation[] = {3, 6, 9, 11 , 9, 6, 3};   // the deformation from ball's ideal radius during collision, 5 for 5 ellipses

int draw_trigger = 0; // when trajectory is off, this trigger flags whether the postRedisplay was done after circle condition
                      // or ellipse condition, so as to draw a circle or ellipse conditionally in the display funcntion

int skipNext = 0;     // skip one of the subsequenct 2 cases when h=0, as h=0 happens twice for every collision


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
  if(ellipse == 0){
  
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
      // trigger ellipse drawing
      if(h == 0 && skipNext == 0){
        ellipse = 1;
        curr_ellipse_count = 0;
        skipNext = 1;   // skip the next instance when h=0
      }
      else if(h == 0 && skipNext == 1){ //skip and don't draw ellipse
        skipNext = 0; // do not skip next one, as that will be in next collision
      }

      // circle draw triggered in display function
      draw_trigger = 0;
    }
  }
  else if(ellipse == 1) // draw ellipses compressing vertically
  {
    if(curr_ellipse_count < num_ellipses){
      GLfloat rx = ball_radius + ellipse_deformation[curr_ellipse_count], ry = ball_radius - ellipse_deformation[curr_ellipse_count];
      vector<GLfloat> new_ellipse = {rx, ry, horizontal_velocity*t, h-ellipse_deformation[curr_ellipse_count]};
      ellipses.push_back(new_ellipse);

      curr_ellipse_count++;

      // ellipse draw triggered in display function
      draw_trigger = 1;
    }
    else  // finished ellipse drawing, go back to equation of motion
    {
      ellipse = 0;
      draw_trigger = 0;
    }
  }


  usleep(100000);  // wait before redrawing to make the animation visible 
  glutPostRedisplay() ; // update and repaint with new position included
}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    if(trajectory)
    {
      // draw all the centers that have been pushed in the vector till now
      for(auto itr: centers){
        GLfloat tempX = itr.first, tempY = itr.second;
        bresenhamCircle(tempX, tempY, ball_radius);
      }

      for(auto el: ellipses){
        GLfloat rx = el[0], ry = el[1], xc = el[2], yc = el[3];
        midptellipse(rx, ry, xc, yc);
      }
    }
    else
    {
      // cricle draw triggered
      if(draw_trigger == 0){
        int curr_size = centers.size();
        GLfloat tempX = centers[curr_size-1].first, tempY = centers[curr_size-1].second;
        bresenhamCircle(tempX, tempY, ball_radius);
        // cout << "circle" << tempX << " " << tempY << " " << ball_radius << endl;
      }
      // ellipse drawing triggered
      else if(draw_trigger == 1)
      {
        int curr_size = ellipses.size();
        auto el = ellipses[curr_size-1];
        GLfloat rx = el[0], ry = el[1], xc = el[2], yc = el[3];
        midptellipse(rx, ry, xc, yc);
        // cout << "ellipse" << rx << " " << ry << " " << xc << " " << yc << endl;
      }
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

  // take input from command line
  if(argc == 1){
    cout << "Showing trajectory of the ball by default" << endl;
    trajectory = 1;
  }
  else if(argc == 2){
    sscanf(argv[1], "%d", &trajectory);
    if(trajectory)
      cout << "Trajectory of the ball: ENABLED" << endl;
    else  
      cout << "Trajectory of the ball: DISABLED" << endl;
  }
  else
  {
    cout << "More arguments passed than desired" << endl;
  }


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