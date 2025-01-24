#version 450
#extension GL_ARB_separate_shader_objects : enable

//Attributes
layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec4 vNormal;

out vec3 vertNormal;
out vec3 vertDir;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;


void main() {

    vertNormal = vec3(normalMatrix * vNormal);
    vec3 vertPos = vec3(modelMatrix * vVertex);
    vertDir = normalize(vertPos);
    
   

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vVertex;
}