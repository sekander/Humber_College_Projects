#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "MMath.h"
#include "Debug.h"
#include "CameraActor.h"
#include "LightActor.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "ShaderComponent.h"
#include "MaterialComponent.h"

#include "Scene0.h"

#include <memory>
#include <iostream>

Scene0::Scene0() {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);

}

bool Scene0::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
	//camera = new CameraActor(nullptr);
	//camera->AddComponent<TransformComponent>(nullptr, Vec3(0.0f, 0.0f, -20.0f), Quaternion());

	xml = new LoadingGameObjects();

	xml->ReadManifestScene0("xml/Manifest.xml");

	camera = std::make_shared<CameraActor>(nullptr);



	camera->AddComponent<TransformComponent>(nullptr, Vec3(0.0f, 0.0f, -20.0f), Quaternion());



	camera->OnCreate();
	camera->GetProjectionMatrix().print("ProjectionMatrix");
	camera->GetViewMatrix().print("ViewMatrix");


	auto colour = xml->return_light_color();

	light = std::make_shared<LightActor>(nullptr, LightStyle::DirectionLight, 
												  Vec3(10.0f, 2.0f, -2.0f), 
												  colour);
												  //Vec4(0.6f, 0.1f, 0.0f, 0.0f));

	light->OnCreate();


	/*
	//mario = new Actor(nullptr);
	mario = std::make_shared<Actor>(nullptr);
	mario->AddComponent<TransformComponent>(nullptr, Vec3(0.0f, 0.0f, 10.0f), Quaternion());
	mario->AddComponent<MeshComponent>(nullptr, "meshes/Mario.obj");
	mario->AddComponent<MaterialComponent>(nullptr, "textures/mario_main.png");
	//mario->AddComponent<ShaderComponent>(nullptr, "shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	mario->AddComponent<ShaderComponent>(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
	mario->OnCreate();
	mario->ListComponents();

	//hammer = new Actor(nullptr);
	hammer = std::make_shared<Actor>(mario.get());
	hammer->AddComponent<TransformComponent>(nullptr, Vec3(-1.0f, 0.0f, 15.0f), QMath::angleAxisRotation(-90.0f, Vec3(1.0f, 0.0f, 0.0f)));
	hammer->AddComponent<MeshComponent>(nullptr, "meshes/Hammer.obj");
	hammer->AddComponent<MaterialComponent>(nullptr, "textures/hammer_BaseColor.png");
	//mario->AddComponent<ShaderComponent>(nullptr, "shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	hammer->AddComponent<ShaderComponent>(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
	hammer->OnCreate();



	mario->GetComponent<TransformComponent>()->
		SetTransform(Vec3(0.f, 0.f, 15.f), Quaternion(0.0f, Vec3(0.0f, 1.0f, 0.0f)));
	*/

	auto mesh_maps = xml->ReturnMap();
	std::unordered_map<std::string, Ref<Actor>>::iterator mesh_it = mesh_maps.begin();
	while (mesh_it != mesh_maps.end())
	{
		std::cout << "Change orienation :: " << mesh_it->first << std::endl;

		//if (mesh_it->first == "Mario")
		//{

		auto mesh = mesh_it->second;

		mesh->GetComponent<TransformComponent>()->
			SetTransform(mesh->GetComponent<TransformComponent>()->GetPosition(),
				Quaternion(0.0f, Vec3(0.0f, 1.0f, 0.0f)));

		mesh_it++;
	}

	//actors.push_back(mario);
	//actors.push_back(hammer);
	//actors.push_back(light);

	//actors_map.insert(std::make_pair("mario", mario));
	//actors_map.insert(std::make_pair("hammer", hammer));
	actors_map.insert(std::make_pair("light", light));
	actors_map.insert(std::make_pair("camera", camera));

	return true;
}

void Scene0::OnDestroy() {
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
	//if(camera) delete camera;

	//if(mario) delete mario;

	delete xml;
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent) {

	std::unordered_map<std::string, Ref<Actor>>::iterator it = actors_map.begin();
	while (it != actors_map.end())
	{
		std::cout << it->first << std::endl;


		if (it->first == "camera" )
		{
			std::cout << "ITS A ME A CAMERA!!!" << std::endl;
			//auto camera = it->second;


			switch (sdlEvent.type) {
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT) {


					camera->GetComponent<TransformComponent>()->SetTransform(
						camera->GetComponent<TransformComponent>()->GetPosition() + Vec3(-0.1f, 0.0f, 0.0f),
						camera->GetComponent<TransformComponent>()->GetQuaternion());

					//reinterpret_cast<>->UpdateViewMatrix();
					//std::dynamic_poiner_cast<Ref<CameraActor>>(camera);
					//std::dynamic_pointer_cast<Actor>();
					camera->UpdateViewMatrix();


				}
				else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT) {

					camera->GetComponent<TransformComponent>()->SetTransform(
						camera->GetComponent<TransformComponent>()->GetPosition() + Vec3(0.1f, 0.0f, 0.0f),
						camera->GetComponent<TransformComponent>()->GetQuaternion());

					//dynamic_pointer_cast<CameraActor>(camera)->UpdateViewMatrix();
					camera->UpdateViewMatrix();

				}
				else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP) {
					camera->GetComponent<TransformComponent>()->SetTransform(
						camera->GetComponent<TransformComponent>()->GetPosition() + Vec3(0.0f, 0.1f, 0.0f),
						camera->GetComponent<TransformComponent>()->GetQuaternion());

					camera->UpdateViewMatrix();

				}
				else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN) {
					camera->GetComponent<TransformComponent>()->SetTransform(
						camera->GetComponent<TransformComponent>()->GetPosition() + Vec3(0.0f, -0.1f, 0.0f),
						camera->GetComponent<TransformComponent>()->GetQuaternion());

					camera->UpdateViewMatrix();

				}
				else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_Z) {
					camera->GetComponent<TransformComponent>()->SetTransform(
						camera->GetComponent<TransformComponent>()->GetPosition() + Vec3(0.0f, 0.0f, 0.1f),
						camera->GetComponent<TransformComponent>()->GetQuaternion());

					camera->UpdateViewMatrix();

				}
				else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_X) {
					camera->GetComponent<TransformComponent>()->SetTransform(
						camera->GetComponent<TransformComponent>()->GetPosition() + Vec3(0.0f, 0.0f, -0.1f),
						camera->GetComponent<TransformComponent>()->GetQuaternion());

					camera->UpdateViewMatrix();

				}
				else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE) {
					camera->GetComponent<TransformComponent>()->SetTransform(
						camera->GetComponent<TransformComponent>()->GetPosition(),
						QMath::angleAxisRotation(15.0f, Vec3(1.0f, 0.0f, 0.0f)));




					camera->UpdateViewMatrix();

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

	


		it++;
	}



}

float angle;

void Scene0::Update(const float deltaTime) {
	//mario->GetComponent<MeshComponent>()

	static float total_time = 0.0f;
	total_time += deltaTime;

	auto mesh_maps = xml->ReturnMap();
	std::unordered_map<std::string, Ref<Actor>>::iterator mesh_it = mesh_maps.begin();
	while (mesh_it != mesh_maps.end())
	{
		std::cout << "Updating :: " << mesh_it->first << std::endl;

		

			auto mesh = mesh_it->second;




			angle = 0.5f * total_time;

			
			mesh->GetComponent<TransformComponent>()->
				SetTransform(mesh->GetComponent<TransformComponent>()->GetPosition(),
					//mesh->GetComponent<TransformComponent>()->GetQuaternion()

					Quaternion(
						cos(angle / 2),
						sin(angle / 2) * 0,
						sin(angle / 2),
						sin(angle / 2) * 0
					));
			
		//}

		mesh_it++;
	}

	
}

void Scene0::Render() const {
	glEnable(GL_DEPTH_TEST);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glUseProgram(shader->GetProgram());
	glBindBuffer(GL_UNIFORM_BUFFER, light->GetLightID());
	glBindBuffer(GL_UNIFORM_BUFFER, camera->GetMatriciesID());


	auto mesh_maps = xml->ReturnMap();
	std::unordered_map<std::string, Ref<Actor>>::iterator mesh_it = mesh_maps.begin();
	while (mesh_it != mesh_maps.end())
	{
		//std::cout << mesh_it->first << std::endl;
		auto actor = mesh_it->second;

		Ref<ShaderComponent> shader = actor->GetComponent<ShaderComponent>();
		Ref<MeshComponent> mesh = actor->GetComponent<MeshComponent>();
		Ref<TransformComponent> transform = actor->GetComponent<TransformComponent>();
		Ref<MaterialComponent> texture = actor->GetComponent<MaterialComponent>();

		if (shader == nullptr || mesh == nullptr || transform == nullptr) {
			return;
		}

		glUseProgram(shader->GetProgram());
		glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, transform->GetTransformMatrix());
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
		mesh->Render(GL_TRIANGLES);

		mesh_it++;
	}


	












	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}




