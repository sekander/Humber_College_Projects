#include <GL/glew.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "Debug.h"
#include "Scene3.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Trackball.h"
#include "Camera.h"

Scene3::Scene3():shader(nullptr),
				 skull(nullptr),
				 lEye(nullptr),
				 rEye(nullptr),
				 x_rotation_angle(0.f),
				 y_rotation_angle(0.f),
				 camera(nullptr)

{
	//shader = nullptr;
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
	//trackball = new Trackball();
}

Scene3::~Scene3() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
	//delete trackball;
	//delete camera;
}

bool Scene3::OnCreate() {
	camera = new Camera();

	camera->LoadSkybox(
						"textures/posx.jpg", "textures/posy.jpg", "textures/posz.jpg", 
						"textures/negx.jpg", "textures/negy.jpg", "textures/negz.jpg"

	);

	camera->OnCreate();

	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
	skull = new Actor(nullptr);
	skull->OnCreate();
	skull->SetMesh(new Mesh(nullptr, "meshes/Skull.obj"));
	skull->GetMesh()->OnCreate();

	lEye = new Actor(skull);
	lEye->OnCreate();
	lEye->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	lEye->GetMesh()->OnCreate();
	lEye->SetTexture(new Texture());
	lEye->GetTexture()->LoadImage("textures/evilEye.jpg");
	lEye->SetModelMatrix(	MMath::translate(Vec3(-0.6f, 0.2f, 0.3f)) * 
							MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f)) * 
							MMath::scale(Vec3(0.3f, 0.3f, 0.3f)));


	rEye = new Actor(skull);
	rEye->OnCreate();
	rEye->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	rEye->GetMesh()->OnCreate();
	rEye->SetTexture(new Texture());
	rEye->GetTexture()->LoadImage("textures/evilEye.jpg");
	rEye->SetModelMatrix(	MMath::translate(Vec3(0.6f, 0.2f, 0.3f)) * 
							MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f)) * 
							MMath::scale(Vec3(0.3f, 0.3f, 0.3f)));




	shader = new Shader(nullptr, "shaders/mult_texphongVert.glsl", "shaders/mult_texphongFrag.glsl");
//	shader = new Shader(nullptr, "shaders/toonVert.glsl", "shaders/toonFrag.glsl");

	shader->OnCreate();

	skull->SetTexture(new Texture());
	skull->GetTexture()->LoadImage("textures/skull_texture.jpg");

	//Clipping pane 100
	projectionMatrix = MMath::perspective(45.0f, 16.0f / 9.0f, 0.5, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.f, 0.f, 10.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f));
	
	MVP = skull->GetModelMatrix() * viewMatrix;

	normalMatrix = MMath::transpose(MMath::inverse(MVP));

	
	lightPos0 = Vec3( 20.0f, 0.0f, 10.0f);
	lightPos1 = Vec3(-20.0f, 0.0f, 10.0f);
	light_colour_1 =    Vec3(  0.1f, 0.1f, 0.8f);
	light_colour_2 =    Vec3(  0.5f, 0.1f, 0.0f);

	number_of_lights = 2;


//	lightPos = Vec3(0.0f, 0.0f, 0.0f);

	return true;
}

void Scene3::OnDestroy() {
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

	lEye->GetMesh()->OnDestroy();
	delete lEye->GetMesh();
	delete lEye->GetTexture();
	lEye->OnDestroy();
	delete lEye;
	
	rEye->GetMesh()->OnDestroy();
	delete rEye->GetMesh();
	delete rEye->GetTexture();
	rEye->OnDestroy();
	delete rEye;


	//skull->OnDestroy();
	//delete skull;

	//skullMesh->OnDestroy();
	//delete skullMesh;


	shader->OnDestroy();
	delete shader;

	//skullTexture->~Texture();


	//moonTexture->~Texture();
	//delete moonTexture;

}

void Scene3::HandleEvents(const SDL_Event &sdlEvent) {
	//trackball->HandleEvents(sdlEvent);
	//skull->SetModelMatrix(trackball->getMatrix4());
	camera->HandleEvents(sdlEvent);
	lEye->SetModelMatrix(
						MMath::translate(Vec3(-0.6f, 0.2f, 0.3f)) *
						MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f)) * 
						//trackball->getMatrix4() * 
						MMath::scale(Vec3(0.3f, 0.3f, 0.3f)));

	
	
	
	
	rEye->SetModelMatrix(
						MMath::translate(Vec3(0.6f, 0.2f, 0.3f)) *
						MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f)) * 
					//	trackball->getMatrix4() * 
						MMath::scale(Vec3(0.3f, 0.3f, 0.3f)));

	
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

void Scene3::Update(const float deltaTime) {
	
	static float total_time = 0.0f;
	total_time += deltaTime;

				  
}

void Scene3::Render() const {
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Draw the camera(skybox)
	camera->Render();
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_CULL_FACE);


	//Throws away images of object
	//Culling means to kill
	//Killing the back face , not being calculated 
	//glFrontFace(GL_CCW);

	/// Clear the screen





	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->GetViewMatrix() );


	glUniform3fv(shader->GetUniformID("lightPos0"), 1, lightPos0);
	glUniform3fv(shader->GetUniformID("lightPos1"), 1, lightPos1);

	glUniform3fv(shader->GetUniformID("light_colour_1"), 1, light_colour_1);
	glUniform3fv(shader->GetUniformID("light_colour_2"), 1, light_colour_2);



	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, skull->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, skull->GetTexture()->getTextureID());
	//glBindTexture(GL_TEXTURE_2D, moonTexture->getTextureID());
	//mesh->Render(GL_LINES);
	skull->GetMesh()->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);


	//glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, lEye->GetModelMatrix());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, skull->GetModelMatrix() * lEye->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, lEye->GetTexture()->getTextureID());
	lEye->GetMesh()->Render(GL_TRIANGLES);

	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, skull->GetModelMatrix() * rEye->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, rEye->GetTexture()->getTextureID());
	rEye->GetMesh()->Render(GL_TRIANGLES);
	
	
	
	glBindTexture(GL_TEXTURE_2D, 0);



	glUseProgram(0);
}



	
