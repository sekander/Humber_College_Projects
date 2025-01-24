#pragma once
#include "Actor.h"
#include "Matrix.h"

#include "Trackball.h"
#include "Skybox.h"

//class Skybox;

class Camera : public Actor {

private:
    Matrix4 projectionMatrix;
    Matrix4 viewMatrix;

    Matrix4 rotation;
    Matrix4 translation;

    Trackball* trackball;
    Skybox *skybox;

public:

    Camera();
    ~Camera();

    void Render() const override;

    //bool OnCreate(char* a ) override;
    bool OnCreate() override;
    void OnDestroy() override;
    void HandleEvents(const SDL_Event& sdlEvent);


    inline Matrix4 GetProjectionMatrix() {return projectionMatrix;}
    inline Matrix4 GetViewMatrix() {return viewMatrix;}

    void LoadSkybox(char* a, char* b, char* c, char* d, char* e, char* f){
        	a_pic = a;
            b_pic = b;
            c_pic = c;
            d_pic = d;
            e_pic = e;
            f_pic = f;
            
       
    };

    Skybox* GetSkybox(){
        return skybox;

    }

    char* a_pic;
    char* b_pic;
    char* c_pic;
    char* d_pic;
    char* e_pic;
    char* f_pic;


};