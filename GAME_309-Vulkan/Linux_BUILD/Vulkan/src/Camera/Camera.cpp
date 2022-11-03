#include "../../include/Camera/Camera.h"

Camera::Camera()
{
    //projectionMatrix = glm::perspective(glm::radians());

    viewMatrix = glm::mat4(1.0f);
}

void Camera::UpdateViewMatrix()
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_positon) * 
                                glm::rotate(glm::mat4(1.0f), m_rotation,
                                glm::vec3(0, 0, 1));

    viewMatrix = glm::inverse(transform);    
}