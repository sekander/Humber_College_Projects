#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene1.h"
#include "MMath.h"
#include "Debug.h"
#include "CameraActor.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "ShaderComponent.h"
#include "MaterialComponent.h"
#include "LightActor.h"
#include "QMath.h"
#include <algorithm>
#include "AssetManager.h"

using namespace MATH;

// we can be fancy and set the camera using the : and {}
Scene1::Scene1() {
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
}

Scene1::~Scene1() {
	Debug::Info("Deleted Scene1: ", __FILE__, __LINE__);

}

bool Scene1::OnCreate() {
	Debug::Info("Loading assets Scene1: ", __FILE__, __LINE__);
	// Let's set up a camera
	// I'll skip a parent for now.  Eventually we'll parent everything to the scene
	// parents will go with the scene graph topic happening later in course
	
	// 2022-04-01
	// We don't need to say new anymore! 
	camera = std::make_shared<CameraActor>(nullptr);
	
	// we want the camera to have a displacement and orientation don't we? 
	// let's add a transform component. need to pass the appropriate arguments
	// rub it in looAt's nose by doing a negative z
	// don't need to put scale in as we have that as default
	camera->AddComponent<TransformComponent>(nullptr, Vec3(-1.0f, 0.0f, -13.0f), QMath::angleAxisRotation(0, Vec3(1.0f, 0.0f, 0.0f)));
	// now use that transform to build the camera matrices using OnCreate
	camera->OnCreate();
	// the projection matrix distorts 4D space
	// get a cube, crush it, and make a truncated pyramid
	camera->GetProjectionMatrix().print("Projection");
	camera->GetViewMatrix().print("View");
	
	// 2022-04-02
	// Trying to get Scott's asset manager working here
	AssetManager assetManager;
	Ref<ShaderComponent> shader = assetManager.GetComponent<ShaderComponent>("Shader");
	Ref<MeshComponent> checkerMesh = assetManager.GetComponent<MeshComponent>("CheckerMesh");
	// lets build mario. No parent until we get the scene graph up and running
	//gameboard = new Actor(nullptr);
	gameboard = std::make_shared<Actor>(nullptr);
	// mario needs a position, and orientation right!?
	gameboard->AddComponent<TransformComponent>(nullptr, Vec3(0.0f, -1.0f, 0.0f), QMath::angleAxisRotation(-90, Vec3(1.0f, 0.0f, 0.0f)));
	// Give Mario an initial velocity

	gameboard->OnCreate(); // we'll put the asset in OnCreate
	
	// 2022-02-11 Umer trying to get Mario on screen (Scott's h/w)
	gameboard->AddComponent<MeshComponent>(nullptr, "meshes/Plane.obj");
	// Now create the mesh component. Need to get it from the actor to use it's OnCreate()
	gameboard->GetComponent<MeshComponent>()->OnCreate();
	// Scott made up the .glsl file ending
	//mario->AddComponent<ShaderComponent>(nullptr, "shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");

	// 2022-03-22 Umer trying a shared component manager
	//std::shared_ptr<Component> shader (new ShaderComponent(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl"));
	//sharedComponents.push_back(shader);


	// 2022-02-12 Umer trying to get light & textures working (Scott's h/w)
	//gameboard->AddComponent<ShaderComponent>(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
	// 2022-04-02
	// Using a shared asset now from our asset manager!
	gameboard->AddComponent<ShaderComponent>(shader);
	gameboard->AddComponent<MaterialComponent>(nullptr, "textures/8x8_checkered_board.png");
	// The OnCreates for the Shader and Material above are called in the Actor's AddComponent
	light = std::make_shared<LightActor>(nullptr, LightStyle::DirectionLight, Vec3(-2.0f, 2.0f, -10.0f), Vec4(0.9f, 0.9f, 0.9f, 0.0f));
	light->OnCreate();

	checker_red = std::make_shared <Actor>(nullptr);
	checker_red->AddComponent<TransformComponent>(nullptr, Vec3(3.0f, 5.0f, 0.0f), QMath::angleAxisRotation(0, Vec3(1.0f, 0.0f, 0.0f)), Vec3(0.15f, 0.15f, 0.15f));
	checker_red->AddComponent<MeshComponent>(checkerMesh);
	checker_red->AddComponent<ShaderComponent>(shader);
	checker_red->AddComponent<MaterialComponent>(nullptr, "textures/redCheckerPiece.png");
	checker_red->OnCreate(); // this runs all the component OnCreates

	checker_black = std::make_shared <Actor>(nullptr);
	checker_black->AddComponent<TransformComponent>(nullptr, Vec3(5.0f, -5.0f, 0.0f), QMath::angleAxisRotation(0, Vec3(1.0f, 0.0f, 0.0f)), Vec3(0.15f, 0.15f, 0.15f));
	checker_black->AddComponent<MeshComponent>(checkerMesh);
	checker_black->AddComponent<ShaderComponent>(shader);
	checker_black->AddComponent<MaterialComponent>(nullptr, "textures/blackCheckerPiece.png");
	checker_black->OnCreate(); // this runs all the component OnCreates

	checker_white = std::make_shared <Actor>(nullptr);
	checker_white->AddComponent<TransformComponent>(nullptr, Vec3(0.0f, 0.0f, 0.0f), QMath::angleAxisRotation(0, Vec3(1.0f, 0.0f, 0.0f)), Vec3(0.15f, 0.15f, 0.15f));
	checker_white->AddComponent<MeshComponent>(checkerMesh);
	checker_white->AddComponent<ShaderComponent>(shader);
	checker_white->AddComponent<MaterialComponent>(nullptr, "textures/whiteCheckerPiece.png");
	checker_white->OnCreate(); // this runs all the component OnCreates

	anchorPoint.set(0.8f, 5.4f, 0.0f);
	rodLength1 = VMath::mag(checker_red->GetComponent<TransformComponent>()->pos - anchorPoint);
	rodLength2 = VMath::mag(checker_red->GetComponent<TransformComponent>()->pos - checker_black->GetComponent<TransformComponent>()->pos);
	rodLength3 = VMath::mag(checker_black->GetComponent<TransformComponent>()->pos - checker_white->GetComponent<TransformComponent>()->pos);

	return true;
}

void Scene1::OnDestroy() {

}
void Scene1::HandleEvents(const SDL_Event &sdlEvent) {
	switch( sdlEvent.type ) {
    case SDL_KEYDOWN:
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT) {
			Vec3 displacement(-1.0f, 0.0f, 0.0f);
			camera->GetComponent <TransformComponent>()->Translate(displacement);
			camera->UpdateViewMatrix();
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
			Vec3 displacement(1.0f, 0.0f, 0.0f);
			camera->GetComponent <TransformComponent>()->Translate(displacement);
			camera->UpdateViewMatrix();
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP) {
			Vec3 displacement(0.0f, 0.0f, -1.0f);
			camera->GetComponent <TransformComponent>()->Translate(displacement);
			camera->UpdateViewMatrix();
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN) {
			Vec3 displacement(0.0f, 0.0f, 1.0f);
			camera->GetComponent <TransformComponent>()->Translate(displacement);
			camera->UpdateViewMatrix();
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_E) {
			Ref<TransformComponent> tc = camera->GetComponent <TransformComponent>();
			tc->SetTransform(tc->GetPosition(), tc->GetOrientation() * QMath::angleAxisRotation(-20.0f, Vec3(0.0f, 1.0f, 0.0f)));			
			camera->UpdateViewMatrix();
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_Q) {
			Ref<TransformComponent> tc = camera->GetComponent <TransformComponent>();
			tc->SetTransform(tc->GetPosition(), tc->GetOrientation() * QMath::angleAxisRotation(20.0f, Vec3(0.0f, 1.0f, 0.0f)));			
			camera->UpdateViewMatrix();
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A) {
			// give red checker a kick to the left
			checker_red->GetComponent<TransformComponent>()->vel.set(-5.0f, 0.0f, 0.0f);
			Vec3 displacement(-0.1f, 0.0f, 0.0f);
			Ref<TransformComponent> tc = gameboard->GetComponent <TransformComponent>();
			tc->Translate(displacement);
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {
			// give red checker a kick to the right
			checker_red->GetComponent<TransformComponent>()->vel.set(5.0f, 0.0f, 0.0f);
			Vec3 displacement(0.1f, 0.0f, 0.0f);
			Ref<TransformComponent> tc = gameboard->GetComponent <TransformComponent>();
			tc->Translate(displacement);
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W) {
			// give red checker a kick forward
			checker_red->GetComponent<TransformComponent>()->vel.set(0.0f, 0.0f, 5.0f);
			Vec3 displacement(0.0f, 0.1f, 0.0f);
			Ref<TransformComponent> tc = gameboard->GetComponent <TransformComponent>();
			tc->Translate(displacement);
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S) {
			// give red checker a kick forward
			checker_red->GetComponent<TransformComponent>()->vel.set(0.0f, 0.0f, -5.0f);
			Vec3 displacement(0.0f, -0.1f, 0.0f);
			Ref<TransformComponent> tc = gameboard->GetComponent <TransformComponent>();
			tc->Translate(displacement);
		}


		break;

	case SDL_MOUSEMOTION:          
		break;

		// 2022-03-16 Umer trying to get mouse coords in world space:
	case SDL_MOUSEBUTTONDOWN:         
		if (sdlEvent.button.button == SDL_BUTTON_LEFT) {
			Vec3 mouseCoords(static_cast<float>(sdlEvent.button.x), static_cast<float>(sdlEvent.button.y), 0.0f);
			//anchorPoint = MMath::inverse(camera->GetViewMatrix() * camera->GetProjectionMatrix()) * mouseCoords;
			//anchorPoint.z = 0.0f;
			mouseCoords.print("mouse px");
			//anchorPoint.print("mouse world");
			//Vec3 anchorPointCalc = MMath::inverse(camera->GetProjectionMatrix() * camera->GetViewMatrix()) * Vec3(675.0f, 353.0f, 0.0f);
			//anchorPoint.z = 0.0f;
			//anchorPointCalc.print("anchorPointCalc");


		}

		break; 

	case SDL_MOUSEBUTTONUP:            
	break;


	default:
		break;
    }
}

void Scene1::Update(const float deltaTime) {
	// TO DO: Include mass in gravity force calc and constraint methods
	Vec3 gravityForce(0.0f, -10.0f, 0.0f);
	float dragCoeff = 0.25f;
	Vec3 dragForce_red   = checker_red->GetComponent<TransformComponent>()->vel   * (-dragCoeff);
	Vec3 dragForce_black = checker_black->GetComponent<TransformComponent>()->vel * (-dragCoeff);
	Vec3 dragForce_white = checker_white->GetComponent<TransformComponent>()->vel * (-dragCoeff);

	Vec3 netForce_red   = gravityForce + dragForce_red;
	Vec3 netForce_black = gravityForce + dragForce_black;
	Vec3 netForce_white = gravityForce + dragForce_white;

	// REFERENCE: Following Erin Catto's slides to implement a rod constraint
    // https://ubm-twvideo01.s3.amazonaws.com/o1/vault/gdc09/slides/04-GDC09_Catto_Erin_Solver.pdf
	// Step one: get a tentative velocity using applied forces
	//checker_red->GetComponent<TransformComponent>()->ApplyForce(netForce_red);
	//checker_black->GetComponent<TransformComponent>()->ApplyForce(netForce_black);
	//checker_white->GetComponent<TransformComponent>()->ApplyForce(netForce_white);

	//checker_red->GetComponent<TransformComponent>()->vel   += checker_red->GetComponent<TransformComponent>()->accel   * deltaTime;
	//checker_black->GetComponent<TransformComponent>()->vel += checker_black->GetComponent<TransformComponent>()->accel * deltaTime;
	//checker_white->GetComponent<TransformComponent>()->vel += checker_white->GetComponent<TransformComponent>()->accel * deltaTime;

	//Step two: loop over constraints to correct velocity errors
	//checker_red->GetComponent<TransformComponent>()->  SimpleRodConstraint(checker_red,   deltaTime, anchorPoint,                                            rodLength1);
	//checker_black->GetComponent<TransformComponent>()->SimpleRodConstraint(checker_black, deltaTime, checker_red->GetComponent<TransformComponent>()->pos,   rodLength2);
	//checker_white->GetComponent<TransformComponent>()->SimpleRodConstraint(checker_white, deltaTime, checker_black->GetComponent<TransformComponent>()->pos, rodLength3);

	// 2022-03-21 Umer trying a soft constraint
	// rod is now bouncy
	//checker_red->GetComponent<TransformComponent>()->SoftConstraint(checker_red, deltaTime, anchorPoint, rodLength1);
	//checker_black->GetComponent<TransformComponent>()->SoftConstraint(checker_black, deltaTime, checker_red->GetComponent<TransformComponent>()->pos,   rodLength2);
	//checker_white->GetComponent<TransformComponent>()->SoftConstraint(checker_white, deltaTime, checker_black->GetComponent<TransformComponent>()->pos, rodLength3);

	// 2022-03-27 Umer trying a figure eight constraint
	checker_red->GetComponent<TransformComponent>()->LemniscateOfGeronoConstraint(checker_red, deltaTime, 5.0f);
	checker_black->GetComponent<TransformComponent>()->LemniscateOfGeronoConstraint(checker_black, deltaTime, 5.0f);

	// Step three: update position using corrected velocities
	checker_red->GetComponent<TransformComponent>()->pos   += checker_red->GetComponent<TransformComponent>()->vel   * deltaTime;
	checker_black->GetComponent<TransformComponent>()->pos += checker_black->GetComponent<TransformComponent>()->vel * deltaTime;
	checker_white->GetComponent<TransformComponent>()->pos += checker_white->GetComponent<TransformComponent>()->vel * deltaTime;

	//// For the figure eight orbit, keep the velocity magnitude constant
	float speed = 5.0f;
	if (VMath::mag(checker_red->GetComponent<TransformComponent>()->vel) > 0.001f) {
		Vec3 velocityNormalized = VMath::normalize(checker_red->GetComponent<TransformComponent>()->vel);
		Vec3 velocity = velocityNormalized * speed;
		checker_red->GetComponent<TransformComponent>()->vel = velocity;
	}
}


void Scene1::Render() const {
	// need to turn on the depth test, otherwise the z-buffer is not on
	glEnable(GL_DEPTH_TEST);

	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Can do this in any order, but lets start by getting the shader component
	Ref<ShaderComponent>    shader    = gameboard->GetComponent<ShaderComponent>();
	Ref<MeshComponent>      mesh      = gameboard->GetComponent<MeshComponent>();
	Ref<TransformComponent> transform = gameboard->GetComponent<TransformComponent>();
	Ref<MaterialComponent>  material  = gameboard->GetComponent<MaterialComponent>();
	// 2022-02-11 Scott says check for nullptrs today!
	if (shader == nullptr || mesh == nullptr || transform == nullptr) {
		return;
	}

	glUseProgram(shader->GetProgram());
	glBindBuffer(GL_UNIFORM_BUFFER, camera->GetMatricesID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, gameboard->GetModelMatrix());
	glBindBuffer(GL_UNIFORM_BUFFER, light->GetLightID());
	glBindTexture(GL_TEXTURE_2D, material->getTextureID());
	//mesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->GetViewMatrix());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, transform->GetTransformMatrix());
	glUniform3fv(shader->GetUniformID("lightPos"), 1, light->GetPosition());
	glBindTexture(GL_TEXTURE_2D, material->getTextureID());


	glUseProgram(checker_red->GetComponent<ShaderComponent>()->GetProgram());
	glUniformMatrix4fv(checker_red->GetComponent<ShaderComponent>()->GetUniformID("modelMatrix"), 1, GL_FALSE, checker_red->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, checker_red->GetComponent<MaterialComponent>()->getTextureID());
	checker_red->GetComponent<MeshComponent>()->Render(GL_TRIANGLES);

	glUseProgram(checker_black->GetComponent<ShaderComponent>()->GetProgram());
	glUniformMatrix4fv(checker_black->GetComponent<ShaderComponent>()->GetUniformID("modelMatrix"), 1, GL_FALSE, checker_black->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, checker_black->GetComponent<MaterialComponent>()->getTextureID());
	checker_black->GetComponent<MeshComponent>()->Render(GL_TRIANGLES);
	// Then unbind the texture to get ready for the next thing we might render

	glUseProgram(checker_white->GetComponent<ShaderComponent>()->GetProgram());
	glUniformMatrix4fv(checker_white->GetComponent<ShaderComponent>()->GetUniformID("modelMatrix"), 1, GL_FALSE, checker_white->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, checker_white->GetComponent<MaterialComponent>()->getTextureID());
	checker_white->GetComponent<MeshComponent>()->Render(GL_TRIANGLES);

	glBindTexture(GL_TEXTURE_2D, 0);




	glUseProgram(0);
}


