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
Shader *sceneFLShader;
Shader *lightCubeShader;
Camera camera(glm::vec3(0.0f,3.0f,3.0f),glm::vec3(0.0f,0.0f,-1.0f));
Settings settings;

GLfloat lastX=WIN_W/2.0;
GLfloat lastY=WIN_H/2.0;
bool firstMouseCall=true; 

GLfloat deltaTime=0.0f;
GLfloat lastFrame=0.0f;

//wireframe Modes
bool wModeDef[5][4]={{1,1,1,0},{0,1,0,1},{1,0,1,0},{1,1,1,1},{1,0,1,1}};
glm::vec3 Colors[4]={glm::vec3(1.0f,1.0f,1.0f),glm::vec3(1.0f,0.0f,1.0f),
                     glm::vec3(0.0f,0.0f,1.0f),glm::vec3(1.0f,0.0f,0.0f)};

void init()
{
    sceneShader = new Shader("src/instanced_shader.vs","src/positional_light.fs");
    sceneFLShader = new Shader("src/instanced_shader.vs","src/flashlight.fs");
    lightCubeShader = new Shader("src/model_shader.vs","src/light_cube.fs");

    //set default Settings
    settings.light=POSITIONAL_CUBE;
    settings.faceCulling=true;
    settings.depthTest=true;
    settings.wMode=CUBE;
    settings.lightColor=WHITE;
    settings.winW=WIN_W;
    settings.winH=WIN_H;
    settings.mViewports=false;

    glClearColor(0.0f,0.3f,0.3f,1.0f);

    glGenVertexArrays(NumVAOs,VAOs);
    glGenBuffers(NumVBOs,VBOs);
    glGenTextures(NumTextures,Textures);
    glGenBuffers(NumEBOs,EBOs);

    loadCubeTexture();
    loadConeTexture();

    if (settings.faceCulling) glEnable(GL_CULL_FACE);
    if (settings.depthTest) glEnable(GL_DEPTH_TEST);

    generateCube();
    generateCone();
    setupLightCube();
}
void display()
{
    GLfloat currentFrame=glutGet(GLUT_ELAPSED_TIME);
    deltaTime=currentFrame-lastFrame;
    lastFrame=currentFrame;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //calculate Object positions
    SurfaceModels models;
    generateSurfaceModels(models, currentFrame);

    glm::vec3 lightColor=Colors[settings.lightColor];
    glm::vec3 pos=camera.getPos();
    glm::mat4 vPos=camera.getViewMatrix();

    //4 projections
    for (int i=0; i<=4; i++) {
        glm::mat4 projection(1.0f);
        glm::mat4 view=vPos;;

        switch (i) {
            case 0:
                if (settings.mViewports) continue;
                glViewport(0.0f,0.0f,settings.winW,settings.winH);
                projection=glm::perspective(glm::radians(45.0f),
                            settings.winW/settings.winH,0.1f,200.0f);
                break;
            case 1:
                glViewport(0.0f,0.0f,settings.winW/2,settings.winH/2);
                projection=glm::perspective(glm::radians(45.0f),
                                    settings.winW/settings.winH,0.1f,200.0f);
                break;
            case 2:
                glViewport(settings.winW/2,0.0f,settings.winW/2,settings.winH/2);
                projection=glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.1f,200.0f);
                view=glm::lookAt(pos*glm::vec3(1.0f,0.0f,1.0f),
                        pos*glm::vec3(1.0f,0.0f,1.0f)+glm::vec3(0.0f,0.0f,-1.0f)
                                                    ,glm::vec3(0.0f,1.0f,0.0f));
                break;
            case 3:
                glViewport(0.0f,settings.winH/2,settings.winW/2,settings.winH/2);
                projection=glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.1f,200.0f);
                pos.y=5.0f;
                view=glm::lookAt(pos,pos+glm::vec3(0.0f,-1.0f,0.001f),
                                            glm::vec3(0.0f,1.0f,0.0f));
                break;
            case 4:
                glViewport(settings.winW/2,settings.winH/2,
                            settings.winW/2,settings.winH/2);
                projection=glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.1f,200.0f);
                break;
        }

        if (settings.light == POSITIONAL_CUBE) {
            glm::vec3 lightPos=glm::vec3(0.0f,10.0f,-10.0f);
            glm::vec3 viewPos=camera.getPos();
            //draw light Cube
            lightCubeShader->activate();
            glm::mat4 model=glm::translate(glm::mat4(1.0f),lightPos);
            lightCubeShader->uniformMat4("model",model);
            lightCubeShader->uniformMat4("view",view);
            lightCubeShader->uniformMat4("projection",projection);
            lightCubeShader->uniformVec3("lightColor",lightColor);
            drawLightCube();

            //setup shader for scene
            sceneShader->activate();
            sceneShader->uniformMat4("view",view);
            sceneShader->uniformMat4("projection",projection);
            sceneShader->uniformVec3("lightColor",lightColor);
            sceneShader->uniformVec3("lightPos",lightPos);
            sceneShader->uniformVec3("viewPos",viewPos);
        }
        else {
            glm::vec3 lightPos=camera.getPos();
            glm::vec3 direction=camera.getFront();
            GLfloat angleOpen=glm::cos(glm::radians(12.5f));
            GLfloat outerAngleOpen=glm::cos(glm::radians(17.5f));

            //setup shader for flashlight scene 
            sceneFLShader->activate();
            sceneFLShader->uniformMat4("view",view);
            sceneFLShader->uniformMat4("projection",projection);
            sceneFLShader->uniformVec3("lightColor",lightColor);
            sceneFLShader->uniformVec3("lightPos",lightPos);
            sceneFLShader->uniformVec3("direction",direction);
            sceneFLShader->uniformFloat("angleOpen",angleOpen);
            sceneFLShader->uniformFloat("outerAngleOpen",outerAngleOpen);

        }


        glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBOCubeInstance]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(models.cubeModels),
                                            models.cubeModels, GL_STATIC_DRAW);
        if (wModeDef[settings.wMode][0]) drawInstancedCubes(10000);
        if (wModeDef[settings.wMode][1]) drawInstancedOuterCubes(10000);

        glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBOConeInstance]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(models.coneModels),
                                            models.coneModels, GL_STATIC_DRAW);
        if (wModeDef[settings.wMode][2]) drawInstancedCones(400);
        if (wModeDef[settings.wMode][3]) drawInstancedOuterCones(400);

        //only one viewport
        if (!settings.mViewports) break;
    }


    glutSwapBuffers();
}

void timer(int value)
{
    display();
	glutTimerFunc(1000/60.0f, timer, 0);
}
void cleanup()
{
    delete sceneShader;
    delete lightCubeShader;
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

