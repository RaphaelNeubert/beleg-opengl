#ifndef OBJECTS_HPP
#define OBJECTS_HPP

typedef struct models {
    glm::mat4 cubeModels[10000];
    glm::mat4 coneModels[400];
} SurfaceModels;

void generateCube();
void drawInstancedCubes(GLuint instances);
void drawInstancedOuterCubes(GLuint instances);

void generateCone();
void drawInstancedCones(GLuint instances);
void drawInstancedOuterCones(GLuint instances);

void setupLightCube();
void drawLightCube();

SurfaceModels& generateSurfaceModels(SurfaceModels& models, GLfloat currentFrame);
#endif

