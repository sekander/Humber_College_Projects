#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;


layout(location = 0) in vec2 texCoords;

layout(location = 1) in vec4 LightIntesity[2];
layout(location = 3) in vec4 LightSpec[2];
layout(location = 5) in vec4 Ka;


uniform sampler2D myTexture;


void main() {

    vec4 texDiffuse = texture(myTexture, texCoords);

    
    fragColor = Ka;
    //for(int i =0; i < 2; i++){
        fragColor += (LightIntesity[0] * texDiffuse) + (LightSpec[0]);    
        fragColor += (LightIntesity[1] * texDiffuse) + (LightSpec[1]);    
    //}
}