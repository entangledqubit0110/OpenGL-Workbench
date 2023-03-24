#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLfloat theta = 0.0;

void init(void) 
{
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    GLfloat mat_specular[] = { 0, 1, 0, 0.0 };
    GLfloat mat_ambient[] = { 1, 0, 0, 0.0 };
    GLfloat mat_shininess[] = { 40.0 };

    GLfloat light_position[] = { 25.0, 20.0, 25.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glColor3f(1, 0.843, 0);
    glutSolidTeapot(15);

    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(30.0, 0.0, 0.0);
    glColor3f(0, 1, 0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 30.0, 0.0);
    glColor3f(0, 0, 1);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 30.0);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-30, 30, -30, 30, -70, 70);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat eyeY = 5;
    GLfloat eyeX = cos(theta*M_PI/180) * 20;
    GLfloat eyeZ = sin(theta*M_PI/180) * 20;

    gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, 1, 0);
    
}


void spin (int value) {
    theta += 1;
    if (theta > 360) theta -= 360;

    GLfloat eyeY = 5;
    GLfloat eyeX = cos(theta*M_PI/180) * 20;
    GLfloat eyeZ = sin(theta*M_PI/180) * 20;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, 1, 0);

    glutTimerFunc(10, spin, 0);
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (700, 700); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Simple Lighting in OpenGL");
    init ();
    
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutTimerFunc(10, spin, 0);

    glutMainLoop();
    return 0;
}