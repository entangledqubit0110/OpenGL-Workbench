/**
 * NAME: ROUNAK PATRA
 * ROLL: 18CS30048
 * EMAIL: rounakpatra2000@gmail.com 
*/

#include <bits/stdc++.h>
#include <math.h>
#include <GL/glut.h>
#include "lighting.h"

using namespace std;

/**
 * ------------------------------------------------------------
 *                      GLOBAL VARIABLES
 * ------------------------------------------------------------
 * size of window
 * eye position variables
 * background color variables
 * mouse control variables
 * light control variables
**/

// size
int width = 700;
int height = 700;

// eye position
GLfloat eye[] = {0.0, 4.0, -10.0};
// color
GLfloat bg_color[] = {0.0, 0.0, 0.0, 1.0};

// mouse control
bool mouseDown = false;
float xrot = 0.0;
float yrot = 0.0;
float xdiff = 0.0;
float ydiff = 0.0;

// control variables
int motionMode = 0;
bool enableAmbient = false;
bool enableRed = false;
bool enableBlue = false;
bool enableGreen = false;
bool animation = false;
GLfloat red_position[3];
GLfloat blue_position[3];
GLfloat green_position[3];


/*
 * CONTROL FUNCTIONS
*/

void createAmbientLight () {
    if (enableAmbient) setAmbientLight();
    else unsetAmbientLight();
}

void createRedLight () {
    red_position[0] = red_light_radius * cos(M_PI*red_theta/180.0);
    red_position[1] = red_light_height;
    red_position[2] = red_light_radius * sin(M_PI*red_theta/180.0);
    
    if (enableRed) setRedLight(red_position);
    else unsetRedLight();

}

void createBlueLight () {
    blue_position[0] = blue_light_radius * cos(M_PI*blue_theta/180.0);
    blue_position[2] = blue_light_radius * sin(M_PI*blue_theta/180.0);
    switch(motionMode){
        case 0:
            blue_position[1] = blue_light_height;
            break;
        case 1:
            blue_position[1] = blue_position[2];
            break;
        default:
            blue_position[1] = blue_light_height;
    }

    
    if (enableBlue) setBlueLight(blue_position);
    else unsetBlueLight();

}

void createGreenLight () {
    green_position[0] = green_light_radius * cos(M_PI*green_theta/180.0);
    green_position[2] = green_light_radius * sin(M_PI*green_theta/180.0);
    switch (motionMode){
        case 0:
            green_position[1] = green_light_height;
            break;
        case 1:
            green_position[1] = -green_position[2];
            break;
        default:
            green_position[1] = green_light_height;
    }
    
    if (enableGreen) setGreenLight(green_position);
    else unsetGreenLight();

}

/*
 * DISPLAY UTILITES 
*/

void init(void) 
{
    glClearColor (bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    createAmbientLight();

    glPushMatrix();
    glRotatef(-xrot, 1.0, 0.0, 0.0);
    glRotatef(yrot, 0.0, 1.0, 0.0);

    createRedLight();
    createBlueLight();
    createGreenLight();
    
    glutSolidTeapot(10);
    glPopMatrix();
    
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-30, 30, -30, 30, -40, 40);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboardHandler (unsigned char c, int x, int y) {
    // ambient light on/off
    if (c == 'M' || c == 'm'){
        enableAmbient = !enableAmbient;
        cout << "Global Light = " << enableAmbient << endl;
    }
    // reset rotated postion
    if (c == 'U' || c == 'u'){
        xrot = 0.0;
        yrot = 0.0;
        red_theta = -120.0;
        blue_theta = 0.0;
        green_theta = 120.0;
        animation = false;
        cout << "Reset Position: Success" << endl;
    }
    // red light
    if (c == 'R' || c == 'r'){
        enableRed = !enableRed;
        cout << "Red Light = " << enableRed << endl;
    }
    // blue light
    if (c == 'B' || c == 'b'){
        enableBlue = !enableBlue;
        cout << "Blue Light = " << enableBlue << endl;
    }
    // green light
    if (c == 'G' || c == 'g'){
        enableGreen = !enableGreen;
        cout << "Green Light = " << enableGreen << endl;
    }
    // animation
    if (c == 'A' || c== 'a'){
        animation = !animation;
        if(animation){
            glutIdleFunc(spinLights);
        }
        else
        {
            glutIdleFunc(NULL);
        }
    }
    glutPostRedisplay();
}


void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else
        mouseDown = false;
}

void mouseMotion(int x, int y)
{
    if (mouseDown)
    {
        yrot = x - xdiff;
        xrot = y + ydiff;
        glutPostRedisplay();
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (width, height); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Satelites");

    init ();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardHandler);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutMainLoop();
    return 0;
}