#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "shader.h"

class Texture{
    public:
    GLuint ID;
    GLenum type;
    Texture(const char* image, GLenum TexType, GLenum slot, GLenum format, GLenum pixelType);
    void TexInit(Shader& shader, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
};

#endif