#version 450
#extension GL_ARB_separate_shader_objects : enable

in vec3 vertNormal;
in vec3 lightDir;
in vec3 eyeDir;

layout(location = 0) out vec4 fragColor;

void main() {

    vec4 ks = vec4(0.3, 0.3, 0.3, 0.0);
    vec4 kd = vec4(0.5, 0.6, 0.1, 0.0);
    vec4 ka = 0.1 * kd;

    float diff = max(dot(vertNormal, lightDir), 0.0); 

    if(diff > 0.5)
        diff = 1.0;
    else
        diff = 0.2;


    fragColor = (diff * kd);
}