#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <glm.hpp>
#include <glew.h>

enum Direction{FORWARDS,BACKWARDS,LEFT,RIGHT,UP,DOWN};

class Camera
{
    private:
        glm::vec3 pos;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;

        float yaw;
        float pitch;
        //options
        float speed;
        float sens;

    public:
        Camera(glm::vec3 pos, glm::vec3 front);
        glm::mat4 getViewMatrix();
        //TODO not needet anymore?
        glm::mat4 getPositionViewMatrix(glm::vec3 manualFront);
        void mouseMovement(int xoffset, int yoffset);
        void keyInput(Direction dir, float deltaTime);

        glm::vec3 getPos();
        glm::vec3 getFront();
};

#endif
