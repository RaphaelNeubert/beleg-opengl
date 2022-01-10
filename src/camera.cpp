#include <glew.h>
#include <gtx/transform.hpp>
#include <glm.hpp>
#include <freeglut.h>
#include "common.hpp"
#include "camera.hpp"

//sets defaults
Camera::Camera(glm::vec3 pos, glm::vec3 front): pos(pos), front(front),
                                                up(glm::vec3(0.0f,1.0f,0.0f)),
                                                right(glm::cross(front,up)),
                                                yaw(-90.0f), pitch(0.0f),
                                                speed(0.05f), sens(0.1f) { }

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(pos,pos+front,up);
}
glm::mat4 Camera::getPositionViewMatrix(glm::vec3 manualFront)
{
    return glm::lookAt(pos,pos+manualFront,up);
}

void Camera::mouseMovement(int xoffset, int yoffset)
{
    yaw+=xoffset*sens;
    pitch+=yoffset*sens;  
    //realistic pitch constrains
    if(pitch > 89.0f)  pitch =  89.0f;
    else if(pitch < -89.0f) pitch = -89.0f;

    glm::vec3 direction;
    direction.x=cos(glm::radians(yaw))*cos(glm::radians(pitch));
    direction.y=sin(glm::radians(pitch));
    direction.z=sin(glm::radians(yaw))*cos(glm::radians(pitch));
    front=glm::normalize(direction);

    right=glm::normalize(glm::cross(front,up));
}

void Camera::keyInput(Direction dir, float deltaTime)
{
    float velocity=speed*deltaTime;
    switch(dir) {
        case FORWARDS:
            pos+=front*velocity;
            break;
        case BACKWARDS:
            pos-=front*velocity;
            break;
        case LEFT:
            pos-=right*velocity;
            break;
        case RIGHT:
            pos+=right*velocity;
            break;
        case UP:
            pos+=up*velocity;
            break;
        case DOWN:
            pos-=up*velocity;
            break;
    }
}
glm::vec3 Camera::getPos()
{
    return pos;
}
glm::vec3 Camera::getFront()
{
    return front;
}
