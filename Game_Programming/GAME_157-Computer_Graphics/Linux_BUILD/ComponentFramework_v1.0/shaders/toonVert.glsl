#version 450
#extension GL_ARB_separate_shader_objects : enable

//Attributes
layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec4 vNormal;

out vec3 vertNormal;
out vec3 lightDir;
out vec3 eyeDir;
//out vec3 vertDir;

//Uniforms
layout(location = 0) uniform mat4 projectionMatrix;
layout(location = 1) uniform mat4 viewMatrix;
layout(location = 2) uniform mat4 modelMatrix;
layout(location = 3) uniform vec3 lightPos;

void main() {

    //mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    mat3 normalMatrix = mat3((modelMatrix));
    vertNormal = normalize(normalMatrix * vNormal.xyz); //Rotate the normal to the correct orientation

    vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex);
    vec3 vertDir = normalize(vertPos);
    eyeDir = -vertDir;
    lightDir = normalize(lightPos + -vertPos);

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vVertex;
}