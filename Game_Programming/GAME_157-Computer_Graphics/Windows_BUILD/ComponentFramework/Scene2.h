#ifndef SCENE2_H
#define SCENE2_H
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


class Scene2 : public Scene {
private:
	
	Actor* skull;
	Actor* lEye;
	Actor* rEye;
	Camera* camera;


	Trackball *trackball;

	Shader* shader;
	Mesh* skullMesh;
	//Texture* texture;
	Texture* skullTexture;

	//On stack 16 floats 
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	//Matrix4 skullModelMatrix;
	float x_rotation_angle;
	float y_rotation_angle;

	Vec3 lightPos;

public:
	explicit Scene2();
	virtual ~Scene2();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE0_H