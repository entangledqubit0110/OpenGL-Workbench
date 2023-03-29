#include <GL/glut.h>

/**
 * ------------------------------------------------------------------------
 *                              GLOBAL LIGHTING
 * ------------------------------------------------------------------------
 * This section defined a global ambeint and diffuse coloring of greyish 
 * components. This is created using GL_LIGHT0. The position is kept further
 * than satelites for better visual effects. 
*/
GLfloat ambient_position[] = {30.0, 0.0, 0.0};
GLfloat ambient_colors[] = {0.1, 0.1, 0.1, 0.5,
                            0.1, 0.1, 0.1, 0.5,
                            0.2, 0.2, 0.2, 0.5};

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
 * ----------------------------------------------------------------------------
 *                                   SATELITES
 * ----------------------------------------------------------------------------
 * The following section contains the utility functions for creating the orbiting 
 * light sources. The sources postion constants and color constants are defined here,
 * However the position change is implemented in the main module.
 * Here:
 * red satelite: GL_LIGHT1
 * blue satelite: GL_LIGHT2
 * green satelite: GL_LIGHT3
 * For every color, the set<Color>Light enabled the corresponding light with suitable
 * parameters and unset<Color>Light disables it.
*/


/**
 * Creates a spherical light source, which is not actually a source as per GL_LIGHTi
 * but a container of GL_LIGHTi i.e., create a source around the GL_LIGHTi already 
 * initialized
 * --------------
 * input
 * ---------------
 * position: x, y, z for the sphere
 * enableColor: enable of disable the sphere's color
 * r, g, b, alpha: shpere's color components when enableColor = true
*/
void createSource (GLfloat position[], bool enableColor, GLfloat r, GLfloat g, GLfloat b, GLfloat alpha) {
    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    
    if (enableColor){
        glPushAttrib(GL_LIGHTING_BIT);
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        glColor4f(r, g, b, alpha);
    }

    glutSolidSphere(0.7, 60, 60);

    if (enableColor)
        glPopAttrib();
    
    glPopMatrix();
}

// red light
GLfloat red_light_color[] =   {0.0, 0.0, 0.0, 1.0,
                                1.0, 0.0, 0.0, 1.0,
                                1.0, 0.0, 0.0, 1.0};

GLfloat red_light_radius = 16.0;
GLfloat red_light_height = 10.0;
GLfloat red_theta = -120.0;

void setRedLight (GLfloat position[]) {
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, red_light_color);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red_light_color + 4);
    glLightfv(GL_LIGHT1, GL_SPECULAR, red_light_color + 8);
}

void unsetRedLight () {
    glDisable(GL_LIGHT1);
}

// blue light
GLfloat blue_light_color[] =   {0.0, 0.0, 0.0, 1.0,
                                0.0, 0.0, 1.0, 1.0,
                                0.0, 0.0, 1.0, 1.0};

GLfloat blue_light_radius = 15.0;
GLfloat blue_light_height = 12.5;
GLfloat blue_theta = 0.0;

void setBlueLight (GLfloat position[]) {
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_POSITION, position);
    glLightfv(GL_LIGHT2, GL_AMBIENT, blue_light_color);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, blue_light_color + 4);
    glLightfv(GL_LIGHT2, GL_SPECULAR, blue_light_color + 8);
}

void unsetBlueLight () {
    glDisable(GL_LIGHT2);
}


// green light
GLfloat green_light_color[] =   {0.0, 0.0, 0.0, 1.0,
                                0.0, 1.0, 0.0, 1.0,
                                0.0, 1.0, 0.0, 1.0};

GLfloat green_light_radius = 17.0;
GLfloat green_light_height = 7.5;
GLfloat green_theta = 120.0;

void setGreenLight (GLfloat position[]) {
    glEnable(GL_LIGHT3);
    glLightfv(GL_LIGHT3, GL_POSITION, position);
    glLightfv(GL_LIGHT3, GL_AMBIENT, green_light_color);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, green_light_color + 4);
    glLightfv(GL_LIGHT3, GL_SPECULAR, green_light_color + 8);
}

void unsetGreenLight () {
    glDisable(GL_LIGHT3);
}


// moving lights variables
GLfloat rotation_amt[] = {0.5, 0.5, 0.5};
int rotation_direction[] = {1, -1, 1};

/*
 * Function to animate the circular motion of lights.
 * Increases rotation as defined by spin amounts and
 * spin directions.
*/ 
void spinLights () {
    red_theta += rotation_direction[0] * rotation_amt[0];
    blue_theta += rotation_direction[1] * rotation_amt[1];
    green_theta += rotation_direction[2] * rotation_amt[2];

    if(red_theta > 360) red_theta -= 360;
    if(blue_theta > 360) blue_theta -= 360;
    if(green_theta > 360) green_theta -= 360;
    glutPostRedisplay();
}

/**
 * --------------------------------------------------------------------------------
 *                              VIEWPOINT LIGHTING
 * --------------------------------------------------------------------------------
 * A light at eye poition using GL_LIGHT4
 * Torch-like powerful directional light
*/

GLfloat viewport_colors[] = {0.3, 0.3, 0.3, 1.0,
                            0.6, 0.6, 0.6, 0.5,
                            0.7, 0.7, 0.7, 0.5};

void setViewPointLight (GLfloat position[]) {
    glEnable(GL_LIGHT4);
    glLightfv(GL_LIGHT4, GL_POSITION, position);
    glLightfv(GL_LIGHT4, GL_AMBIENT, viewport_colors);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, viewport_colors + 4);
    glLightfv(GL_LIGHT4, GL_SPECULAR, viewport_colors + 8);
}

void unsetViewPointLight () {
    glDisable(GL_LIGHT4);
}