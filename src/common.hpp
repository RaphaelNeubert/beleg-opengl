#ifndef COMMON_HPP
#define COMMON_HPP

#include "shader.hpp"
#include "camera.hpp"

#define WIN_W 1920
#define WIN_H 1080

extern GLuint program; 
enum VAO_IDs {VAOCube, VAOCone, VAOLightCube, NumVAOs};
enum VBO_IDs {VBOCube, VBOCone, VBOCubeInstance, VBOConeInstance, NumVBOs};
enum EBO_IDs {EBOCube, EBOCone, NumEBOs};
enum Attrib_IDs {vPosition, vColor, vTexture, vNormal,
                vInstance1, vInstance2, vInstance3, vInstance4};
enum Texture_IDs {texCube1, texCube2, NumTextures};
extern GLuint VAOs[NumVAOs];
extern GLuint VBOs[NumVBOs];
extern GLuint Textures[NumTextures];
extern GLuint EBOs[NumEBOs];

extern Camera camera;

extern GLfloat deltaTime;

//settings
enum lightType {POSITIONAL_CUBE, FLASHLIGHT, NumLightTypes};
enum wireframeMode {CUBE, ALLONLY, NONE, ALL, CONE, NumWireframeModes};
enum colorMode{WHITE, PURPLE, BLUE, RED, NumColorModes};

typedef struct sceneSettings {
    lightType light;
    bool faceCulling;
    bool depthTest;
    wireframeMode wMode;
    colorMode lightColor;
    GLfloat winW;
    GLfloat winH;
    bool mViewports;
}Settings;

extern Settings settings;

#endif

