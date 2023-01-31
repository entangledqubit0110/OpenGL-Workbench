#include <GL/glut.h>
#include <math.h>


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
void bouncingBall (int h0){

    float v = 0;             // m/s, current velocity
    float g = 10;            // m/s^2
    float t = 0;             // starting time
    float dt = 0.5;        // time step
    float rho = 0.85;        // coefficient of restitution
    float tau = 0.10;        // contact time for bounce
    float hmax = h0;         // keep track of the maximum height

    float h = h0;
    float hstop = 1;         // stop when bounce is less than 1
    int freefall = 1;       // state: freefall or in contact

    float t_last = -sqrt(2*h0/g);    // time we would have launched to get to h0 at t=0
    float vmax = sqrt(2 * hmax * g);


    while(hmax > hstop){
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
        
        // glPushMatrix();
        // glBegin(GL_POINTS);
        // glVertex2f(10*t, h);
        // glEnd();
        // glPopMatrix();
        
        bresenhamCircle(10*t, h, 50);
    }


}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50.0, 1600.0-50.0, -50.0, 900.0-50.0);


    glColor3f(1.0, 0.0, 0.0);
    bouncingBall(700);

    glFlush();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv) ;
  glutInitDisplayMode(GLUT_RGB) ;
  glutInitWindowSize(800,450) ;
  glutInitWindowPosition(100,100) ;
  glutCreateWindow("Bouncing ball") ;
  init() ;
  glutDisplayFunc(display) ;
  glutMainLoop() ;
}