#pragma once

#include <GL/glew.h>
#include "Component.h"
#include "Shader.h"

class Mesh;
//class Shader;


class Skybox : Component 
{
private:

    GLuint textureID;
    Mesh* mesh;
    Shader* shader;

    const char *posXfilename, *posYfilename, *posZfilename, *negXfilename, *negYfilename, *negZfilename;

public:
Skybox(const char *posXfilename,
       const char *posYfilename,
       const char *posZfilename,
       const char *negXfilename,
       const char *negYfilename,
       const char *negZfilename
       );
       
~Skybox();

virtual bool OnCreate() override;
virtual void OnDestroy() override;
virtual void Update(const float deltaTime_) override;
virtual void Render() const override;
    
Shader* GetShader(){return shader;}

GLuint GetTextureID()
{
    return textureID;
}

};