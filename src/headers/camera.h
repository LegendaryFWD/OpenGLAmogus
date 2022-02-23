#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shader.h"

class Camera{
    public:
            glm::vec3 Pos;
            glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
            glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::mat4 cameraMatrix = glm::mat4(1.0f);

            bool fClick;
            
            int width;
            int height;

            float speed = 0.025f;
            float sense = 20.0f;

            Camera(int width, int height, glm::vec3 pos);

            
            void Update(float FOVdeg, float nearPlane, float farPlane);
            void Matrix(Shader& shader, const char* uniform);
            void Inputs(GLFWwindow* window);

};

#endif