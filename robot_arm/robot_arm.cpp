#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <stdio.h>


GLfloat spinWhole = 0;
GLfloat spinForeArm = 0;


void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel(GL_FLAT);
}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT);

    
    
    glPushMatrix(); // for the whole block

      glRotatef(spinWhole, 0, 0, 1);  // rotation for whole arm
      glTranslatef(25.0, 0.0, 0.0);   // translate for whole arm
      

      glPushMatrix();   // for the upper arm block
        glScalef(10.0, 2.0, 1.0);   // scale the upper arm to make a cuboid
        
        // draw the cube
        glColor3f(1.0, 0.0, 0.0);
        glutWireCube(5);

      glPopMatrix();  // upper arm block end

      
      glPushMatrix();   // for the lower arm block 

        glTranslatef(50, 0, 0);

        glTranslatef(-25, 0, 0);    // rotate making the edge mid pt (25, 0, 0) origin
        glRotatef(spinForeArm, 0, 0, 1);  // spin
        glTranslated(25, 0, 0);   // x direction still 25 shifted from origin
                                  // shift back to converge the edge


        // glTranslatef(x, y, 0);
        glScalef(10.0, 2.0, 1.0);       // scale to make a cuboid
    
        // draw the cube
        glColor3f(0.0, 0.5, 0.7);
        glutWireCube(5);


       
        
      glPopMatrix();    // lower arm block end

    glPopMatrix();    //whole block end

    glutSwapBuffers() ;
}

void reshape(int w, int h)
{
    glViewport(0,0,(GLsizei) w,(GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75, 1, 0, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(100.0, 100.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

void spin(int direction)
{
  spinWhole = spinWhole + direction*5.0 ;
  if (spinWhole > 360.0)
    spinWhole = spinWhole - 360.0 ;
  glutPostRedisplay() ;
}

void spinPartial(int direction)
{
    spinForeArm = spinForeArm + direction*5.0 ;
    if (spinForeArm > 360.0)
        spinForeArm = spinForeArm - 360.0 ;
    glutPostRedisplay() ;
    }



void keyboard(unsigned char Key, int x, int y){
  
  switch(Key){
    case 'S': spin(1);
    break;
    case 's': spin(-1);
    break;
    case 'E': spinPartial(1);
    break;
    case 'e': spinPartial(-1);
    break;
  }
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv) ;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB) ;
    glutInitWindowSize(700,700) ;
    glutInitWindowPosition(100,100) ;
    glutCreateWindow("Bouncing ball") ;
    init() ;
    glutDisplayFunc(display) ;
    glutReshapeFunc(reshape) ;
    glutKeyboardFunc(keyboard);
    glutMainLoop() ;
}