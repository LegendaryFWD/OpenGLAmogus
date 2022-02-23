#ifndef SHADER_H
#define SHADER_H


#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* file);

class Shader
{
    public:
        GLuint ID;
        Shader(const char* Vertex, const char* Frag);
        void Activate();
        void Delete();
    private:
        void CompileErrors(unsigned int shader, const char* type);

};
#endif