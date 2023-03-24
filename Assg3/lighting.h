#include <GL/glut.h>

// ambient
GLfloat ambient_position[] = {30.0, 0.0, 0.0};
GLfloat ambient_colors[] = {0.7, 0.7, 0.7, 1.0,
                            0.1, 0.1, 0.1, 1.0,
                            0.0, 0.0, 0.0, 1.0};

// enable ambient light with LIGHT0
void setAmbientLight () {
    glLightfv(GL_LIGHT0, GL_POSITION, ambient_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_colors);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ambient_colors + 4);
    glLightfv(GL_LIGHT0, GL_SPECULAR, ambient_colors + 8);
    glEnable(GL_LIGHT0);
}

// disable ambient light with LIGHT0
void unsetAmbientLight () {
    glDisable(GL_LIGHT0);
}

/*
 * SATELITES 
*/
void createSource (GLfloat position[]) {
    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    glutSolidSphere(2, 60, 60);
    glPopMatrix();
}

// red light
GLfloat red_light_color[] =   {0.0, 0.0, 0.0, 1.0,
                                1.0, 0.0, 0.0, 1.0,
                                0.0, 0.0, 0.0, 1.0};

GLfloat red_light_radius = 20.0;
GLfloat red_light_height = 10.0;
GLfloat red_theta = -120.0;

void setRedLight (GLfloat position[]) {
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, red_light_color);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light_color + 4);
    glLightfv(GL_LIGHT1, GL_SPECULAR, red_light_color + 8);

    createSource(position);
}

void unsetRedLight () {
    glDisable(GL_LIGHT1);
}

// blue light
GLfloat blue_light_color[] =   {0.0, 0.0, 0.0, 1.0,
                                0.0, 0.0, 1.0, 1.0,
                                0.0, 0.0, 0.0, 1.0};

GLfloat blue_light_radius = 20.0;
GLfloat blue_light_height = 12.5;
GLfloat blue_theta = 0.0;

void setBlueLight (GLfloat position[]) {
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_POSITION, position);
    glLightfv(GL_LIGHT2, GL_AMBIENT, blue_light_color);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, blue_light_color + 4);
    glLightfv(GL_LIGHT2, GL_SPECULAR, blue_light_color + 8);

    createSource(position);

}

void unsetBlueLight () {
    glDisable(GL_LIGHT2);
}


// green light
GLfloat green_light_color[] =   {0.0, 0.0, 0.0, 1.0,
                                0.0, 1.0, 0.0, 1.0,
                                0.0, 0.0, 0.0, 1.0};

GLfloat green_light_radius = 16.0;
GLfloat green_light_height = 7.5;
GLfloat green_theta = 120.0;

void setGreenLight (GLfloat position[]) {
    glEnable(GL_LIGHT3);
    glLightfv(GL_LIGHT3, GL_POSITION, position);
    glLightfv(GL_LIGHT3, GL_AMBIENT, green_light_color);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, green_light_color + 4);
    glLightfv(GL_LIGHT3, GL_SPECULAR, green_light_color + 8);

    createSource(position);

}

void unsetGreenLight () {
    glDisable(GL_LIGHT3);
}


// moving lights
GLfloat red_spin_amt = 0.5;
GLfloat blue_spin_amt = 0.5;
GLfloat green_spin_amt = 0.5;

void spinLights () {
    red_theta += red_spin_amt;
    blue_theta += blue_spin_amt;
    green_theta += green_spin_amt;
    if(red_theta > 360) red_theta -= 360;
    if(blue_theta > 360) blue_theta -= 360;
    if(green_theta > 360) green_theta -= 360;
    glutPostRedisplay();
}