#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;
layout(location = 0) in vec3 texCoords;


uniform samplerCube skyboxTexture;

void main() {

    fragColor = texture(skyboxTexture, texCoords);

    //fragColor = vec4(1, 0, 0, 0);
}