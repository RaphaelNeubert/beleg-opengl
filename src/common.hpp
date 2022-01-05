#ifndef COMMON_HPP
#define COMMON_HPP

#include "shader.hpp"
#include "camera.hpp"

#define WIN_W 1080
#define WIN_H 1080

extern GLuint program; 
enum VAO_IDs {VAOCube, VAOCone, NumVAOs};
enum VBO_IDs {VBOCube, VBOCone, NumVBOs};
enum EBO_IDs {EBOCube, EBOCone, NumEBOs};
enum Attrib_IDs {vPosition, vColor, vTexture};
enum Texture_IDs {texCube1, NumTextures};
extern GLuint VAOs[NumVAOs];
extern GLuint VBOs[NumVBOs];
extern GLuint Textures[NumTextures];
extern GLuint EBOs[NumEBOs];

extern Shader *shader;
extern Camera camera;

extern bool firstMouseCall;
extern GLfloat lastX;
extern GLfloat lastY;

extern GLfloat deltaTime;
extern GLfloat lastFrame;

#endif

