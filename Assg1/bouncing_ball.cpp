#include <bits/stdc++.h>
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>
#include "bresenham_circle.h"
#include "midpoint_ellipse.h"

using namespace std;


// GENERAL GLOBAL VARIABLES
int FRAME_DELAY = 60000;    // delay between updating ball's position for animation
int SHOW_TRAJECTORY = 1;    // whether to show the past positions of the ball till now, enabled by default
GLfloat BALL_RADIUS = 30.0;   // size of the ball



// ELLIPSE DRAWING UTILITIES
vector<vector<GLfloat>> ellipses;         // position and measurements of the ellipses

int ellipse = 0;                          // flag for enabling elipse drawing at the bottom of the path
                                          // enabled when collision is detected i.e., h = 0
                                          

int num_ellipses;                         // number of ellipses to be drawn during transition
                                          // determined based on the collision velocity
                                          // has a maximum value of 7 (based on the size of deformations )

int curr_ellipse_count = 0;               // number of ellipses that has been drawn during transition


vector<GLfloat> ellipse_deformation;      // the deformation from ball's ideal radius during collision
                                          // a num_ellipses sized vector

int DRAW_TRIGGER = 0; // when trajectory is off, this trigger flags whether the postRedisplay was done after circle condition
                      // or ellipse condition, so as to draw a circle or ellipse conditionally in the display funcntion

int skipNext = 0;     // skip one of the subsequenct 2 cases when h=0, 
                      // as h=0 happens twice for every collision, once when incoming, once when outgoing



// GLOBAL VARIABLES FOR MOTION OF BALL
vector<pair<GLfloat, GLfloat>> centers;   // positions of the center of the ball
GLfloat horizontal_velocity = 10.0;       // constant throughout the motion

float h0 = 700;             // initial height of the ball
float v = 0;                // m/s, current velocity
const float g = 10;         // m/s^2, accelaration due to gravity, constant
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


// set num_ellipses based on the current collision velocity
void set_ellipses_for_velocity (){
  // static logic for number of ellipses
  if(abs(v) < 20) num_ellipses = 0;
  else if(abs(v) < 40) num_ellipses = 1;
  else if(abs(v) < 80) num_ellipses = 3;
  else num_ellipses = 5;


  // reconstruct the deformation vector
  if(num_ellipses > 0){
    ellipse_deformation.clear();
    ellipse_deformation = vector<GLfloat>(num_ellipses);
    for(int i = 0; i < (num_ellipses/2) + 1; i++){
      ellipse_deformation[i] = 3 * (1 + i);
      ellipse_deformation[num_ellipses-1-i] = 3 * (1 + i);
    }
  }

}


void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel(GL_FLAT);
}



// the function where the ball's motion is updated
void bouncingBall (void){

  // following the equation of motion
  if(ellipse == 0){
    
     // update the position of the center 
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

      // trigger ellipse drawing if collision and incoming
      if(h == 0 && skipNext == 0){
        ellipse = 1;
        curr_ellipse_count = 0;
        skipNext = 1;   // skip the next instance when h=0, i.e., outgoing
        set_ellipses_for_velocity();  // set the number of ellipses
      }
      else if(h == 0 && skipNext == 1){ //skip and don't draw ellipse
        skipNext = 0; // do not skip next one, as that will be in next collision
      }

      // circle draw triggered in display function
      DRAW_TRIGGER = 0;
    }
  }
  else if(ellipse == 1) // draw ellipses compressing vertically
  {
    if(curr_ellipse_count < num_ellipses){  // more ellipses to draw
      // Assume ball is elongated in x and compressed in y by the same amount
      GLfloat rx = BALL_RADIUS + ellipse_deformation[curr_ellipse_count]; // x elongation
      GLfloat ry = BALL_RADIUS - ellipse_deformation[curr_ellipse_count]; // y compression

      // defining measurements of the new ellipse
      vector<GLfloat> new_ellipse = {rx, ry, horizontal_velocity*t, h-ellipse_deformation[curr_ellipse_count]};
      ellipses.push_back(new_ellipse);  // push the ellipse's measurements

      curr_ellipse_count++;

      // ellipse draw triggered in display function
      DRAW_TRIGGER = 1;
    }
    else  // finished ellipse drawing, go back to equation of motion of the circle
    {
      ellipse = 0;
      DRAW_TRIGGER = 0;
    }
  }


  usleep(FRAME_DELAY);  // wait before redrawing to make the animation visible 
  glutPostRedisplay() ; // update and repaint with new position included
}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    if(SHOW_TRAJECTORY)   // we want to draw all past circle and ellipses
    {
      // draw all the centers that have been pushed in the vector till now
      for(auto itr: centers){
        GLfloat tempX = itr.first, tempY = itr.second;
        bresenhamCircle(tempX, tempY, BALL_RADIUS);
      }

      // draw all the ellipses pushed in the vector till now
      for(auto el: ellipses){
        GLfloat rx = el[0], ry = el[1], xc = el[2], yc = el[3];
        midptellipse(rx, ry, xc, yc);
      }
    }
    else
    {
      // cricle draw triggered
      if(DRAW_TRIGGER == 0){    
        // find the last position
        int curr_size = centers.size();
        GLfloat tempX = centers[curr_size-1].first, tempY = centers[curr_size-1].second;
        // draw a circle in the last position
        bresenhamCircle(tempX, tempY, BALL_RADIUS);
      }
      // ellipse drawing triggered
      else if(DRAW_TRIGGER == 1)
      {
        // find the last position
        int curr_size = ellipses.size();
        auto el = ellipses[curr_size-1];
        // draw a ellipse in the last position
        GLfloat rx = el[0], ry = el[1], xc = el[2], yc = el[3];
        midptellipse(rx, ry, xc, yc);

        cout << curr_ellipse_count << " ellipse " << rx << " " << ry << " " << xc << " " << yc << endl; 
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
    gluOrtho2D(0.0-BALL_RADIUS, 1600.0-BALL_RADIUS, 0.0-BALL_RADIUS, 900.0-BALL_RADIUS);

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
    SHOW_TRAJECTORY = 1;
  }
  else if(argc == 2){
    sscanf(argv[1], "%d", &SHOW_TRAJECTORY);
    if(SHOW_TRAJECTORY)
      cout << "Trajectory of the ball: ENABLED" << endl;
    else  
      cout << "Trajectory of the ball: DISABLED" << endl;
  }
  else
  {
    cout << "More arguments passed than desired" << endl;
  }


  // clear the vectors
  centers.clear();
  ellipses.clear();


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