#version 450
#extension GL_ARB_separate_shader_objects : enable

//Attributes
layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 uvCoord;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;


uniform vec3 lightPos0;
uniform vec3 lightPos1;
uniform vec3 light_colour_1;
uniform vec3 light_colour_2;

uniform int number_of_lights;
uniform vec3 light_positions[2];
uniform vec3 light_colours[2];

uniform int arrayOfInts[5];



layout(location = 0) out vec2 texCoords;
layout(location = 1) out vec4 LightIntesity[2];
//layout(location = 2) out vec4 LightIntesity_1;
layout(location = 3) out vec4 LightSpec[2];
//layout(location = 4) out vec4 LightSpec_1;

layout(location = 5) out vec4 Ka;

/*
struct LightInfo {
    vec3 light_position;
    vec3 light_colour;
}

uniform LightInfo Light;
*/
void main() {

  /*  
arrayOfInts[0] = 0; 
arrayOfInts[1] = 1; 
arrayOfInts[2] = 2; 
arrayOfInts[3] = 45; 
arrayOfInts[4] = 3; 
*/


    texCoords = uvCoord;
    texCoords.y *= -1.0;

    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    normalMatrix = mat3((modelMatrix));
    vec3 vertNormal = normalize(normalMatrix * vNormal); //Rotate the normal to the correct orientation

    vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex * arrayOfInts[0]);
    vec3 vertDir = normalize(vertPos);
    vec3 eyeDir = -vertDir;


    for(int i = 0; i < number_of_lights; i++)
    {
        vec3 light_direction = normalize(lightPos0 - vertPos);
        //vec3 light_direction = normalize(light_positions[i] - vertPos);
        //vec3 light_direction[2];
        //light_direction[0] = normalize(lightPos0 - vertPos);
        //light_direction[1] = normalize(lightPos1 - vertPos);
        
        float diff;
        vec3 reflection;
        float spec;

        //vec4 kd = vec4(light_colours[i], 0.0);
        //vec4 kd[2];
        vec4 kd = vec4(light_colour_1, 0.0);
        //kd[1] = vec4(light_colour_2, 0.0);


        Ka = 0.01 * kd;
        vec4 ks = 0.7 * kd;

        diff =       max(dot(vertNormal, light_direction), 0.0);
        reflection = normalize(reflect(-light_direction, vertNormal));
        spec =       max(dot(eyeDir, reflection), 0.0);
        spec =       pow(spec, 14.0);

        LightIntesity[i]  = diff * kd;
        LightSpec[i]     = spec * ks;

        //fragColor = Ka; 
    }

    /*

    vec3 lightDir0 = normalize(lightPos0 - vertPos);
    //lightDir1 = normalize(lightPos1 - vertPos);


    float diff[2];
    vec3 reflection[2];
    float spec[2];
    //specular light
    //vec4 ks = vec4(0.3, 0.3, 0.3, 0.0);
    //vec4 kd = vec4(0.5, 0.6, 0.1, 0.0);
    
    //Flood light
    //vec4 kd = vec4(0.1, 0.6, 0.1, 0.0);
    vec4 kd = vec4(light_colour_1, 0.0);
    //vec4 kd_2 = vec4(light_colour_2, 0.0);
    
    //ambient
    //vec4 ka = 0.01 * kd;
    Ka = 0.01 * kd;
    vec4 ks = 0.7 * kd;


    diff[0] = max(dot(vertNormal, lightDir0), 0.0); 
//    diff[1] = max(dot(vertNormal, lightDir1), 0.0); 


    reflection[0] = normalize(reflect(-lightDir0, vertNormal));
 //   reflection[1] = normalize(reflect(-lightDir1, vertNormal));


    spec[0] = max(dot(eyeDir, reflection[0]), 0.0);
    //Shinnyness
    spec[0] = pow(spec[0], 14.0);
    
//    spec[1] = max(dot(eyeDir, reflection[1]), 0.0);
    //Shinnyness
//    spec[1] = pow(spec[1], 14.0);

  //  Ka = ka;
    LightIntesity = diff[0] * kd;
    LightSpec = spec[0] * ks;

    */

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vVertex;
}