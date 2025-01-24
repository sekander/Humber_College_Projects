#version 450
#extension GL_ARB_separate_shader_objects : enable

//Attributes
layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 uvCoord;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;



uniform vec3 lightPos0;
uniform vec3 lightPos1;

uniform vec3 light_colour_1;
uniform vec3 light_colour_2;


layout(location = 0) out vec3 vertNormal;
layout(location = 1) out vec3 lightDir[2];
//layout(location = 2) out vec3 lightDir1;
layout(location = 3) out vec3 eyeDir;
layout(location = 4) out vec2 texCoords;
layout(location = 5) out vec3 lightColours[2];



void main() {
    
    texCoords = uvCoord;
    texCoords.y *= -1.0;

    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    //mat3 normalMatrix = mat3((modelMatrix));
    vertNormal = normalize(normalMatrix * vNormal); //Rotate the normal to the correct orientation

    vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex);
    vec3 vertDir = normalize(vertPos);
    eyeDir = -vertDir;

    lightDir[0] = normalize(lightPos0 - vertPos);
    lightDir[1] = normalize(lightPos1 - vertPos);

    lightColours[0] = light_colour_1;
    lightColours[1] = light_colour_2;

   // int i = number_of_lights;

 //   lightcolour_1 = light_colour_1;
//    lightcolour_2 = light_colour_2;


    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vVertex;
}