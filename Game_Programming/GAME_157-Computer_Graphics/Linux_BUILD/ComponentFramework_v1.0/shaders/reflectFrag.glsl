#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;
//layout(location = 0) in vec3 texCoords;


in vec3 vertNormal;
in vec3 vertDir;

uniform samplerCube skyboxTexture;



void main() {

    vec3 vert_reflection = reflect(vertDir, vertNormal);
    vert_reflection.x *= -1.0;

    vec3 vert_refraction = refract(-vertDir, vertNormal, 1.0/1.52);

    fragColor = texture(skyboxTexture, vert_reflection * vert_refraction);
//    fragColor = texture(skyboxTexture, vert_refraction);


    //fragColor = texture(skyboxTexture, texCoords);
    //fragColor = vec4(1, 0, 0, 0);
}
