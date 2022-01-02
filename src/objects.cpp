#include <glew.h>
#include "common.hpp"
#include "objects.hpp"

void generateCube()
{
    GLfloat vertices[]={
        //front
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        //back
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f
    };
    GLuint indices[]={
        0,1,2,
        1,2,3,

        4,5,6,
        5,6,7
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBOCube]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glBindVertexArray(VAOs[VAOBasic]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[VBOCube]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(vPosition,3,GL_FLOAT,GL_FALSE,0,(void*)0);
    glEnableVertexAttribArray(vPosition);
}
void drawCube()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBOCube]);
    glBindVertexArray(VAOs[VAOBasic]);
    glDrawElements(GL_TRIANGLES,12,GL_UNSIGNED_INT, 0);
}
