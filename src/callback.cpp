#include "callback.hpp"
#include "camera.hpp"
#include "common.hpp"
#include <glut.h>

void reshape(int w, int h)
{
}
void keyboard(unsigned char key, int mouseX, int mouseY)
{
    unsigned int state;
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
        case 'e':
            camera.keyInput(UP, deltaTime);
            break;
        case 'q':
            camera.keyInput(DOWN, deltaTime);
            break;

        case 'l':
            state=settings.light+1;
            if (state == NumLightTypes) settings.light=POSITIONAL_CUBE;
            else settings.light=static_cast<lightType>(state);
            break;
        case 'm':
            state=settings.wMode+1;
            if (state == NumWireframeModes) settings.wMode=CUBE;
            else settings.wMode=static_cast<wireframeMode>(state);
            break;
        case 'c':
            state=settings.lightColor+1;
            if (state == NumColorModes) settings.lightColor=WHITE;
            else settings.lightColor=static_cast<colorMode>(state);
            break;
        case '1':
            if (settings.depthTest) {
                glDisable(GL_DEPTH_TEST);
                settings.depthTest=false;
                puts("disabled depth test");
            }
            else {
                glEnable(GL_DEPTH_TEST);
                settings.depthTest=true;
                puts("enabled depth test");
            }
            break;
        case '2':
            if (settings.faceCulling){
                glDisable(GL_CULL_FACE);
                settings.faceCulling=false;
                puts("disabled face culling");
            }
            else{
                glEnable(GL_CULL_FACE);
                settings.faceCulling=true;
                puts("enabled face culling");
            }
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
    if (mouseX < 200 || mouseX > WIN_W-200) {
        lastX=WIN_W/2;
        glutWarpPointer(WIN_W/2,mouseY);
    }
    if (mouseY < 200 || mouseY > WIN_H-200) {
        lastY=WIN_H/2;
        glutWarpPointer(mouseX,WIN_H/2);
    }
}
