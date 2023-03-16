#include <GL/glut.h>

GLfloat CARLIMIT[2] = {-250, 250};  // car movement boundaries

// night sky transition colors
int SKYNIGHT[5][3] =  {
                        {190,169,222},
                        {135,136,156},
                        {84,107,171},
                        {46,68,130},
                        {19, 24, 98}
                    };
// day sky transition colors
int SKYDAY[5][3] =  {
                        {0,249,255},
                        {122,252,255},
                        {145,252,255},
                        {186,253,255},
                        {201,252,253}
                    };