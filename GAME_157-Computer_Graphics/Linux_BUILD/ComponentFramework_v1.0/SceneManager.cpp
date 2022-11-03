//#include <SDL.h>
#include <SDL2/SDL.h>
#include "SceneManager.h"
#include "Timer.h"
#include "Window.h"
#include "Scene0.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Scene6.h"
#include "Scene7.h"


SceneManager::SceneManager(): 
	currentScene(nullptr), window(nullptr), timer(nullptr),
	fps(60), isRunning(false), fullScreen(false) {
	//Debug::Info("Starting the SceneManager", __FILE__, __LINE__);
}

SceneManager::~SceneManager() {
	if (currentScene) {
		currentScene->OnDestroy();
		delete currentScene;
		currentScene = nullptr;
	}
	
	if (timer) {
		delete timer;
		timer = nullptr;
	}

	if (window) {
		delete window;
		window = nullptr;
	}
	Debug::Info("Deleting the SceneManager", __FILE__, __LINE__);
}

bool SceneManager::Initialize(std::string name_, int width_, int height_) {

	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Failed to initialize Window object", __FILE__, __LINE__);
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		Debug::FatalError("Failed to initialize Timer object", __FILE__, __LINE__);
		return false;
	}

	/********************************   Default first scene   ***********************/
	BuildNewScene(SCENE_NUMBER::SCENE5);
	
	return true;
}

/// This is the whole game
void SceneManager::Run() {
	timer->Start();
	isRunning = true;
	while (isRunning) {
		timer->UpdateFrameTicks();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();
		HandleEvents();
		SDL_GL_SwapWindow(window->getWindow());
		SDL_Delay(timer->GetSleepTime(fps));
	}
}

void SceneManager::HandleEvents() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_EventType::SDL_QUIT) {
			isRunning = false;
			return;
		}
		else if (sdlEvent.type == SDL_KEYDOWN) {
			switch (sdlEvent.key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE:
			case SDL_SCANCODE_Q:
				isRunning = false;
				return;
				[[fallthrough]]; /// C17 Prevents switch/case fallthrough warnings
			case SDL_SCANCODE_1:
				BuildNewScene(SCENE_NUMBER::SCENE1);
				break;
			case SDL_SCANCODE_2:
				BuildNewScene(SCENE_NUMBER::SCENE2);
				break;
			case SDL_SCANCODE_3:
				BuildNewScene(SCENE_NUMBER::SCENE3);
				break;
			case SDL_SCANCODE_4:
				BuildNewScene(SCENE_NUMBER::SCENE4);
				break;
				
			case SDL_SCANCODE_5:
				BuildNewScene(SCENE_NUMBER::SCENE5);
				break;
				
			case SDL_SCANCODE_6:
				BuildNewScene(SCENE_NUMBER::SCENE6);
				break;
			case SDL_SCANCODE_7:
				BuildNewScene(SCENE_NUMBER::SCENE7);
				break;
			case SDL_SCANCODE_0:
				BuildNewScene(SCENE_NUMBER::SCENE0);
				break;
			default:
				break;
			}
		}
		if (currentScene == nullptr) {
			Debug::FatalError("Failed to initialize Scene", __FILE__, __LINE__);
			isRunning = false;
			return;
		}
		currentScene->HandleEvents(sdlEvent);
	}
}

void SceneManager::BuildNewScene(SCENE_NUMBER scene) {
	bool status; 

	if (currentScene != nullptr) {
		currentScene->OnDestroy();
		delete currentScene;
		currentScene = nullptr;
	}

	switch (scene) {
	case SCENE_NUMBER::SCENE0:
		currentScene = new Scene0();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE1:
		currentScene = new Scene1();
		status = currentScene->OnCreate();
		break;
		
	case SCENE_NUMBER::SCENE2:
		currentScene = new Scene2();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE3:
		currentScene = new Scene3();
		status = currentScene->OnCreate();
		break;
	case SCENE_NUMBER::SCENE4:
		currentScene = new Scene4();
		status = currentScene->OnCreate();
		break;
	
	case SCENE_NUMBER::SCENE5:
		currentScene = new Scene5();
		status = currentScene->OnCreate();
		break;
	case SCENE_NUMBER::SCENE6:
		currentScene = new Scene6();
		status = currentScene->OnCreate();
		break;
		
	case SCENE_NUMBER::SCENE7:
		currentScene = new Scene7();
		status = currentScene->OnCreate();
		break;

	default:
		Debug::Error("Incorrect scene number assigned in the manager", __FILE__, __LINE__);
		currentScene = nullptr;
		break;
	}	
}


