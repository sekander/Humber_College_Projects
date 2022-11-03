#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include <memory>
#include <vector>
#include "Component.h"
using namespace MATH;

/// Forward declarations (don't have to do these, will just need to #include)
union SDL_Event;
class CameraActor;
class Actor;
class LightActor;

class Scene1 : public Scene {
private:
	// 2022-04-01
	// Let's use shared pointers now
	// I stuffed the using Ref call in Component.h, which is in Actor.h, which is in Scene.h. Phew!
	Ref<CameraActor> camera; // in the future we'll get rid of the camera pointer, and have the Scene capable to hold a camera
	Ref<Actor> gameboard;
	Ref<LightActor> light;
	Ref<Actor> checker_red;
	Ref<Actor> checker_black;
	Ref<Actor> checker_white;

	Vec3 anchorPoint;
	// 2022-03-13 Umer trying an anchor constraint
	float rodLength1;
	float rodLength2;
	float rodLength3;

public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event &sdlEvent);
};


#endif // SCENE1_H