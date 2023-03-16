#include <GL/glut.h>
#include <math.h>

// draw an unit square at (0, 0, 0)
void drawUnitSqaure (){
    glRectf(-0.5, -0.5, 0.5, 0.5);
}

// draw an unit square loop at (0, 0, 0)
void drawUnitSqaureLoop (){
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5, -0.5, 0);
    glVertex3f(-0.5, 0.5, 0);
    glVertex3f(0.5, 0.5, 0);
    glVertex3f(0.5, -0.5, 0);
    glEnd();
} 

// draw a circle using polygon at (0, 0, 0)
void drawCircle(float r, int slices) {
    glBegin(GL_POLYGON);
    float perEdgeAngle = 2.0*M_PI/float(slices);
    for (int i = 0; i < slices; i++)   {
        float theta = float(i) * perEdgeAngle; 
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex3f(x, y, 0); 
    }
    glEnd();
}

// draw a loop using lineloop at (0, 0, 0)
void drawLoop(float r, int slices) {
    glBegin(GL_LINE_LOOP);
    float perEdgeAngle = 2.0*M_PI/float(slices);
    for (int i = 0; i < slices; i++)   {
        float theta = float(i) * perEdgeAngle; 
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex3f(x, y, 0); 
    }
    glEnd();
}