#ifndef SCENE4_H
#define SCENE4_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Shader;
class Actor;
class Mesh;
class Texture;
class Trackball;
class Camera;



class Scene4 : public Scene {
private:
	


	Camera* camera;

	Shader* shader;

	Actor* skull;
    GLuint textureID;


	

	//Actor* sphere;
	//Texture* texture;
	//On stack 16 floats 
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;


	Matrix4 normalMatrix;

	Matrix4 MVP;

	float x_rotation_angle;
	float y_rotation_angle;



public:
	explicit Scene4();
	virtual ~Scene4();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE0_H