#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"

#include <vector>

#include <unordered_map>
#include "LoadingGameObjects.h"


using namespace MATH;

/// Forward declarations 
union SDL_Event;
class CameraActor;
class LightActor;
class Actor;

class Scene1 : public Scene {
private:
	//CameraActor* camera;
	//Actor* gameboard;
	//Actor* checker;
	//Actor* black_checker;

	std::vector<Ref<Actor>> checker_pieces;

	std::vector<Ref<Actor>> actors;
	std::unordered_map<std::string, Ref<Actor>> actors_map;
	std::unordered_map<std::string, Ref<Actor>>::iterator it = actors_map.begin();


	LoadingGameObjects* xml;


	Ref<CameraActor> camera;
	Ref<LightActor> light;
	Ref<Actor> gameboard;
	Ref<Actor> checker;
	//Ref<Actor> checker_red;
	//Ref<Actor> checker_black;


	//LightActor* light;
	int x, y;

public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event& sdlEvent);


};


#endif // SCENE1_H