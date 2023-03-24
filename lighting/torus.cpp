#include <bits/stdc++.h>
#include <math.h>
#include <GL/glut.h>
using namespace std;

GLfloat theta = 0.0;
GLfloat light_circling_radius = 60.0;

GLfloat light_position[] = {light_circling_radius, 0.0, 0.0, 0.0};
GLfloat light_ambient_and_diffuse[] = {0.6, 0.0, 0.0, 1.0};
GLfloat light_specular[] = {1.0, 0.0, 0.0, 1.0};
GLfloat light_shininess[] = {100.0};
GLfloat light_spot_cutoff = 40.0;
GLfloat light_spot_direction[] = {0.0, -1.0, 0.0};

GLfloat mat_ambient_and_diffuse[] = {0.6, 0.0, 0.0, 1.0};
GLfloat mat_specular[] = {1.0, 0.0, 0.0, 1.0};
GLfloat mat_shininess[] = {100.0};


void setLightDirection (){
    GLfloat light_direction_vector[] = {0.0, 0.0, 0.0};
    GLfloat norm = 0;
    for (int i = 0; i < 3; i++)
    {
      light_direction_vector[i] = -light_position[i];
      norm += (light_direction_vector[i] * light_direction_vector[i]);
    }

    for (int i = 0; i < 3; i++) light_spot_direction[i] = light_direction_vector[i] / norm;

    // for(int i = 0; i < 3; i++)
    //   cout << light_spot_direction[0] << ",";
    // cout << endl;
}

void createLight(){
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    // glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_and_diffuse);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, light_ambient_and_diffuse);
    // glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    // glLightfv(GL_LIGHT0, GL_SHININESS, light_shininess);
    // glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, light_spot_cutoff);
    // setLightDirection();
    // glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_spot_direction);
}

void init(void) 
{
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    

    // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_ambient_and_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    createLight();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(light_position[0], light_position[1], light_position[2]);
    glutWireCube(7);
    glPopMatrix();

    glPushMatrix();
    // glColor3f(0.6, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glutSolidTorus(20, 25, 40, 100);

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
    glOrtho(-70, 70, -70, 70, -70, 70);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);

    
}


void spin () {
    theta += 1;
    if (theta > 360) theta -= 360;

    light_position[0] = cos(theta*M_PI/180) * light_circling_radius;
    light_position[2] = sin(theta*M_PI/180) * light_circling_radius;

    createLight();
    glutPostRedisplay();
}


void mouse(int button, int state, int x, int y)
{
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN)
        glutIdleFunc(spin) ;
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
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (700, 700); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Simple Lighting in OpenGL");
    init ();
    
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}