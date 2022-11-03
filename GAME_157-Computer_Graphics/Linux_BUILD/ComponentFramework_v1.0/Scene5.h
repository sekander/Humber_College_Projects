#ifndef SCENE5_H
#define SCENE5_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include "GL/glew.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Shader;
class Actor;
class Mesh;
class Texture;
class Trackball;
class Camera;



class Scene5 : public Scene {
private:
	Camera* camera;
	Actor* sphere;
	Shader* shader;

	//Vec3	lightPos;
	float 	totalTime;
	GLuint  noiseTextureID;

	Vec3 offset;




public:
	explicit Scene5();
	virtual ~Scene5();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE0_H