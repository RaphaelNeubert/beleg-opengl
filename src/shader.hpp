#ifndef SHADER_H
#define SHADER_H

#include <glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:
        unsigned int id;

        Shader(const char* pathVertexShader, const char* pathFragmentShader);
        void activateShader();
    private:
        void checkCompileErrors(unsigned int shader);
        void checkLinkErrors(unsigned int program);

};
#endif
