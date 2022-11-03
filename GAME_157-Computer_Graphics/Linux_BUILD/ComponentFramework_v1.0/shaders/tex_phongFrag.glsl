#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;

layout(location = 0) in vec3 vertNormal; 
layout(location = 1) in vec3 lightDir; 
layout(location = 2) in vec3 eyeDir; 
layout(location = 3) in vec2 texCoords;


uniform sampler2D myTexture;

void main() {

    //specular light
    //vec4 ks = vec4(0.3, 0.3, 0.3, 0.0);
    //vec4 kd = vec4(0.5, 0.6, 0.1, 0.0);
    
    //Flood light
    vec4 kd = vec4(0.6, 0.6, 0.6, 0.0);
    //ambient
    vec4 ka = 0.01 * kd;
    vec4 ks = 0.7 * kd;



    vec4 texDiffuse = texture(myTexture, texCoords);


    float diff = max(dot(vertNormal, lightDir), 0.0); 
    vec3 reflection = normalize(reflect(-lightDir, vertNormal));
    float spec = max(dot(eyeDir, reflection), 0.0);
    //Shinnyness
    spec = pow(spec, 14.0);
    //fragColor = ka + (diff * kd) + (spec * ks);
    fragColor = ka + (kd * texDiffuse * diff) + (ks * spec);
}