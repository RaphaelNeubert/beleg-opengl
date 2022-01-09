#include "shader.hpp"


Shader::Shader(const char* pathVertexShader, const char* pathFragmentShader)
{
// read File contents
    std::ifstream vFile;
    std::ifstream fFile;
    std::string vSource;
    std::string fSource;
    // ifstream.open() sets failbit on failure, this assures that in this case
    // exception is thrown
    vFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        vFile.open(pathVertexShader);
        fFile.open(pathFragmentShader);
        std::stringstream vStream, fStream;

        vStream << vFile.rdbuf();
        fStream << fFile.rdbuf();

        vFile.close();
        fFile.close();

        vSource=vStream.str();
        fSource=fStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vCode=vSource.c_str();
    const char* fCode=fSource.c_str();
    GLuint fragment;
    // compile vertex shader
    GLuint vertex=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "vertex");
    // compile fragment Shader
    fragment=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "fragment");
    // link shaders
    id=glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    checkLinkErrors(id);
    // delete the shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::activate()
{
    glUseProgram(id);
}

void Shader::checkCompileErrors(unsigned int shader, const char* type)
{
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char clog[1024];
        glGetShaderInfoLog(shader, 1024, NULL, clog);
        std::cerr << "ERROR::SHADER_COMPILATION_ERROR type:"<<type << "\n"
                  << clog << std::endl;
        }
}

void Shader::checkLinkErrors(unsigned int program)
{
    int success;
glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char clog[1024];
        glGetProgramInfoLog(program, 1024, NULL, clog);
        std::cerr << "ERROR::SHADER_LINKING_ERROR " << "\n" << clog
                  << std::endl;
    }
}
void Shader::uniformMat4(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(id,name.c_str()), 1,GL_FALSE, &value[0][0]);
}
void Shader::uniformVec3(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(id,name.c_str()), 1, &value[0]);
}
void Shader::uniformFloat(const std::string& name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(id,name.c_str()), value);
}
