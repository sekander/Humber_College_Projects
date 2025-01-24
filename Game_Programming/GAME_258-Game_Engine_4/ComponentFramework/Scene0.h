#ifndef SCENE0_H
#define SCENE0_H
#include "Vector.h"
#include "Matrix.h"

#include "Scene.h"
#include "LoadingGameObjects.h"
#include <vector>
#include <unordered_map>


using namespace MATH;

/// Forward declarations 
union SDL_Event;
class CameraActor;
class LightActor;
class Actor;

class Scene0 : public Scene {
private:

	std::vector<Ref<Actor>> actors;
	std::unordered_map<std::string, Ref<Actor>> actors_map;

	Ref<CameraActor> camera;
	Ref<LightActor> light;
	Ref<Actor> hammer;
	Ref<Actor> mario;

	LoadingGameObjects* xml;

	int x, y;

public:
	explicit Scene0();
	virtual ~Scene0();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event& sdlEvent);


};


#endif // SCENE0_H