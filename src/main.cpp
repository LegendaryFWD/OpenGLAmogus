#include "headers/VAO.h"
#include "headers/VBO.h"
#include "headers/EBO.h"
#include "headers/shader.h"
#include "headers/texture.h"
#include "headers/camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>
#include <iostream>
#include <math.h>


const unsigned int width = 800, height = 800;

void framebufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}


GLfloat vertex[] = 
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 1.0f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

GLuint index[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    
    GLFWwindow* window = glfwCreateWindow(width, height, "matrix", NULL, NULL);
    if(window == NULL){
        // std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    gladLoadGL();
    
    glViewport(0,0,width,height);
    
    Shader WrappedShader("C:/Users/deusd/Documents/cpp/nada/src/resources/default.vert", "C:/Users/deusd/Documents/cpp/nada/src/resources/default.frag");

    VAO VAOst;
    VAOst.Bind();

    VBO VBOst(vertex, sizeof(vertex));
    EBO EBOst(index, sizeof(index));

    VAOst.LinkAtribb(VBOst, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAOst.LinkAtribb(VBOst, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAOst.LinkAtribb(VBOst, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VBOst.Unbind();
    VAOst.Unbind();
    EBOst.Unbind();


    
    Texture tex("C:/Users/deusd/Documents/cpp/nada/src/resources/amogus.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    tex.TexInit(WrappedShader, "tex0", 0);

    Camera cam(width, height, glm::vec3(0.0f, 0.5f, 3.0f));
    
    glEnable(GL_DEPTH_TEST);
    
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        WrappedShader.Activate();
        
        cam.Inputs(window);
        
        cam.Update(45.0f, 0.1f, 100.0f);

        cam.Matrix(WrappedShader, "camMatrix");
        
        tex.Bind();
        VAOst.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(index)/sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapInterval(1);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    VAOst.Delete();
    VBOst.Delete();
    EBOst.Delete();
    tex.Delete();
    WrappedShader.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}