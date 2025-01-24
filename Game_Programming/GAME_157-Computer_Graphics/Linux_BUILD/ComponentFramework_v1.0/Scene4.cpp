#include <GL/glew.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "Debug.h"
#include "Scene4.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Trackball.h"
#include "Camera.h"

Scene4::Scene4():shader(nullptr),
				 skull(nullptr),
				 x_rotation_angle(0.f),
				 y_rotation_angle(0.f),
				 camera(nullptr)

{
	//shader = nullptr;
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
	//trackball = new Trackball();
}

Scene4::~Scene4() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
	//delete trackball;
	//delete camera;
}

bool Scene4::OnCreate() {
	camera = new Camera();

	camera->LoadSkybox(
						"textures/posx.jpg", "textures/posy.jpg", "textures/posz.jpg", 
						"textures/negx.jpg", "textures/negy.jpg", "textures/negz.jpg"

	);

	camera->OnCreate();

	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
	
	skull = new Actor(nullptr);
	skull->OnCreate();
	//skull->SetMesh(new Mesh(nullptr, "meshes/enterprise.obj"));
	skull->SetMesh(new Mesh(nullptr, "meshes/Skull.obj"));
	skull->GetMesh()->OnCreate();




	shader = new Shader(nullptr, "shaders/reflectVert.glsl", "shaders/reflectFrag.glsl");






	shader->OnCreate();



	//Clipping pane 100
	projectionMatrix = MMath::perspective(45.0f, 16.0f / 9.0f, 0.5, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.f, 0.f, 10.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f));
	//modelMatrix.loadIdentity();

	

	normalMatrix = MMath::transpose(MMath::inverse(skull->GetModelMatrix()));

	


//	lightPos = Vec3(0.0f, 0.0f, 0.0f);

	return true;
}

void Scene4::OnDestroy() {
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);

	if(camera) {
		camera->OnDestroy();
		delete camera;
	}

	skull->GetMesh()->OnDestroy();
	delete skull->GetMesh();
	delete skull->GetTexture();
	skull->OnDestroy();
	delete skull;




	shader->OnDestroy();
	delete shader;


}

void Scene4::HandleEvents(const SDL_Event &sdlEvent) {

	camera->HandleEvents(sdlEvent);

	switch( sdlEvent.type ) {
    case SDL_KEYDOWN:
		if(sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
		{
		
			skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::rotate(+5.0f, Vec3(0.0f, 1.0f, 0.0f)));


		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
		
			skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::rotate(-5.0f, Vec3(0.0f, 1.0f, 0.0f)));

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
		{

			skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::rotate(+5.0f, Vec3(1.0f, 0.0f, 0.0f)));

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
		{

			skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::rotate(-5.0f, Vec3(1.0f, 0.0f, 0.0f)));

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

void Scene4::Update(const float deltaTime) {
	
	static float total_time = 0.0f;
	total_time += deltaTime;

				  
}

void Scene4::Render() const {
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
	//glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, );
	glUniformMatrix4fv(shader->GetUniformID("normalMatrix"), 1, GL_FALSE, normalMatrix);
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, skull->GetModelMatrix());
	//glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, MVP);

	
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, camera->GetSkybox()->GetTextureID());
	//glBindTexture(GL_TEXTURE_2D, 0);
	//mesh->Render();
	skull->GetMesh()->Render();
	//skull->GetMesh()->Render(GL_TRIANGLES);

	//Unbind texture
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);
}



	
