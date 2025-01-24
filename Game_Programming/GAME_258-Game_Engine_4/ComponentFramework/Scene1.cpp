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

#include "Scene1.h"


#include <memory>
#include <iostream>


Scene1::Scene1() {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene1::~Scene1() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);

}

bool Scene1::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);

	xml = new LoadingGameObjects();
	xml->ReadManifestScene1("xml/Manifest.xml");



	camera = std::make_shared<CameraActor>(nullptr);
	//camera = new CameraActor(nullptr);
	//camera->AddComponent<TransformComponent>(nullptr, Vec3(0.0f, 0.0f, -20.0f), Quaternion());
	camera->AddComponent<TransformComponent>(nullptr, Vec3(0.0f, 0.0f, -15.0f), Quaternion());

	camera->OnCreate();
	camera->GetProjectionMatrix().print("ProjectionMatrix");
	camera->GetViewMatrix().print("ViewMatrix");

	light = std::make_shared<LightActor>(nullptr, LightStyle::DirectionLight, Vec3(0.0f, 0.0f, -10.0f), Vec4(0.6f, 0.5f, 0.5f, 0.0f), 5.0f);
	//light = new LightActor(nullptr, LightStyle::DirectionLight, Vec3(0.0f, 0.0f, -10.0f), Vec4(0.6f, 0.5f, 0.5f, 0.0f), 5.0f);
	light->OnCreate();

	gameboard = std::make_shared<Actor>(nullptr);
	//gameboard = new Actor(nullptr);
	//Quaternion(0.85f, -0.5f, 0.0f, 0.0f)
	gameboard->AddComponent<TransformComponent>(nullptr, Vec3(0.0f, 0.0f, 0.0f), Quaternion(0.85f, -0.5f, 0.0f, 0.0f));
	gameboard->AddComponent<MeshComponent>(nullptr, "meshes/Plane.obj");
	gameboard->AddComponent<MaterialComponent>(nullptr, "textures/8x8_checkered_board.png");
	gameboard->AddComponent<ShaderComponent>(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
	gameboard->OnCreate();
	gameboard->ListComponents();


	float x_start_position_checker = -5.5;

	float xpos_checker = 0.0f;
	float ypos_checker = -4.3;

	//checker = std::make_shared<Actor>(gameboard);
	//checker->AddComponent<TransformComponent>(nullptr, Vec3(x_start_position_checker + xpos_checker, ypos_checker, 0.0f), Quaternion(), Vec3(0.15f, 0.15f, 0.15f));
	//checker->AddComponent<MeshComponent>(nullptr, "meshes/CheckerPiece.obj");
	//checker->AddComponent<MaterialComponent>(nullptr, "textures/redCheckerPiece.png");
	//checker->AddComponent<ShaderComponent>(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
	//checker->OnCreate();


	


	
	//Loop through 32 checker pieces
	for (int i = 0; i < 32; i++)
	{
		//Checker piece displacment
		xpos_checker += 1.2;

		//Second row
		if (i > 7) {
			ypos_checker = -3.3;
			x_start_position_checker = -15.0f;
		}

		//Black checkers
		if (i > 15)
		{
			ypos_checker = 4.3;
			x_start_position_checker = -25.0f;

		}

		//Second row of black checkers
		if (i > 23)
		{

			ypos_checker = 3.3;
			x_start_position_checker = -34.0f;
		}

		//Actor* checker_piece = new Actor(gameboard);
		Ref<Actor> checker_piece = std::make_shared<Actor>(nullptr);


		checker_piece->AddComponent<TransformComponent>(nullptr, Vec3(x_start_position_checker + xpos_checker, ypos_checker, 0.0f), Quaternion(), Vec3(0.15f, 0.15f, 0.15f));
		checker_piece->AddComponent<MeshComponent>(nullptr, "meshes/CheckerPiece.obj");

		if(i < 16)
			checker_piece->AddComponent<MaterialComponent>(nullptr, "textures/redCheckerPiece.png");
		else
			checker_piece->AddComponent<MaterialComponent>(nullptr, "textures/blackCheckerPiece.png");

		checker_piece->AddComponent<ShaderComponent>(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
		checker_piece->OnCreate();

		checker_pieces.push_back(checker_piece);

	}
	

	
	


	actors_map.insert(std::make_pair("gameboard", gameboard));
	actors_map.insert(std::make_pair("light", light));
	actors_map.insert(std::make_pair("camera", camera));


	return true;
}

void Scene1::OnDestroy() {
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
	//if(camera) delete camera;

	//if(gameboard) delete gameboard;

	delete xml;

}

void Scene1::HandleEvents(const SDL_Event& sdlEvent) {
	//std::unordered_map<std::string, Ref<Actor>>::iterator it = actors_map.begin();
	
	/*
	while (it != actors_map.end())
	{
		std::cout << it->first << std::endl;


		if (it->first == "camera")
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

		if (it->first == "gameboard")
		{
			std::cout << "ITS A ME A Gameboard!!!" << std::endl;
			//auto camera = it->first;


			switch (sdlEvent.type) {
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_E) {
					Ref<TransformComponent> tc = gameboard->GetComponent<TransformComponent>();

					tc->SetTransform(tc->GetPosition(),
						tc->GetQuaternion() * QMath::angleAxisRotation(-2.0f, Vec3(0.0f, 1.0f, 0.0f)));

				}
				else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_Q) {
					Ref<TransformComponent> tc = gameboard->GetComponent<TransformComponent>();

					tc->SetTransform(tc->GetPosition(),
						tc->GetQuaternion() * QMath::angleAxisRotation(2.0f, Vec3(0.0f, 1.0f, 0.0f)));

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
	*/
}


void Scene1::Update(const float deltaTime) {
	//mario->GetComponent<MeshComponent>()

	static float total_time = 0.0f;
	total_time += deltaTime;


	/*
	angle = 0.5f * total_time;



		mario->GetComponent<TransformComponent>()->
		SetTransform(Vec3(0.f, 0.f, 15.f),
			Quaternion(
				cos( angle/ 2),
				sin(angle / 2) * 0,
				sin(angle / 2) ,
				sin(angle / 2) * 0
		)


		);
		*/

		//QMath::rotate(Vec3(0.0f, 0.0f, 0.0f), )


	//	QMath::angleAxisRotation(90, Vec3(0.0f, 0.0f, 0.0f));
}

void Scene1::Render() const {
	glEnable(GL_DEPTH_TEST);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





	

	Ref<ShaderComponent> shader = gameboard->GetComponent<ShaderComponent>();
	Ref<MeshComponent> mesh = gameboard->GetComponent<MeshComponent>();
	Ref<TransformComponent> transform = gameboard->GetComponent<TransformComponent>();
	Ref<MaterialComponent> texture = gameboard->GetComponent<MaterialComponent>();

	if (shader == nullptr || mesh == nullptr || transform == nullptr) {
		return;
	}

	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->GetViewMatrix());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, transform->GetTransformMatrix());
	glBindBuffer(GL_UNIFORM_BUFFER, camera->GetMatriciesID());
	glBindBuffer(GL_UNIFORM_BUFFER, light->GetLightID());
	//glUniform3fv(shader->GetUniformID("lightPos"), 1, );
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	mesh->Render(GL_TRIANGLES);





	
	for (auto checker : checker_pieces)
	{
		shader = checker->GetComponent<ShaderComponent>();
		mesh = checker->GetComponent<MeshComponent>();
		transform = checker->GetComponent<TransformComponent>();
		texture = checker->GetComponent<MaterialComponent>();

		Matrix4 mmc = gameboard->GetModelMatrix() * checker->GetModelMatrix();


		glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, mmc);
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
		mesh->Render(GL_TRIANGLES);

	}
	
	























	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}




