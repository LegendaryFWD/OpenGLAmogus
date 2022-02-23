#include "headers/camera.h"

Camera::Camera(int width, int height, glm::vec3 pos){
    Camera::width = width;
    Camera::height = height;
    Camera::Pos = pos;
}

void Camera::Update(float FOVDeg, float nearPlane, float farPlane){
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    
    view = glm::lookAt(Pos, Pos + Orientation, Up);
    proj = glm::perspective(glm::radians(FOVDeg), (float)width / height, nearPlane, farPlane);

    cameraMatrix = proj * view;
}

void Camera::Matrix(Shader& shader, const char* uniform){
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}


void Camera::Inputs(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        Pos += speed * Orientation;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        Pos += speed * -glm::normalize(glm::cross(Orientation, Up));
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        Pos += speed * -Orientation;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        Pos += speed * glm::normalize(glm::cross(Orientation, Up));
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        speed = 0.075f;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE){
        speed = 0.025f;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        Pos += speed * Up;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
        Pos += speed * -Up;
    }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if(fClick){
            glfwSetCursorPos(window, (width / 2), (height / 2));
            fClick = false;
        }

        double mouseX;
        double mouseY;

        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sense * (float)(mouseY - (height / 2)) / height;
        float rotY = sense * (float)(mouseX - (width / 2)) / width;

        glm::vec3 newOrient = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));
        if(abs(glm::angle(newOrient, Up) - glm::radians(90.0f) <= glm::radians(85.0f))){
            Orientation = newOrient;
        }

        Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
        glfwSetCursorPos(window, (width / 2), (height / 2));

    }

    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        fClick = true;
        
    }
}