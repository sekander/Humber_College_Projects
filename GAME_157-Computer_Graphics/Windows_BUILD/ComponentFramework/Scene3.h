#ifndef SCENE3_H
#define SCENE3_H
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

/*
struct LightInfo {
	Vec3 light_position;
	Vec3 light_colour;
};

LightInfo light;
*/


class Scene3 : public Scene {
private:
	
	Actor* skull;
	Actor* lEye;
	Actor* rEye;

	//Trackball* trackball;
	Camera* camera;

	Shader* shader;
	Mesh* skullMesh;
	//Texture* texture;
	//On stack 16 floats 
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;

	Matrix4 normalMatrix;

	Matrix4 MVP;

	float x_rotation_angle;
	float y_rotation_angle;

	Vec3 lightPos0;
	Vec3 lightPos1;

	Vec3 light_colour_1;
	Vec3 light_colour_2;
	int number_of_lights;



public:
	explicit Scene3();
	virtual ~Scene3();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE0_H