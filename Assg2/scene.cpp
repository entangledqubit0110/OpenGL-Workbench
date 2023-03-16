#include <bits/stdc++.h>
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>

#include "basic_shapes.h"
#include "constants.h"

using namespace std;

// GLOBAL VARIABLES
// DAY-NIGHT CYCLE
GLfloat dayCycleSpin = 30;      // rotation to dictate position of sun and moon
GLfloat sunSpin = 0;            // rotate sun around its center

// CAR MOVEMENT
GLfloat moveForward = -250;     // translation of the car along horizontal axis
GLfloat wheelSpin = 0;        // spin of the wheels, clockwise as the car moves from left to right

// SKYCOLOR
GLfloat skycolor[3] = {0.0, 0.0, 0.0};

                

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glShadeModel(GL_FLAT);
}


// set the sky's color from current angle of sun & moon
void setSkyColor () {
    int colorIdx = 0;
    // day time
    if (dayCycleSpin < 180){
        // rising sun
        if (dayCycleSpin < 90){
            colorIdx = int(dayCycleSpin) / 18;
        }
        // falling sun
        else if (dayCycleSpin > 90)
        {
            colorIdx = 4 - (int(dayCycleSpin - 90) / 18);
        }
        else
        {
            colorIdx = 4;
        }

        for(int i = 0; i < 3; i++) skycolor[i] = SKYDAY[colorIdx][i]/255.0;

    }
    // night
    else
    {
        // rising moon
        GLfloat theta = dayCycleSpin - 180;
        if (theta < 90){
            colorIdx = int(theta) / 18;
        }
        // falling sun
        else if (theta > 90)
        {
            colorIdx = 4 - (int(theta - 90) / 18);
        }
        else
        {
            colorIdx = 90;
        }

        for(int i = 0; i < 3; i++) skycolor[i] = SKYNIGHT[colorIdx][i]/255.0;
    }

}



// draw windows
void drawWindow () {
    glScalef(20, 30, 1);
    // border
    glColor3f(0, 0, 0);
    drawUnitSqaureLoop();
    
    // window
    glColor3f(0.5, 0.5, 0.5);
    drawUnitSqaure();
    
    // window bars
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(0, -0.5, 0.1);
    glVertex3f(0, 0.5, 0.1);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-0.25, -0.5, 0.1);
    glVertex3f(-0.25, 0.5, 0.1);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.25, -0.5, 0.1);
    glVertex3f(0.25, 0.5, 0.1);
    glEnd();
}

// draw doors
void drawDoor () {
    // door opening
    glScalef(40, 60, 1);
    glColor3f(0.5, 0.5, 0.5);
    drawUnitSqaure();

    glTranslatef(0, 0, 0.1);
    
    // wooden door
    glColor3f(0.6, 0.3, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.5, 0);
    glVertex3f(-0.5, 0.5, 0);
    glVertex3f(0.3, 0.3, 0);
    glVertex3f(0.3, -0.3, 0);
    glEnd();
}


// draw sun and moon
void drawSunAndMoon (){
    glPushMatrix();
    glRotatef(dayCycleSpin, 0, 0, 1);      // rotation for day-night cycle

    // sun
    glPushMatrix();
    glTranslatef(150, 0, -3);
    glRotatef(sunSpin, 0, 0, 1);    // rotation around center

    glColor3f(0.9, 0.8, 0.1);
    // sun rays
    int num_rays = 8;
    for (int i = 0; i < num_rays; i++){
        glPushMatrix();
        glRotatef(i*(360.0/float(num_rays)), 0, 0, 1);
        glTranslatef(30, 0, 0);

        glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(15, 0, 0);
        glEnd();
        glPopMatrix();
    }

    // sun circle
    drawCircle(30, 40);
    glPopMatrix();

    // moon
    glPushMatrix();
    glTranslatef(-150, 0, -3);
    glColor3f(0.9, 0.9, 0.9);
    drawCircle(30, 40);
    glPopMatrix();

    glPopMatrix();

    // covering circle of background color to render moon as curved shape
    GLfloat moonX = -150*cos(dayCycleSpin*M_PI/180.0);
    GLfloat moonY = -150*sin(dayCycleSpin*M_PI/180.0);
    glPushMatrix();
    glTranslatef(moonX-15, moonY+15, -2.5);
    glColor3f(skycolor[0], skycolor[1], skycolor[2]);
    drawCircle(40, 40);
    glPopMatrix();


}

void drawWheel () {
    glPushMatrix();
    glTranslatef(0, -130, 0.3);
    glRotatef(-wheelSpin, 0, 0, 1);

    // spokes
    int num_spokes = 6;
    for (int i = 0; i < num_spokes; i++){
        glPushMatrix();
        glRotatef(i*(180.0/float(num_spokes)), 0, 0, 1);

        glBegin(GL_LINES);
        glColor3f(1, 1, 1);
        glVertex3f(0, 0, 0);
        glVertex3f(10, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(-10, 0, 0);
        glEnd();
        glPopMatrix();
    }

    glColor3f(0.5, 0.6, 0.7);
    drawLoop(10, 20);
    drawLoop(11, 20);

    // glColor3f(0.0, 0.0, 0.0);
    // drawCircle(10, 20);
    glPopMatrix();
}


// draw the car
void drawCar (){
    glPushMatrix();
    glTranslatef(moveForward, 0, 0);

    // car body
    glPushMatrix();
    glTranslatef(0, -120, 0.4);

    // lower part
    glPushMatrix();
    glScalef(70, 20, 1);
    glColor3f(0, 0.6, 0.3);
    drawUnitSqaure();
    glPopMatrix();

    // upper part
    glTranslatef(0, 10, 0);
    glPushMatrix();
    glScalef(40, 20, 1);
    glColor3f(0, 0.6, 0.4);
    drawUnitSqaure();
    glPopMatrix();

    glPopMatrix();
    // front wheel
    glPushMatrix();
    glTranslatef(-20, 0, 0);
    drawWheel();
    glPopMatrix();

    // rear wheel
    glPushMatrix();
    glTranslatef(20, 0, 0);
    drawWheel();
    glPopMatrix();

    glPopMatrix();
}

void display(void){

    // color of the background
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    /*
    **************  HOUSE   **************
    */

    // center at 0, 140 X 90
    glPushMatrix();
    glTranslatef(0, 20, 0);

    // roof
    glPushMatrix();
    glTranslatef(0, 45+10, 0);  // roof shifted up by (house_width/2) + (roof_width/2)
    glScalef(150, 20, 1);
    glColor3f(0.6, 0.2, 0.1);
    drawUnitSqaure();
    glPopMatrix();

    // body
    glPushMatrix();
    glScalef(140, 90, 1);
    glColor3f(0.6, 0.6, 0.4);
    drawUnitSqaure();
    glPopMatrix();

    // left window    
    glPushMatrix();
    glTranslatef(-45, 10, 0.1);
    drawWindow();
    glPopMatrix();

    // right window
    glPushMatrix();
    glTranslatef(45, 10, 0.1);
    drawWindow();
    glPopMatrix();

    // door
    glPushMatrix();
    glTranslatef(0, -15, 0.1);
    drawDoor();
    glPopMatrix();

    glPopMatrix();
    
    /*
    
    **********  HOUSE END   *************
    
    */

    /*
    **************  BACKGROUND  **************
    */

    // sky
    glPushMatrix();
    glTranslatef(0, 500-45, -5);
    glScalef(1000, 1000, 100);
    glColor3f(skycolor[0], skycolor[1], skycolor[2]);
    drawUnitSqaure();
    glPopMatrix();

    // draw Sun & Moon
    glPushMatrix();
    drawSunAndMoon();
    glPopMatrix();

    //background green
    glPushMatrix();
    glTranslatef(0, -20, -2);
    glScalef(1000, 50, 100);
    glColor3f(0.5, 0.7, 0);
    drawUnitSqaure();
    glPopMatrix();

    // road
    glPushMatrix();
    glTranslatef(0, -500-45, 0);
    glScalef(1000, 1000, 100);
    glColor3f(0, 0, 0);
    drawUnitSqaure();
    glPopMatrix();

    // stripes
    glPushMatrix();
    glTranslatef(0, -110, 0.1);
    glScalef(1000, 10, 100);
    glColor3f(0.9, 0.9, 0.8);
    drawUnitSqaure();
    glPopMatrix();

    int num_stripes = 10;
    for(int i = 0; i < num_stripes; i++){
        glPushMatrix();
        glTranslatef(-200 + i * 40, -110, 0.2);
        glScalef(7, 30, 1);

        glColor3f(0, 0, 0);
        drawUnitSqaure();
        glPopMatrix();
    }

    // back footpath
    glPushMatrix();
    glTranslatef(0, -10-45, 0.1);
    glScalef(1000, 20, 100);
    glColor3f(0.6, 0.6, 0.6);
    drawUnitSqaure();
    glPopMatrix();

    // front footpath
    glPushMatrix();
    glTranslatef(0, -130-45, 0.1);
    glScalef(1000, 50, 100);
    glColor3f(0.6, 0.6, 0.6);
    drawUnitSqaure();
    glPopMatrix();

    // front green
    glPushMatrix();
    glTranslatef(0, -200, 0.2);
    glScalef(1000, 50, 100);
    glColor3f(0.5, 0.7, 0);
    drawUnitSqaure();
    glPopMatrix();

    /*
    **************  BACKGROUND END  **************
    */

   /*
   *************     CAR     ****************
   */

    drawCar();

    // glutSwapBuffers() ;
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei) w,(GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200, 200, -200, 200, -200, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


// timer function to animate day-night cycle
void timerDay (int value) {
    glutTimerFunc(10, timerDay, 0);
    dayCycleSpin += 0.2;
    if (dayCycleSpin > 360) dayCycleSpin -= 360;
    setSkyColor();
    sunSpin += 1.0;
    if (sunSpin > 360) sunSpin -= 360;

    glutPostRedisplay();
}


// timer function to animate car movement
void timerCar (int value) {
    glutTimerFunc(6, timerCar, 0);

    wheelSpin += 1.5;
    if (wheelSpin > 360) wheelSpin -= 360;

    moveForward += 2;
    if (moveForward > CARLIMIT[1]) moveForward = CARLIMIT[0];
    glutPostRedisplay();
}



int main(int argc, char** argv)
{
    setSkyColor();  // set sky color for first time

    glutInit(&argc, argv) ;
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(800, 800) ;
    glutInitWindowPosition(10,10) ;
    glutCreateWindow("Scene") ;
    init() ;
    glutDisplayFunc(display) ;
    glutReshapeFunc(reshape) ;
    glEnable(GL_DEPTH_TEST);

    glutTimerFunc(10, timerDay, 0);
    glutTimerFunc(6, timerCar, 0);
    
    glutMainLoop() ;
}