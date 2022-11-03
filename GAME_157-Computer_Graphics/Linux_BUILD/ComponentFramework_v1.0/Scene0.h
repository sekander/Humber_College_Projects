#ifndef SCENE0_H
#define SCENE0_H
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

class Scene0 : public Scene {
private:
	
	Actor* sphere;
	Shader* shader;
	Mesh* mesh;
	//Texture* texture;
	Texture* earthTexture;
	Texture* moonTexture;
	//On stack 16 floats 
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 earthModelMatrix;
	Matrix4 moonModelMatrix;
	Vec3 lightPos;

public:
	explicit Scene0();
	virtual ~Scene0();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE0_H