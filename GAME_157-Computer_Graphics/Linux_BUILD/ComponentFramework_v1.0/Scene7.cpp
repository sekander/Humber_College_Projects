#include <GL/glew.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "Debug.h"
#include "Scene7.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

Scene7::Scene7():shader(nullptr),
				 skull(nullptr),
				 skullMesh(nullptr),
				 skullTexture(nullptr),
				 x_rotation_angle(0.f),
				 y_rotation_angle(0.f)

{
	//shader = nullptr;
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene7::~Scene7() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
}

bool Scene7::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
	skull = new Actor(nullptr);
	skull->OnCreate();

	//mesh = new Mesh(nullptr, "meshes/Sphere.obj");
	//mesh = new Mesh(nullptr, "meshes/Mario.obj");
	skullMesh = new Mesh(nullptr, "meshes/Skull.obj");
	skullMesh->OnCreate();

	//shader = new Shader(nullptr, "shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	//shader = new Shader(nullptr, "shaders/phongVert.glsl", "shaders/phongFrag.glsl");
	//shader = new Shader(nullptr, "shaders/mult_texphongVert.glsl", "shaders/mult_texphongFrag.glsl");
	//shader = new Shader(nullptr, "shaders/bk_Vert.glsl", "shaders/bk_Frag.glsl");
	shader = new Shader(nullptr, "shaders/toonVert.glsl", "shaders/toonFrag.glsl");
	shader->OnCreate();

	skullTexture = new Texture();
	//texture->LoadImage("textures/mario_main.png");
	skullTexture->LoadImage("textures/skull_texture.jpg");
	//skullTexture->LoadImage("textures/earthclouds.jpg");
	//moonTexture = new Texture();
	//moonTexture->LoadImage("textures/moon.jpg");
	
	//Clipping pane 100
	projectionMatrix = MMath::perspective(45.0f, 16.0f / 9.0f, 0.5, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.f, 0.f, 10.f), Vec3(0.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f));

	MVP = skullModelMatrix * viewMatrix;

	normalMatrix = MMath::transpose(MMath::inverse(MVP));

//	number_of_lights = MAX_NUMBER_OF_LIGHTS;
	
	//modelMatrix.loadIdentity();
	//lightPos = Vec3(10.0f, -10.f, 0.f);
	//light.light_position = Vec3(0.0f, 0.0f, 0.0f);

	lightPos = Vec3(10.0f, 0.0f, 0.0f);

	//light.light_colour = Vec3(  0.6f, 0.1f, 0.1f);
 
	//lightPos0 = Vec3( 20.0f, 0.0f, 10.0f);
	//lightPos1 = Vec3(-20.0f, 0.0f, 10.0f);
	light_colour_1 =    Vec3(  0.6f, 0.6f, 0.1f);
	number_of_lights = 2;
	light_positons[0] = Vec3(10.0f, 0.0f, 10.0f);
	light_positons[1] = Vec3(-10.0f, 0.0f, 0.0f);
	light_colours[0] =  Vec3(  0.6f, 0.0f, 0.0f);
	light_colours[1] =  Vec3(  0.0f, 0.0f, 0.6f);
	//light_colour_2 =    Vec3(  0.1f, 0.6f, 0.1f);

	arrayOfInts[0] = 1;
	arrayOfInts[1] = 2;
	arrayOfInts[2] = 14;
	arrayOfInts[3] = 15;
	arrayOfInts[4] = 9;


	return true;
}

void Scene7::OnDestroy() {
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
	skull->OnDestroy();
	delete skull;

	skullMesh->OnDestroy();
	delete skullMesh;


	shader->OnDestroy();
	delete shader;

	skullTexture->~Texture();
	delete skullTexture;

	//moonTexture->~Texture();
	//delete moonTexture;

}

void Scene7::HandleEvents(const SDL_Event &sdlEvent) {
	switch( sdlEvent.type ) {
    case SDL_KEYDOWN:
		if(sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
		{
			//y_rotation_angle -= 5.0f; 
			//skullModelMatrix = MMath::rotate(y_rotation_angle, Vec3(0.0f, 1.0f, 0.0f));	
			skullModelMatrix *= MMath::rotate(+5.0f, Vec3(0.0f, 1.0f, 0.0f));	
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			//y_rotation_angle += 5.0f; 
			//skullModelMatrix = MMath::rotate(y_rotation_angle, Vec3(0.0f, 1.0f, 0.0f));	
			skullModelMatrix *= MMath::rotate(-5.0f, Vec3(0.0f, 1.0f, 0.0f));	
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
		{
			//x_rotation_angle += 5.0f; 
			//skullModelMatrix = MMath::rotate(x_rotation_angle, Vec3(1.0f, 0.0f, 0.0f));	
			skullModelMatrix *= MMath::rotate(+5.0f, Vec3(1.0f, 0.0f, 0.0f));	
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
		{
			//x_rotation_angle -= 5.0f; 
			//skullModelMatrix = MMath::rotate(x_rotation_angle, Vec3(1.0f, 0.0f, 0.0f));	
			skullModelMatrix *= MMath::rotate(-5.0f, Vec3(1.0f, 0.0f, 0.0f));	
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

void Scene7::Update(const float deltaTime) {
	
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

void Scene7::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); 
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	//glUniformMatrix4fv(shader->GetUniformID("normalMatrix"), 1, GL_FALSE, normalMatrix);
	//glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);



	//gUniform3fv(shader->GetUniformID("lightPos0"), 1, light.light_position);
	//glUniform3fv(shader->GetUniformID("light_colour_1"), 1, light.light_colour);

	//glUniform1i(shader->GetUniformID("number_of_lights"), number_of_lights);
	//glUniform2iv(shader->GetUniformID("arrayOfInts"), 5, arrayOfInts);
	//glUniform3fv()
	//glUniform3fv(shader->GetUniformID("light_positons"), 1, lightPos0);
	//glUniform3fv(shader->GetUniformID("light_colours"), 1, light_colour_1);

	
	//glUniform3fv(shader->GetUniformID("lightPos0"), 1, lightPos);
	//glUniform3fv(shader->GetUniformID("light_colour_1"), 1, light_colour_1);

	//glUniform3fv(shader->GetUniformID("lightPos0"), 1, (const GLfloat*)light_positons);
	//glUniform3fv(shader->GetUniformID("light_colours"), 2, *light_colours);
//	for(int i = 0; i < number_of_lights; i++){
		//glUniform3fv(shader->GetUniformID("lightPos0"), 1,  *light_positons);
		//glUniform3fv(shader->GetUniformID("light_colour_1"), 1, light_colours[0]);
//		if(i < 1){
//			glUniform3fv(shader->GetUniformID("lightPos1"), 1, light_positons[1]);
//			glUniform3fv(shader->GetUniformID("light_colour_2"), 1, light_colours[1]);
//		}

///	}


	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, skullModelMatrix);
	glBindTexture(GL_TEXTURE_2D, skullTexture->getTextureID());




	//glBindTexture(GL_TEXTURE_2D, moonTexture->getTextureID());
	//mesh->Render(GL_LINES);
	skullMesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);
/*
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, moonModelMatri);
	glBindTexture(GL_TEXTURE_2D, moonTexture->getTextureID());
	mesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);
*/


	glUseProgram(0);
}



	
