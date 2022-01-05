#include <iostream>
#include <glew.h>
#include <glut.h>
#include <freeglut.h>
#include <glm.hpp>
#include <gtx/transform.hpp>

#include "common.hpp"
#include "shader.hpp"
#include "objects.hpp"
#include "callback.hpp"
#include "textures.hpp"

// program wide states
GLuint program; 
GLuint VAOs[NumVAOs];
GLuint VBOs[NumVBOs];
GLuint Textures[NumTextures];
GLuint EBOs[NumEBOs];

Shader *shader;
Camera camera(glm::vec3(0.0f,0.0f,3.0f),glm::vec3(0.0f,0.0f,-1.0f));
GLfloat lastX=WIN_W/2.0;
GLfloat lastY=WIN_H/2.0;
bool firstMouseCall=true; 

GLfloat deltaTime=0.0f;
GLfloat lastFrame=0.0f;

void init()
{
    shader = new Shader("src/shader.vs","src/shader.fs");
    shader->activate();

    glClearColor(0.0f,0.3f,0.3f,1.0f);

    glGenVertexArrays(NumVAOs,VAOs);
    glGenBuffers(NumVBOs,VBOs);
    glGenTextures(NumTextures,Textures);
    glGenBuffers(NumEBOs,EBOs);

    loadCube1Texture();
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    generateCube();
    generateCone();
}
void display()
{
    GLfloat currentFrame=glutGet(GLUT_ELAPSED_TIME);
    deltaTime=currentFrame-lastFrame;
    lastFrame=currentFrame;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glVertexAttrib4f(vColor, 1.0f, 1.0f, 1.0f, 0.0f);

    glm::mat4 projection=glm::mat4(1.0);
    projection=glm::perspective(glm::radians(45.0f),1.0f,0.1f,100.0f);

    glm::mat4 view=camera.getViewMatrix();


    shader->uniformMat4("view",view);
    shader->uniformMat4("projection",projection);

    SurfaceModels models;
    generateSurfaceModels(models, currentFrame);
    
    for (size_t i=0; i<sizeof(models.cubeModels)/sizeof(glm::mat4); i++) {
        shader->uniformMat4("model",models.cubeModels[i]);
        drawCube();
        //drawOuterCube();
    }
    for (size_t i=0; i<sizeof(models.coneModels)/sizeof(glm::mat4); i++) {
        shader->uniformMat4("model",models.coneModels[i]);
        //drawCone();
        drawOuterCone();
    }

    glutSwapBuffers();
}

void timer(int value)
{
    display();
	glutTimerFunc(1000/144.0f, timer, 0);
}
void cleanup()
{
    delete shader;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WIN_W,WIN_H);
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
    glutKeyboardFunc(keyboard);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutPassiveMotionFunc(passivemouse);
    timer(0);
	glutMainLoop();
}

