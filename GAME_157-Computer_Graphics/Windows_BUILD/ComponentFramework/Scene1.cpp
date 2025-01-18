#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene1.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

Scene1::Scene1():shader(nullptr),
				 sphere(nullptr),
				 mesh(nullptr),
				 texture(nullptr)
{
	//shader = nullptr;
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene1::~Scene1() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
}

bool Scene1::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
	sphere = new Actor(nullptr);
	sphere->OnCreate();

	//mesh = new Mesh(nullptr, "meshes/Sphere.obj");
	mesh = new Mesh(nullptr, "meshes/Mario.obj");
	//mesh = new Mesh(nullptr, "meshes/Skull.obj");
	mesh->OnCreate();

	//shader = new Shader(nullptr, "shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	//shader = new Shader(nullptr, "shaders/phongVert.glsl", "shaders/phongFrag.glsl");
	shader = new Shader(nullptr, "shaders/mult_texphongVert.glsl", "shaders/mult_texphongFrag.glsl");
	shader->OnCreate();

	texture = new Texture();
	texture->LoadImage("textures/mario_fire.png");
	//texture->LoadImage("textures/skull_texture.png");
	//texture->LoadImage("textures/earthclouds.jpg");
	
	//Clipping pane 100
	projectionMatrix = MMath::perspective(45.0f, 16.0f / 9.0f, 0.5, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.f, 0.f, 5.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f));
	
	
	modelMatrix.loadIdentity();
	//lightPos = Vec3(10.0f, -10.f, 0.f);
	lightPos0 = Vec3( 20.0f, 0.0f, 10.0f);
	lightPos1 = Vec3(-20.0f, 0.0f, 10.0f);
	light_colour_1 =    Vec3(  0.6f, 0.1f, 0.1f);
	light_colour_2 =    Vec3(  0.1f, 0.6f, 0.1f);

	light_positions[0] = Vec3( 20.0f, 0.0f, 10.0f);
	light_positions[1] = Vec3(-20.0f, 0.0f, 10.0f);

	light_colours[0] = Vec3(  0.6f, 0.1f, 0.1f);
	light_colours[1] = Vec3(  0.1f, 0.6f, 0.1f);

	number_of_lights = 2;

	return true;
}

void Scene1::OnDestroy() {
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

void Scene1::HandleEvents(const SDL_Event &sdlEvent) {
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

void Scene1::Update(const float deltaTime) {
	
	static float total_time = 0.0f;
	total_time += deltaTime;

	//modelMatrix = MMath::rotate(total_time * 50.0f , Vec3(0.0f, 1.0f, 0.0f));
	
	modelMatrix = MMath::rotate(total_time * 50.0f , Vec3(0.0f, 1.0f, 0.0f)) *
				  MMath::rotate(0.0f, Vec3(1.0f, 0.0f, 0.0f));
}

void Scene1::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); 
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);


	//glUniform1i(shader->GetUniformID("number_of_lights"), number_of_lights);

	glUniform3fv(shader->GetUniformID("lightPos0"), 1, lightPos0);
	glUniform3fv(shader->GetUniformID("lightPos1"), 1, lightPos1);
	//glUniform3fv(shader->GetUniformID("light_colours"), number_of_lights, light_colours[0]);


	glUniform3fv(shader->GetUniformID("light_colour_1"), 1, light_colour_1);
	glUniform3fv(shader->GetUniformID("light_colour_2"), 1, light_colour_2);


	//glUniform3fv(shader->GetUniformID("light_colours"), 2, light_colours[0]);

	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	//mesh->Render(GL_LINES);
	mesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}



	
