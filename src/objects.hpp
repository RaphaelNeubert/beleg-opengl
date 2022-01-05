#ifndef OBJECTS_HPP
#define OBJECTS_HPP

typedef struct models {
    glm::mat4 cubeModels[2500];
    glm::mat4 coneModels[100];
} SurfaceModels;

void generateCube();
void drawCube();
void drawOuterCube();

void generateCone();
void drawCone();
void drawOuterCone();

SurfaceModels& generateSurfaceModels(SurfaceModels& models, GLfloat currentFrame);
#endif

