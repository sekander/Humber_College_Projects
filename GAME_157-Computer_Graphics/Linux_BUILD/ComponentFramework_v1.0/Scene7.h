#ifndef SCENE7_H
#define SCENE7_H
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

/*
struct LightInfo {
	Vec3 light_position;
	Vec3 light_colour;
};

LightInfo light;
*/


class Scene7 : public Scene {
private:
	
	Actor* skull;
	Shader* shader;
	Mesh* skullMesh;
	//Texture* texture;
	Texture* skullTexture;
	//On stack 16 floats 
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 skullModelMatrix;

	Matrix4 normalMatrix;

	Matrix4 MVP;

	float x_rotation_angle;
	float y_rotation_angle;

	Vec3 lightPos;
	Vec3 light_colour_1;
	//Vec3 light_colour_2;
	int number_of_lights;
	Vec3 light_positons[1];
	Vec3 light_colours[1];

	int arrayOfInts[5];
	//Vec3 lightPos1;

public:
	explicit Scene7();
	virtual ~Scene7();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE0_H