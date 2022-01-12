#include <glew.h>
#include <gtx/transform.hpp>
#include "common.hpp"
#include "objects.hpp"

static glm::vec3 calculateNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
    //glm::vec3 x(c[0]-a[0],c[1]-a[1],c[2]-a[2]);
    //glm::vec3 y(b[0]-a[0],b[1]-a[1],b[2]-a[2]);
    return glm::normalize(glm::cross(b-a,c-a));
}
void generateCube()
{
    GLfloat vertices[]={
        //front
        -0.5f,-0.5f,0.5f,  0.5f, -0.5f, 0.5f,
        -0.5f,0.5f,0.5f,   0.5f, 0.5f, 0.5f,
        //back
        0.5f,-0.5f,-0.5f,   -0.5f, -0.5f, -0.5f,
        0.5f,0.5f,-0.5f,   -0.5f, 0.5f, -0.5f,
        //left
        -0.5f,-0.5f,-0.5f,   -0.5f, -0.5f, 0.5f,
        -0.5f,0.5f,-0.5f,   -0.5f, 0.5f, 0.5f,
        //right
        0.5f,-0.5f,0.5f,   0.5f, -0.5f, -0.5f,
        0.5f,0.5f,0.5f,   0.5f, 0.5f, -0.5f,
        //up
        -0.5f,0.5f,0.5f,   0.5f, 0.5f, 0.5f,
        -0.5f,0.5f,-0.5f,   0.5f, 0.5f, -0.5f,
        //down
        -0.5f,-0.5f,0.5f,   -0.5f, -0.5f, -0.5f,
        0.5f,-0.5f,0.5f,   0.5f, -0.5f, -0.5f
    };
    GLuint indices[]={
        //front
        0,1,2,  1,3,2,
        //back
        4,5,6,  5,7,6,
        //left
        8,9,10,  9,11,10,
        //right
        12,13,14,  13,15,14,
        //up
        16,17,18,  17,19,18,
        //down
        20,21,22,  21,23,22
    };
    GLfloat texcoords[]={
        0.0f,0.0f, 1.0f,0.0f, 0.0f,1.0f, 1.0f,1.0f,
        0.0f,0.0f, 1.0f,0.0f, 0.0f,1.0f, 1.0f,1.0f,
        0.0f,0.0f, 1.0f,0.0f, 0.0f,1.0f, 1.0f,1.0f,
        0.0f,0.0f, 1.0f,0.0f, 0.0f,1.0f, 1.0f,1.0f,
        0.0f,0.0f, 1.0f,0.0f, 0.0f,1.0f, 1.0f,1.0f,
        0.0f,0.0f, 1.0f,0.0f, 0.0f,1.0f, 1.0f,1.0f
    };
    GLfloat normals[sizeof(vertices)/sizeof(GLfloat)];
    for (GLuint i=0; i<sizeof(vertices)/sizeof(GLfloat); i+=12) {
        glm::vec3 num=calculateNormal(
                glm::vec3(vertices[i],vertices[i+1], vertices[i+2]),
                glm::vec3(vertices[i+3],vertices[i+4],vertices[i+5]),
                glm::vec3(vertices[i+6],vertices[i+7],vertices[i+8]));
        normals[i]=num.x; normals[i+1]=num.y; normals[i+2]=num.z;

        num=calculateNormal(
                glm::vec3(vertices[i+3],vertices[i+4],vertices[i+5]),
                glm::vec3(vertices[i+6],vertices[i+7],vertices[i+8]),
                glm::vec3(vertices[i],vertices[i+1], vertices[i+2]));
        normals[i+3]=num.x; normals[i+4]=num.y; normals[i+5]=num.z;

        num=calculateNormal(
                glm::vec3(vertices[i+6],vertices[i+7],vertices[i+8]),
                glm::vec3(vertices[i],vertices[i+1], vertices[i+2]),
                glm::vec3(vertices[i+3],vertices[i+4],vertices[i+5]));
        normals[i+6]=num.x; normals[i+7]=num.y; normals[i+8]=num.z;

        num=calculateNormal(
                glm::vec3(vertices[i+9],vertices[i+10], vertices[i+11]),
                glm::vec3(vertices[i+6],vertices[i+7],vertices[i+8]),
                glm::vec3(vertices[i+3],vertices[i+4],vertices[i+5]));
        normals[i+9]=num.x; normals[i+10]=num.y; normals[i+11]=num.z;
        //std::cout<<"x="<<num.x<<" y="<<num.y<<" z="<<num.z<<std::endl;
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBOCube]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glBindVertexArray(VAOs[VAOCube]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[VBOCube]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices)+sizeof(texcoords)+sizeof(normals),vertices,GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER,sizeof(vertices),sizeof(texcoords),texcoords);
    glBufferSubData(GL_ARRAY_BUFFER,sizeof(vertices)+sizeof(texcoords),sizeof(normals),normals);
    glVertexAttribPointer(vPosition,3,GL_FLOAT,GL_FALSE,0,(void*)0);
    glVertexAttribPointer(vTexture,2,GL_FLOAT,GL_FALSE,0,(void*)sizeof(vertices));
    glVertexAttribPointer(vNormal,3,GL_FLOAT,GL_FALSE,0,(void*)(sizeof(vertices)+sizeof(texcoords)));
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vTexture);
    glEnableVertexAttribArray(vNormal);
    
    //instanced rendering
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBOCubeInstance]);
    glEnableVertexAttribArray(vInstance1);
    glVertexAttribPointer(vInstance1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(vInstance2);
    glVertexAttribPointer(vInstance2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(vInstance3);
    glVertexAttribPointer(vInstance3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2*sizeof(glm::vec4)));
    glEnableVertexAttribArray(vInstance4);
    glVertexAttribPointer(vInstance4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3*sizeof(glm::vec4)));

    glVertexAttribDivisor(vInstance1, 1);
    glVertexAttribDivisor(vInstance2, 1);
    glVertexAttribDivisor(vInstance3, 1);
    glVertexAttribDivisor(vInstance4, 1);

}
void drawInstancedCubes(GLuint instances)
{
    glBindTexture(GL_TEXTURE_2D, Textures[texCube1]);
    glBindVertexArray(VAOs[VAOCube]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[VBOCube]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBOCube]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glVertexAttrib3f(vColor, 1.0f, 1.0f, 1.0f);
    glDrawElementsInstanced(GL_TRIANGLES,36,GL_UNSIGNED_INT, 0, instances);
    glBindVertexArray(0);
}
void drawInstancedOuterCubes(GLuint instances)
{
    glBindVertexArray(VAOs[VAOCube]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[VBOCube]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBOCube]);
    glVertexAttrib3f(vColor, 0.0f, 0.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (settings.wMode == ALLONLY) glLineWidth(2.0f);
    else glLineWidth(5.0f);
    glDrawElementsInstanced(GL_TRIANGLES,36,GL_UNSIGNED_INT, 0, instances);
}


void generateCone()
{
    GLuint n=100; //triangle count
    GLfloat r=0.5; //radius
    GLfloat jump=360.0/n;
    n+=2;
    GLfloat alpha=0.0;
    GLfloat vertices[n*3*2];  //*2 because of bottom circle
    GLuint indices[n*3*2];
    GLfloat normals[n*3*2];
    GLfloat texcoords[n*2];  

    //shelf center
    vertices[0]=0.0f; vertices[1]=0.5; vertices[2]=0.0f;
    indices[0]=0; indices[1]=1; indices[2]=2;
    texcoords[0]=0.5f; texcoords[1]=1.0f;

    //shelf
    for (GLuint i=1; i<n; i++) {
        //new point coordinate
        vertices[i*3]=r*cos(alpha*M_PI/180);
        vertices[i*3+1]=-0.5f;
        vertices[i*3+2]=-1*(r*sin(alpha*M_PI/180));
        //triangle indices
        indices[i*3]=0;
        indices[i*3+1]=i-1;
        indices[i*3+2]=i;
        texcoords[i*2]=(GLfloat)i/n;
        texcoords[i*2+1]=0.0f;
        alpha+=jump;
    }
    //bottom circle center
    vertices[n*3]=0.0f; vertices[n*3+1]=-0.5f; vertices[n*3+2]=0.0f;
    indices[n*3]=n; indices[n*3+1]=n+2; indices[n*3+2]=n+1;
    alpha=0.0f;
    //bottom circle 
    for (GLuint i=n+1; i<n*2; i++) {
        vertices[i*3]=r*cos(alpha*M_PI/180);
        vertices[i*3+1]=-0.5f;
        vertices[i*3+2]=-1*(r*sin(alpha*M_PI/180));
        //triangle indices
        indices[i*3]=n;
        indices[i*3+1]=i;
        indices[i*3+2]=i-1;
        alpha+=jump;
    }
    //calculate normals
    normals[0]=0.0f; normals[1]=1.0f; normals[2]=0.0f;
    normals[n*3]=0.0f; normals[n*3+1]=-1.0f; normals[n*3+2]=0.0f;
    for (GLuint i=1; i<n-1; i++) {
        glm::vec3 num=calculateNormal(
                glm::vec3(vertices[i*3],vertices[i*3+1], vertices[i*3+2]),
                glm::vec3(vertices[i*3+3],vertices[i*3+4],vertices[i*3+5]),
                glm::vec3(vertices[0],vertices[1],vertices[2]));
        normals[i*3]=num.x; normals[i*3+1]=num.y; normals[i*3+2]=num.z;
        normals[n*3+i*3]=0.0f; normals[n*3+i*3+1]=-1.0f; normals[n*3+i*3+2]=0.0f;
    }
    //calculate last normal using first data point
    glm::vec3 num=calculateNormal(
            glm::vec3(vertices[101*3],vertices[101*3+1], vertices[101*3+2]),
            glm::vec3(vertices[3],vertices[4],vertices[5]),
            glm::vec3(vertices[0],vertices[1],vertices[2]));
    normals[101*3]=num.x; normals[101*3+1]=num.y; normals[101*3+2]=num.z;
    normals[n*3+101*3]=0.0f; normals[n*3+101*3+1]=-1.0f; normals[n*3+101*3+2]=0.0f;
    /*
    for (int i=0; i<3*n*2; i+=3) {
        std::cout<<"i="<<i<<" val="<<normals[i]<<"   ";
        std::cout<<"i="<<i+1<<" val="<<normals[i+1]<<"   ";
        std::cout<<"i="<<i+2<<" val="<<normals[i+2]<<"   "<<std::endl;
    }
    */

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBOCone]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(VAOs[VAOCone]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[VBOCone]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices)+sizeof(texcoords)+sizeof(normals),vertices,GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER,sizeof(vertices),sizeof(texcoords),texcoords);
    glBufferSubData(GL_ARRAY_BUFFER,sizeof(vertices)+sizeof(texcoords),sizeof(normals),normals);
    glVertexAttribPointer(vPosition,3,GL_FLOAT,GL_FALSE,0,(void*)0);
    glVertexAttribPointer(vTexture,2,GL_FLOAT,GL_FALSE,0,(void*)sizeof(vertices));
    glVertexAttribPointer(vNormal,3,GL_FLOAT,GL_FALSE,0,(void*)(sizeof(vertices)+sizeof(texcoords)));
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vTexture);
    glEnableVertexAttribArray(vNormal);

    //instanced rendering
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBOConeInstance]);
    glEnableVertexAttribArray(vInstance1);
    glVertexAttribPointer(vInstance1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(vInstance2);
    glVertexAttribPointer(vInstance2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(vInstance3);
    glVertexAttribPointer(vInstance3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2*sizeof(glm::vec4)));
    glEnableVertexAttribArray(vInstance4);
    glVertexAttribPointer(vInstance4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3*sizeof(glm::vec4)));

    glVertexAttribDivisor(vInstance1, 1);
    glVertexAttribDivisor(vInstance2, 1);
    glVertexAttribDivisor(vInstance3, 1);
    glVertexAttribDivisor(vInstance4, 1);

    glBindVertexArray(0);
}
void drawInstancedCones(GLuint instances)
{
    glBindTexture(GL_TEXTURE_2D, Textures[texCube2]);
    glBindVertexArray(VAOs[VAOCone]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[VBOCone]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBOCone]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glVertexAttrib3f(vColor, 1.0f, 1.0f, 1.0f);
    glDrawElementsInstanced(GL_TRIANGLES,612,GL_UNSIGNED_INT,0,instances);
}
void drawInstancedOuterCones(GLuint instances)
{
    glBindVertexArray(VAOs[VAOCone]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[VBOCone]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBOCone]);
    glBindVertexArray(VAOs[VAOCone]);
    glVertexAttrib3f(vColor, 0.0f, 0.0f, 0.0f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.0f);
    glDrawElementsInstanced(GL_TRIANGLES,612,GL_UNSIGNED_INT,0,instances);
}
void setupLightCube()
{
    glBindVertexArray(VAOs[VAOLightCube]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBOCube]);
    glVertexAttribPointer(vPosition,3,GL_FLOAT,GL_FALSE,0,(void*)0);
    glEnableVertexAttribArray(vPosition);
}
void drawLightCube()
{
    glBindVertexArray(VAOs[VAOLightCube]);
    glBindBuffer(GL_ARRAY_BUFFER,VBOs[VBOCube]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[EBOCube]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
SurfaceModels& generateSurfaceModels(SurfaceModels& models,GLfloat currentFrame)
{

    GLuint n=sizeof(models.cubeModels)/sizeof(glm::mat4); //cubes

    GLint rows=sqrt(n);
    GLuint pc=0;

    for (GLint i=0; i<rows; i++) {
        for (GLint j=0; j<rows; j++) {
            //cube
            models.cubeModels[i*rows+j]=glm::translate(glm::mat4(1.0f),
                                glm::vec3(j-rows/2,sin(currentFrame/1000)*
                                                    sin(i+1)*cos(j+1),i-rows/2));
            //cone
            if (i%5 == 0) {
                if (j%5 == 0) {
                //place cone
                models.coneModels[pc]=glm::translate(glm::mat4(1.0f),
                                        glm::vec3(j-rows/2,sin(currentFrame/1000)*
                                                        sin(i+1)*cos(j+1)+1,i-rows/2));
                pc++;
                }
            }
        }
    }
    return models;
}
