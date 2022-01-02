#include "callback.hpp"
#include "camera.hpp"
#include "common.hpp"
#include <glut.h>

void reshape(int w, int h)
{
}
void keyboard(unsigned char key, int mouseX, int mouseY)
{
    switch(key) {
        case 'w':
            camera.keyInput(FORWARDS, deltaTime);
            break;
        case 's':
            camera.keyInput(BACKWARDS, deltaTime);
            break;
        case 'a':
            camera.keyInput(LEFT, deltaTime);
            break;
        case 'd':
            camera.keyInput(RIGHT, deltaTime);
            break;
    }
}
void passivemouse(int mouseX, int mouseY)
{
    GLfloat xoffset=mouseX-lastX;
    //reversed since y-coordinates 0 at top
    GLfloat yoffset=lastY-mouseY; 

    lastX=mouseX;
    lastY=mouseY;

    //execute once
    if (firstMouseCall){
        xoffset=0.0f;
        yoffset=0.0f;
        firstMouseCall=false;
    }

    camera.mouseMovement(xoffset,yoffset);

    //resets mouse to middle at the boarder
    if (mouseX < 100 || mouseX > WIN_W-100) {
        lastX=WIN_W/2;
        glutWarpPointer(WIN_W/2,mouseY);
    }
    if (mouseY < 100 || mouseY > WIN_H-100) {
        lastY=WIN_H/2;
        glutWarpPointer(mouseX,WIN_H/2);
    }
}
