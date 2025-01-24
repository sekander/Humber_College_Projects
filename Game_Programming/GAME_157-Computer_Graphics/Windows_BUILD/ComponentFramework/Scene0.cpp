#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

Scene0::Scene0():shader(nullptr),
				 sphere(nullptr),
				 mesh(nullptr)
{
	//shader = nullptr;
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
}

bool Scene0::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
	sphere = new Actor(nullptr);
	sphere->OnCreate();

	//mesh = new Mesh(nullptr, "meshes/Sphere.obj");
	mesh = new Mesh(nullptr, "meshes/Mario.obj");
	mesh->OnCreate();

	//shader = new Shader(nullptr, "shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	//shader = new Shader(nullptr, "shaders/phongVert.glsl", "shaders/phongFrag.glsl");
	shader = new Shader(nullptr, "shaders/tex_phongVert.glsl", "shaders/tex_phongFrag.glsl");
	shader->OnCreate();

	texture = new Texture();
	texture->LoadImage("textures/mario_main.png");
	
	//Clipping pane 100
	projectionMatrix = MMath::perspective(45.0f, 16.0f / 9.0f, 0.5, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.f, 0.f, 5.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f));
	
	
	modelMatrix.loadIdentity();
	lightPos = Vec3(10.0f, -10.f, 0.f);

	return true;
}

void Scene0::OnDestroy() {
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;

	mesh->OnDestroy();
	delete mesh;


	shader->OnDestroy();
	delete shader;

	texture->~Texture();
	delete texture;
}

void Scene0::HandleEvents(const SDL_Event &sdlEvent) {
	switch( sdlEvent.type ) {
    case SDL_KEYDOWN:
		break;

	case SDL_MOUSEMOTION:          
		break;

	case SDL_MOUSEBUTTONDOWN:              
		break; 

	case SDL_MOUSEBUTTONUP:            
	break;

	default:
		break;
    }
}

void Scene0::Update(const float deltaTime) {
	
	static float total_time = 0.0f;
	total_time += deltaTime;

	modelMatrix = MMath::rotate(total_time * 50.0f , Vec3(0.0f, 1.0f, 0.0f));
	
}

void Scene0::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); 
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);
	glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	//mesh->Render(GL_LINES);
	mesh->Render(GL_TRIANGLES);
	glUseProgram(0);
}



	
