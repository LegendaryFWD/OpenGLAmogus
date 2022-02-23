#include "headers/texture.h"

Texture::Texture(const char* image, GLenum TexType, GLenum slot, GLenum format, GLenum pixelTexType){
    
    type = TexType;
    
    int width, height, numColch;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &width, &height, &numColch, 0);
    
    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(TexType, ID);

    glTexParameteri(TexType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(TexType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameteri(TexType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(TexType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(TexType, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(TexType);
    
    stbi_image_free(bytes);
    glBindTexture(TexType, 0); 

}

void Texture::TexInit(Shader& shader, const char* uniform, GLuint unit){
    GLuint texID = glGetUniformLocation(shader.ID, "tex0");
    shader.Activate();
    glUniform1i(texID, 0); 
}

void Texture::Bind(){
    glBindTexture(type, ID);
}

void Texture::Unbind(){
    glBindTexture(type, 0);
    
}

void Texture::Delete(){
    glDeleteTextures(1, &ID);
}