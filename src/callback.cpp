#include "callback.hpp"
#include "camera.hpp"
#include "common.hpp"
#include <glut.h>

GLfloat lastX=WIN_W/2.0;
GLfloat lastY=WIN_H/2.0;
bool firstMouseCall=true; 

void reshape(int w, int h)
{
    settings.winW=(GLfloat)w;
    settings.winH=(GLfloat)h;
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
            }
            else {
                glEnable(GL_DEPTH_TEST);
                settings.depthTest=true;
            }
            break;
        case '2':
            if (settings.faceCulling) {
                glDisable(GL_CULL_FACE);
                settings.faceCulling=false;
            }
            else {
                glEnable(GL_CULL_FACE);
                settings.faceCulling=true;
            }
            break;
        case 'v':
            if (settings.mViewports) {
                settings.mViewports=false;
            }
            else {
                settings.mViewports=true;
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
    if ((float)mouseX < settings.winW/10 || 
            (float)mouseX > settings.winW-settings.winW/10) {
        lastX=settings.winW/2;
        glutWarpPointer(settings.winW/2,mouseY);
    }
    if (mouseY < settings.winH/10|| mouseY > settings.winH-settings.winH/10) {
        lastY=settings.winH/2;
        glutWarpPointer(mouseX,settings.winH/2);
    }
}
