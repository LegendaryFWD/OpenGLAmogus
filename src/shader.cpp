#include "headers/shader.h"
#include <string.h>

std::string get_file_contents(const char* file){
    std::ifstream in(file, std::ios::binary);
    if(in)
    {
        std::string content;
        in.seekg(0, std::ios::end);
        content.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&content[0], content.size());
        in.close();
        return (content);
    }
    std::cout << "fuck" << std::endl;
    throw(errno);
}

Shader::Shader(const char* Vertex, const char* Frag){
    std::string vCode = get_file_contents(Vertex);
    std::string fCode = get_file_contents(Frag);
    
    const char* vertexS = vCode.c_str();
    const char* fragS = fCode.c_str();
    
    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &vertexS, NULL);
    glCompileShader(vshader);
    CompileErrors(vshader, "VERTEX");

    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &fragS, NULL);
    glCompileShader(fshader);
    CompileErrors(fshader, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vshader);
    glAttachShader(ID, fshader);

    glLinkProgram(ID);
    CompileErrors(ID, "PROGRAM");
    
    glDeleteShader(vshader);
    glDeleteShader(fshader);
}

void Shader::Activate(){
    glUseProgram(ID);
}

void Shader::Delete(){
    glDeleteProgram(ID);
}

void Shader::CompileErrors(unsigned int shader, const char* type){
    GLint CompileState;
    char infoLog[1024];
    if(strcmp(type ,"PROGRAM") == 0){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &CompileState);
        if(CompileState == GL_FALSE){
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
        }
    }
    else{
        glGetProgramiv(shader, GL_COMPILE_STATUS, &CompileState);
        if(CompileState == GL_FALSE){
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
        }
    }
}