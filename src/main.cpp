#include <iostream>
#include <glew.h>
#include <glut.h>
#include <freeglut.h>
#include <glm.hpp>

#include "shader.hpp"

#define W_WIDTH 1920
#define W_HEIGHT 1080

// program wide states
GLuint program; 
enum VAO_IDs {VAOBasic,NumVAOs};
enum VBO_IDs {VBOCube, VBOCone, NumVBOs};
enum EBO_IDs {EBOCube,NumEBOs};
enum Attrib_IDs {vPosition, vColor, vTexture, vElement};
enum Texture_IDs {texRectangle, NumTextures};
GLuint VAOs[NumVAOs];
GLuint VBOs[NumVBOs];
GLuint Textures[NumTextures];
GLuint EBOs[NumEBOs];

void generateCube()
{
    GLfloat vertices[]={
        0.0f, 0.0f, 0.0f,
        0.2f, 0.0f, 0.0f,
        0.1f, 0.2f, 0.0f,
        0.2f, 0.2f, 0.0f
    };
    GLuint indices[]={
        0,1,2,
        1,2,3
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
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT, 0);
}

void reshape(int w, int h)
{
}
void init()
{
    Shader shader("src/shader.vs","src/shader.fs");
    shader.activate();

    glClearColor(0.0f,0.3f,0.3f,1.0f);

    glGenVertexArrays(NumVAOs,VAOs);
    glGenBuffers(NumVBOs,VBOs);
    //glGenTextures(NumTextures,Textures);
    glGenBuffers(NumEBOs,EBOs);
    generateCube();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glVertexAttrib4f(vColor, 1.0f, 0.0f, 0.0f, 1.0f);
    drawCube();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(W_WIDTH,W_HEIGHT);
	glutInitContextVersion(4,5);  // (4,2) (3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	 //GLUT_COMPATIBILITY_PROFILE
	glutCreateWindow(argv[0]);
	glewExperimental=GL_TRUE;
	if (glewInit()) {
        std::cerr << "Failed to initialize glew. aborting" <<std::endl;
        exit(-1);
    }
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
}

