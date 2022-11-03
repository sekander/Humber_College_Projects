#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene2.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Trackball.h"
#include "Camera.h"


Scene2::Scene2():shader(nullptr),
				 skull(nullptr),
				 skullMesh(nullptr),
				 skullTexture(nullptr),
				 lEye(nullptr),
				 rEye(nullptr),
				 x_rotation_angle(0.f),
				 y_rotation_angle(0.f)

{
	//shader = nullptr;
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
	trackball = new Trackball();
}

Scene2::~Scene2() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
	delete trackball;
}

bool Scene2::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
	camera = new Camera();


	camera->LoadSkybox(
		"textures/posx.jpg", "textures/posy.jpg", "textures/posz.jpg",
		"textures/negx.jpg", "textures/negy.jpg", "textures/negz.jpg"

	);


	camera->OnCreate();




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




	//mesh = new Mesh(nullptr, "meshes/Sphere.obj");
	//mesh = new Mesh(nullptr, "meshes/Mario.obj");
	//skullMesh = new Mesh(nullptr, "meshes/Skull.obj");
	//skullMesh->OnCreate();

	//shader = new Shader(nullptr, "shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	//shader = new Shader(nullptr, "shaders/phongVert.glsl", "shaders/phongFrag.glsl");
	shader = new Shader(nullptr, "shaders/tex_phongVert.glsl", "shaders/tex_phongFrag.glsl");
	shader->OnCreate();

	skull->SetTexture(new Texture());
	skull->GetTexture()->LoadImage("textures/skull_texture.jpg");
	//skullTexture = new Texture();
	//texture->LoadImage("textures/mario_main.png");
	//skullTexture->LoadImage("textures/skull_texture.jpg");
	//skullTexture->LoadImage("textures/earthclouds.jpg");
	//moonTexture = new Texture();
	//moonTexture->LoadImage("textures/moon.jpg");
	
	//Clipping pane 100
	projectionMatrix = MMath::perspective(45.0f, 16.0f / 9.0f, 0.5, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.f, 0.f, 10.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f));
	
	
	//modelMatrix.loadIdentity();
	//lightPos = Vec3(10.0f, -10.f, 0.f);
	lightPos = Vec3(0.0f, 0.0f, 0.0f);

	return true;
}

void Scene2::OnDestroy() {
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

void Scene2::HandleEvents(const SDL_Event &sdlEvent) {
	camera->HandleEvents(sdlEvent);



	trackball->HandleEvents(sdlEvent);
	//skull->SetModelMatrix(trackball->getMatrix4());
	lEye->SetModelMatrix(
						MMath::translate(Vec3(-0.6f, 0.2f, 0.3f)) *
						MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f)) * 
						trackball->getMatrix4() * 
						MMath::scale(Vec3(0.3f, 0.3f, 0.3f)));

	
	
	
	
	rEye->SetModelMatrix(
						MMath::translate(Vec3(0.6f, 0.2f, 0.3f)) *
						MMath::rotate(-90.0f, Vec3(0.0f, 1.0f, 0.0f)) * 
						trackball->getMatrix4() * 
						MMath::scale(Vec3(0.3f, 0.3f, 0.3f)));

	
	switch( sdlEvent.type ) {
    case SDL_KEYDOWN:
		if(sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
		{
			//y_rotation_angle -= 5.0f; 
			//skullModelMatrix = MMath::rotate(y_rotation_angle, Vec3(0.0f, 1.0f, 0.0f));	
			//skullModelMatrix *= MMath::rotate(+5.0f, Vec3(0.0f, 1.0f, 0.0f));
			//Matrix4 mm = skull->GetModelMatrix();	
			//mm *= MMath::rotate(+5.0f, Vec3(0.0f, 1.0f, 0.0f));
			skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::rotate(+5.0f, Vec3(0.0f, 1.0f, 0.0f)));

			//skull->GetModelMatrix();

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			//y_rotation_angle += 5.0f; 
			//skullModelMatrix = MMath::rotate(y_rotation_angle, Vec3(0.0f, 1.0f, 0.0f));	
			//skullModelMatrix *= MMath::rotate(-5.0f, Vec3(0.0f, 1.0f, 0.0f));	
			skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::rotate(-5.0f, Vec3(0.0f, 1.0f, 0.0f)));

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
		{
			//x_rotation_angle += 5.0f; 
			//skullModelMatrix = MMath::rotate(x_rotation_angle, Vec3(1.0f, 0.0f, 0.0f));	
			//skullModelMatrix *= MMath::rotate(+5.0f, Vec3(1.0f, 0.0f, 0.0f));	
			skull->SetModelMatrix(skull->GetModelMatrix() *= MMath::rotate(+5.0f, Vec3(1.0f, 0.0f, 0.0f)));

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
		{
			//x_rotation_angle -= 5.0f; 
			//skullModelMatrix = MMath::rotate(x_rotation_angle, Vec3(1.0f, 0.0f, 0.0f));	
			//skullModelMatrix *= MMath::rotate(-5.0f, Vec3(1.0f, 0.0f, 0.0f));	
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

void Scene2::Update(const float deltaTime) {
	
	static float total_time = 0.0f;
	total_time += deltaTime;

	//modelMatrix = MMath::rotate(total_time * 50.0f , Vec3(0.0f, 1.0f, 0.0f));
	
	//skullModelMatrix = MMath::rotate(total_time * 30.0f , Vec3(0.0f, 1.0f, 0.0f));
				  //MMath::rotate(-90.0f, Vec3(1.0f, 0.0f, 0.0f));

/*
	moonModelMatrix = MMath::rotate(total_time * 10.0f , Vec3(0.0f, 1.0f, 0.0f)) *
					  MMath::translate(Vec3(6.0f, 0.0f, 0.f)) * 
					  MMath::rotate(total_time * 50.0f , Vec3(0.0f, 1.0f, 0.0f)) *
					  MMath::scale(Vec3(0.27f, 0.27f, 0.27f)) *
				  	  MMath::rotate(-90.0f, Vec3(1.0f, 0.0f, 0.0f));
*/					  
}

void Scene2::Render() const {

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Draw the camera(skybox)
	camera->Render();

	/// Clear the screen
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); 
	glUseProgram(shader->GetProgram());
	//glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	//glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->GetViewMatrix() );

	glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);

	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, skull->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, skull->GetTexture()->getTextureID());
	//glBindTexture(GL_TEXTURE_2D, moonTexture->getTextureID());
	//mesh->Render(GL_LINES);
	skull->GetMesh()->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);
/*
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, moonModelMatri);
	glBindTexture(GL_TEXTURE_2D, moonTexture->getTextureID());
	mesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);
*/


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



	
