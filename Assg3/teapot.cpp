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

#define ENABLED "ENABLED"
#define DISABLED "DISABLED"
#define STATUS(x) (x)? ENABLED : DISABLED

enum MotionType {
    NORMAL= 0,
    ANGULAR = 1
};

/*
 * ------------------------------------------------------------
 *                      GLOBAL VARIABLES
 * ------------------------------------------------------------
 * size of window
 * eye position variables
 * object color variables
 * mouse control variables
 * light control variables
*/

// size
int width = 700;
int height = 700;

// eye position
GLfloat eye[] = {0.0, 4.0, -10.0};
// color
// background
GLfloat bg_color[] = {0.0, 0.0, 0.0, 1.0};
// teapot
GLfloat teapot_color[] =    {0.6, 0.6, 0.6, 0.6,
                            0.6, 0.6, 0.6, 1.0,
                            0.8, 0.8, 0.8, 1.0};

// mouse control
bool mouseDown = false;
float xrot = 0.0;
float yrot = 0.0;
float xdiff = 0.0;
float ydiff = 0.0;

// control variables


MotionType motionMode = NORMAL;
bool enableAmbient = false;
bool enableViewPoint = false;
bool enableRed = false;
bool enableBlue = false;
bool enableGreen = false;
bool animation = false;
GLfloat red_position[3];
GLfloat blue_position[3];
GLfloat green_position[3];


/**
 * ---------------------------------------------------------------------
 *                          LIGHT CONTROL FUNCTIONS
 * ---------------------------------------------------------------------
 * This section contains the creation methods of red, blue and green lights
 * as well as the ambient and viewpoint lights, conditioned by the control
 * variables truth values.
 * For more details regarding the light parameters, refer to lighting.h
*/

void createAmbientLight () {
    if (enableAmbient) setAmbientLight();
    else unsetAmbientLight();
}

void createRedLight () {
    red_position[0] = red_light_radius * cos(M_PI*red_theta/180.0);
    red_position[1] = red_light_height;
    red_position[2] = red_light_radius * sin(M_PI*red_theta/180.0);
    
    if (enableRed) {
        setRedLight(red_position);
    }
    else 
    {
        unsetRedLight();
    }

    createSource(red_position, enableRed, 1.0, 0.0, 0.0, 0.6);
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

    
    if (enableBlue) {
        setBlueLight(blue_position);
    }
    else {
        unsetBlueLight();
    }

    createSource(blue_position, enableBlue, 0.0, 0.0, 1.0, 0.6);
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
    
    if (enableGreen) 
    {
        setGreenLight(green_position);
    }
    else {
        unsetGreenLight();
    }

    createSource(green_position, enableGreen, 0.0, 1.0, 0.0, 0.6);
}

void createViewPointLight () {
    if (enableViewPoint) setViewPointLight(eye);
    else unsetViewPointLight();
}

/*
 * --------------------------------------------------------------------
 *                              DISPLAY UTILITES 
 * --------------------------------------------------------------------
 * The following section contains the main display function where
 * the light sources are created and teapot is created and colored with
 * material attributes.

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
    createViewPointLight();

    glPushMatrix();
    glRotatef(-xrot, 1.0, 0.0, 0.0);
    glRotatef(yrot, 0.0, 1.0, 0.0);

    createRedLight();
    createBlueLight();
    createGreenLight();
    
    glPushAttrib(GL_LIGHTING_BIT);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, teapot_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, teapot_color + 4);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, teapot_color + 8);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 120.0);
    
    glutSolidTeapot(10);
    
    glPopAttrib();

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

/*
 * --------------------------------------------------------------------------
 *                      EVENT HANDLERS (CONTROL AND MOTION)
 * --------------------------------------------------------------------------
 * The following section handles the user input controlling the ON/OFF events
 * of all the lights. Also the mouse drag movement is handled here.
 * The Key controls are:
 * L: ON/OFF global ambient lighting
 * V: ON/OFF viewpoint lighting
 * R: ON/OFF red light
 * B: ON/OFF blue light
 * G: ON/OFF green light
 * A: ON/OFF animation
 * U: reset the position of the object and lights
*/

void processSpecialKey (int key, int x, int y){

    if (key == GLUT_KEY_DOWN){
        for(int i = 0; i < 3; i++) rotation_amt[i] = max(rotation_amt[i] - 0.5, 0.5);
    }
    else if (key == GLUT_KEY_UP){
        for(int i = 0; i < 3; i++) rotation_amt[i] = min(rotation_amt[i] + 0.5, 10.0);
    }

    glutPostRedisplay();
}

void keyboardHandler (unsigned char c, int x, int y) {
    // ambient light on/off
    if (c == 'L' || c == 'l'){
        enableAmbient = !enableAmbient;
        string status = STATUS(enableAmbient);
        cout << "[GLOBAL LIGHTING]: " << status << endl;
    }
    // viewpoint light on/off
    if (c == 'V' || c == 'v'){
        enableViewPoint = !enableViewPoint;
        string status = STATUS(enableViewPoint);
        cout << "[VIEWPOINT LIGHT]: " << status << endl;
    }
    // reset rotated postion
    if (c == 'U' || c == 'u'){
        xrot = 0.0;
        yrot = 0.0;
        red_theta = -120.0;
        blue_theta = 0.0;
        green_theta = 120.0;
        animation = false;
        cout << "[RESET POSITION]: Success" << endl;
    }
    // red light
    if (c == 'R' || c == 'r'){
        enableRed = !enableRed;
        string status = STATUS(enableRed);
        cout << "[RED LIGHT]: " << status << endl;
    }
    // blue light
    if (c == 'B' || c == 'b'){
        enableBlue = !enableBlue;
        string status = STATUS(enableBlue);
        cout << "[BLUE LIGHT]: " << status << endl;
    }
    // green light
    if (c == 'G' || c == 'g'){
        enableGreen = !enableGreen;
        string status = STATUS(enableGreen);
        cout << "[GREEN LIGHT]: " << status << endl;
    }
    // animation
    if (c == 'A' || c== 'a'){
        animation = !animation;
        string status = STATUS(animation);
        cout << "[ANIMATION]: " << status << endl;
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

// set rotation type according to passed cmd line argument
void setRotationType (int argc, char** argv){
    if (argc > 1){
        string arg = argv[1];
        if (arg == "ANGULAR"){
            motionMode = ANGULAR;
        }
        else
        {
            motionMode = NORMAL;
        }
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    setRotationType(argc, argv);


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
    glutSpecialFunc(processSpecialKey);
    glutMainLoop();
    return 0;
}