#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>

GLfloat spin[] = {-15.0, -15.0, 0.0};

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel(GL_FLAT);
}


void drawSquare (float a, int r, int g, int b){

    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    
    glVertex3f(-a/2, -a/2, a/2);
    glVertex3f(a/2, -a/2, a/2);
    glVertex3f(a/2, a/2, a/2);
    glVertex3f(-a/2, a/2, a/2);

    glEnd();
}

void drawColoredCube (int side){

    drawSquare(side, 1, 0, 0);        // draw the square

    glPushMatrix();
        glRotatef(90, 1.0, 0.0, 0.0);    // the top side
        drawSquare(side, 0, 1, 0);      // draw the square
    glPopMatrix();

    glPushMatrix();
        glRotatef(-90, 1.0, 0.0, 0.0);   // the bottom side
        drawSquare(side, 0, 0, 1);      // draw the square
    glPopMatrix();

    glPushMatrix();
        glRotatef(180, 1.0, 0.0, 0.0);    // the back side
        drawSquare(side, 0, 1, 1);      // draw the square
    glPopMatrix();

    glPushMatrix();
        glRotatef(-90, 0.0, 1.0, 0.0);    // the left side
        drawSquare(side, 1, 1, 0);      // draw the square
    glPopMatrix();

    glColor3f(1.0, 0.0, 1.0);
    glPushMatrix();
        glRotatef(90, 0.0, 1.0, 0.0);    // the right side
        drawSquare(side, 1, 0, 1);      // draw the square
    glPopMatrix();

}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();     // whole block  
    glRotatef(spin[2], 0.0, 0.0, 1.0);  // rotate around z-axis
    glRotatef(spin[1], 1.0, 0.0, 0.0);  // rotate around x-axis
    glRotatef(spin[0], 0.0, 1.0, 0.0);  // rotate around y-axis

    drawColoredCube(7);
    glPopMatrix();  // whole block end
    glutSwapBuffers();
}


void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei) w,(GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10);
    
}

void processSpecialKey (int key, int x, int y){

    if (key == GLUT_KEY_LEFT){
        spin[0] -= 5.0;
    }
    else if (key == GLUT_KEY_RIGHT){
        spin[0] += 5.0;
    }
    else if (key == GLUT_KEY_DOWN){
        spin[1] += 5.0;
    }
    else if (key == GLUT_KEY_UP){
        spin[1] -= 5.0;
    }
    else if (key == GLUT_KEY_F11){
        spin[2] -= 5.0;
    }
    else if (key == GLUT_KEY_F12){
        spin[2] += 5.0;
    }
    else if (key == GLUT_KEY_F1){
        spin[0] = 0;
        spin[1] = 0;
        spin[2] = 0;
    }

    glutPostRedisplay();
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv) ;
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH) ;
    glutInitWindowSize(700,700) ;
    glutInitWindowPosition(100,100) ;
    glutCreateWindow("Bouncing ball") ;
    init() ;
    glutDisplayFunc(display) ;
    glutReshapeFunc(reshape) ;
    glutSpecialFunc(processSpecialKey);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop() ;
}