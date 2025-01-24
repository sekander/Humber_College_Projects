#version 450
#extension GL_ARB_separate_shader_objects : enable

//Attributes
layout(location = 0) in vec4 vVertex;


uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) out vec3 texCoords;

void main() {
    
    texCoords = vec3(vVertex);
    
    texCoords = texCoords * vec3(-1.0, 1.0, 1.0);

 

    gl_Position = projectionMatrix * viewMatrix  * vVertex;
}