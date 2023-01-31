#include <GL/glut.h>


/*
    draw a circle with center at (Cx, Cy)
    and radius r using Bresenham's Circle drawing algorithm
*/
void bresenhamCircle (int Cx, int Cy, int r){
    glPushMatrix();
    glTranslatef(Cx, Cy, 0.0);

        
    GLfloat x = 0, y = r;
    GLfloat p = 3- 2*r;
    while(x < y){
        glPushMatrix();
        glBegin(GL_POINTS);

        glVertex2f(x, y);
        glVertex2f(x, -y);
        glVertex2f(-x, y);
        glVertex2f(-x, -y);

        glVertex2f(y, x);
        glVertex2f(y, -x);
        glVertex2f(-y, x);
        glVertex2f(-y, -x);

        glEnd();
        glPopMatrix();

        if(p < 0){
            p += 4*x + 6;
        }
        else
        {
            p += 4*(x-y) + 10;
            y--;
        }
        x++;
    }

    glPopMatrix();
}