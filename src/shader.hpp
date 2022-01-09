#ifndef SHADER_H
#define SHADER_H

#include <glew.h>
#include <glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:
        unsigned int id;

        Shader(const char* pathVertexShader, const char* pathFragmentShader);
        void activate();
        void uniformMat4(const std::string& name, const glm::mat4& value);
        void uniformVec3(const std::string& name, const glm::vec3& value);
        void uniformFloat(const std::string& name, const GLfloat value);
    private:
        void checkCompileErrors(unsigned int shader, const char* type);
        void checkLinkErrors(unsigned int program);

};
#endif
