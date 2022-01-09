#ifndef COMMON_HPP
#define COMMON_HPP

#include "shader.hpp"
#include "camera.hpp"

#define WIN_W 1080
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

extern Shader *sceneShader;
extern Shader *sceneFLShader;
extern Shader *sunShader;
extern Camera camera;

extern bool firstMouseCall;
extern GLfloat lastX;
extern GLfloat lastY;

extern GLfloat deltaTime;
extern GLfloat lastFrame;

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

}Settings;

extern Settings settings;

#endif

