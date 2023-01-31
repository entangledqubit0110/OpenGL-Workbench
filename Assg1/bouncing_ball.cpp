#include <bits/stdc++.h>
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>

using namespace std;

vector<pair<GLfloat, GLfloat>> centers;

GLfloat ball_radius = 30.0;

float h0 = 700;
float v = 0;                // m/s, current velocity
float g = 10;               // m/s^2
float t = 0;                // starting time
float dt = 0.3;               // time step
float rho = 0.85;           // coefficient of restitution
float tau = 0.10;           // contact time for bounce

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


void bresenhamCircle (int Cx, int Cy, int r){
    glPushMatrix();
    glTranslatef(Cx, Cy, 0.0);

        
    GLfloat x = 0, y = r;
    GLfloat p = 3- 2*r;
    while(x < y){
        glPushMatrix();
        glBegin(GL_POINTS);

        glVertex2f(x, y);
        glVertex2f(x, -y);
        glVertex2f(-x, y);
        glVertex2f(-x, -y);

        glVertex2f(y, x);
        glVertex2f(y, -x);
        glVertex2f(-y, x);
        glVertex2f(-y, -x);

        glEnd();
        glPopMatrix();

        if(p < 0){
            p += 4*x + 6;
        }
        else
        {
            p += 4*(x-y) + 10;
            y--;
        }
        x++;
    }

    glPopMatrix();
}


// the ball starts bouncing from height h at x = 0
void bouncingBall (void){
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
        
        centers.push_back(make_pair(10*t, h));
    }
    
    sleep(0.01);
    glutPostRedisplay() ;
}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

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