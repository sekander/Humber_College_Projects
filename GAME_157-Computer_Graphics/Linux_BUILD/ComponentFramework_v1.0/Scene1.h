#ifndef SCENE1_H
#define SCENE1_H
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

class Scene1 : public Scene {
private:
	
	Actor* sphere;
	Shader* shader;
	Mesh* mesh;
	Texture* texture;
	//On stack 16 floats 
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;
	Vec3 light_colour_1;
	Vec3 light_colour_2;
	Vec3 lightPos0;
	Vec3 lightPos1;

//	Vec3 light_positions[2];
//	Vec3 light_colours[2];

	int number_of_lights;
	

public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE0_H