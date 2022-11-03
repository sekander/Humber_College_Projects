#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene5.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Trackball.h"
#include "Camera.h"
#include "Noise.h"

Scene5::Scene5():shader(nullptr),
				 sphere(nullptr),
				 camera(nullptr)

{
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene5::~Scene5() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
}

bool Scene5::OnCreate() {
	camera = new Camera();

	camera->LoadSkybox(
						"textures/StarSkyboxPosx.png", "textures/StarSkyboxPosy.png", "textures/StarSkyboxPosz.png", 
						"textures/StarSkyboxNegx.png", "textures/StarSkyboxNegY.png", "textures/StarSkyboxnegz.png"

	);

	camera->OnCreate();

	noiseTextureID = CreateNoise3D();

	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);



	
	sphere = new Actor(nullptr);
	sphere->OnCreate();
	sphere->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	sphere->GetMesh()->OnCreate();




	shader = new Shader(nullptr, "shaders/noiseVert.glsl", "shaders/turbulenceFrag.glsl");





	//sphere->SetTexture(new Texture());
	//sphere->GetTexture()->LoadImage("textures/moon.jpg");




	shader->OnCreate();


	




	return true;
}

void Scene5::OnDestroy() {
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);

	DeleteNoise3D();

	if(camera) {
		camera->OnDestroy();
		delete camera;
	}



	sphere->GetMesh()->OnDestroy();
	delete sphere->GetMesh();
	delete sphere->GetTexture();
	sphere->OnDestroy();
	delete sphere;



	shader->OnDestroy();
	delete shader;

}

void Scene5::HandleEvents(const SDL_Event &sdlEvent) {

	camera->HandleEvents(sdlEvent);


	
	switch( sdlEvent.type ) {
    case SDL_KEYDOWN:
		if(sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
		{
		
			sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::rotate(+5.0f, Vec3(0.0f, 1.0f, 0.0f)));


		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
		
			sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::rotate(-5.0f, Vec3(0.0f, 1.0f, 0.0f)));

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
		{

			sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::rotate(+5.0f, Vec3(1.0f, 0.0f, 0.0f)));

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
		{

			sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::rotate(-5.0f, Vec3(1.0f, 0.0f, 0.0f)));

		}
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

void Scene5::Update(const float deltaTime) {
	
	static float total_time = 0.0f;
	total_time += deltaTime;

	offset.x += 0.001f;
	offset.y += 0.001f;
	offset.z -= 0.005f;


				  
}

void Scene5::Render() const {
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Draw the camera(skybox)
	camera->Render();
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_CULL_FACE);








	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->GetViewMatrix() );
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere->GetModelMatrix());
	glUniform3fv(shader->GetUniformID("offset"), 1, offset);

	
	
	
	



	glBindTexture(GL_TEXTURE_3D, noiseTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, camera->GetSkybox()->GetTextureID());

	sphere->GetMesh()->Render();

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindTexture(GL_TEXTURE_3D, 0);


	

	glUseProgram(0);
}



	
