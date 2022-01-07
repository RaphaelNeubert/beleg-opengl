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

Shader *sceneShader;
Shader *sunShader;
Camera camera(glm::vec3(0.0f,3.0f,3.0f),glm::vec3(0.0f,0.0f,-1.0f));

GLfloat lastX=WIN_W/2.0;
GLfloat lastY=WIN_H/2.0;
bool firstMouseCall=true; 

GLfloat deltaTime=0.0f;
GLfloat lastFrame=0.0f;

glm::vec3 lightPos(0.0f,-10.0f,-10.0f);

void init()
{
    sceneShader = new Shader("src/instanced_shader.vs","src/shader.fs");
    sunShader = new Shader("src/model_shader.vs","src/sun.fs");

    glClearColor(0.0f,0.3f,0.3f,1.0f);

    glGenVertexArrays(NumVAOs,VAOs);
    glGenBuffers(NumVBOs,VBOs);
    glGenTextures(NumTextures,Textures);
    glGenBuffers(NumEBOs,EBOs);

    loadCube1Texture();
    loadCube2Texture();

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    generateCube();
    generateCone();
    setupSun();
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
    glm::vec3 lightColor(1.0f,1.0f,1.0f);

    //draw world
    sceneShader->activate();
    sceneShader->uniformMat4("view",view);
    sceneShader->uniformMat4("projection",projection);
    sceneShader->uniformVec3("lightColor",lightColor);
    sceneShader->uniformVec3("lightPos",lightPos);

    SurfaceModels models;
    generateSurfaceModels(models, currentFrame);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBOCubeInstance]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(models.cubeModels), models.cubeModels, GL_STATIC_DRAW);
    //drawInstancedCubes(10000);
    //drawInstancedOuterCubes(10000);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBOConeInstance]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(models.coneModels), models.coneModels, GL_STATIC_DRAW);
    drawInstancedCones(400);
    //drawInstancedOuterCones(400);

    //draw sun
    sunShader->activate();
    glm::mat4 model=glm::translate(glm::mat4(1.0f),lightPos);
    sunShader->uniformMat4("model",model);
    sunShader->uniformMat4("view",view);
    sunShader->uniformMat4("projection",projection);
    drawSun();


    glutSwapBuffers();
}

void timer(int value)
{
    display();
	glutTimerFunc(1000/144.0f, timer, 0);
}
void cleanup()
{
    delete sceneShader;
    delete sunShader;
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

