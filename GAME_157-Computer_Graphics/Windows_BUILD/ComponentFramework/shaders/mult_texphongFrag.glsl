#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;

layout(location = 0) in vec3 vertNormal;

layout(location = 1) in vec3 lightDir[2]; 
//layout(location = 2) in vec3 lightDir1; 

layout(location = 3) in vec3 eyeDir; 
layout(location = 4) in vec2 texCoords;
layout(location = 5) in vec3 lightColours[2];






uniform sampler2D myTexture;





void main() {

    float diff[2];
    vec3  reflection[2];
    float spec[2];
    vec4  kd[2];

    for(int i =0; i < 2; i++)
    {
        kd[i] = vec4(lightColours[i], 0.0);
        
        //ambient
        vec4 ka = 0.01 * kd[i];
        vec4 ks = 0.7 * kd[i];

        vec4 texDiffuse = texture(myTexture, texCoords);

        diff[i] = max(dot(vertNormal, lightDir[i]), 0.0); 
        reflection[i] = normalize(reflect(-lightDir[i], vertNormal));


        spec[i] = max(dot(eyeDir, reflection[i]), 0.0);
        //Shinnyness
        spec[i] = pow(spec[i], 14.0);



        //fragColor = ka + (diff * kd) + (spec * ks);
        fragColor = ka;
        fragColor += (kd[0] * texDiffuse * diff[0]) + (ks * spec[0]);
        fragColor += (kd[1] * texDiffuse * diff[1]) + (ks * spec[1]);


        
    }

}