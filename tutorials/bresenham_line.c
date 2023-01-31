#include <GL/glut.h>
#include <math.h>

int begin[2] = {5, 6};
int end[2] = {10, 100};


void init(void)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}


void displayLine(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 250.0, 0.0, 250.0);

    int x = begin[0], y = begin[1];
    int dx = end[0] - begin[0], dy = end[1] - begin[1];
    int p = 2*dy - dx;
    while(x <= end[0]){
        glPushMatrix();
        glPointSize(1);
        glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(x, y);
        glEnd();
        glPopMatrix();

        x++;

        if(p < 0){
            p += 2*dy;
        }
        else
        {
            p += (2*dy - 2*dx);
            y++;
        }
    }

    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(begin[0], begin[1]);
    glVertex2f(end[0], end[1]);
    glEnd();
    glPopMatrix();

    glFlush();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Bresenham Line");
    init() ;
    glutDisplayFunc(displayLine);
    glutMainLoop() ;
}
