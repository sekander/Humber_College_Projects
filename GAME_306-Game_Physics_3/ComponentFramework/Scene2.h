#pragma once
#include "Scene.h"
#include <unordered_map>
#include "Actor.h"
#include "LightActor.h"
#include "CameraActor.h"

// 2022-04-01
// Put in the actor stuff here! Inherit from Actor
// and override the addcomponent so we can have multuple actors

class Scene2 : public Scene
{
public:

	bool renderMeshes = true;
	bool renderCollisionShapes = true;
	explicit Scene2();
	virtual ~Scene2();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event& sdlEvent);


	// Keep track of Actors from XML asset manager
	std::unordered_map< std::string, Ref<Component>> actors;
	// We only have one camera and light, so they don't need to be in the map
	Ref<CameraActor> camera;
	Ref<LightActor> light;
	// We'll use a ray to click on our geometry objects 
	// GEOMETRY::RayIntersectionInfo rayInfo; (TODO)

};

