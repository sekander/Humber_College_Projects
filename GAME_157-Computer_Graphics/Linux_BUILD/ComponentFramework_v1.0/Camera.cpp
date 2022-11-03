#include "Camera.h"

Camera::Camera():Actor(nullptr)
{
	projectionMatrix = MMath::perspective(45.0f, 16.0f / 9.0f, 0.5, 100.0f);
	translation 	 = MMath::translate(0.0f, 0.0f, -10.0f);
	rotation		 = MMath::rotate(0.0f, Vec3(0.0f, 1.0f, 0.0f));

	viewMatrix = rotation * translation;
	trackball = new Trackball();
}

Camera::~Camera(){

	delete trackball;
	delete skybox;
}

bool Camera::OnCreate(){
	//skybox = new Skybox("textures/posx.jpg", "textures/posy.jpg", "textures/posz.jpg", 
	//					"textures/negx.jpg", "textures/negy.jpg", "textures/negz.jpg");

	//skybox->OnCreate();

//	LoadSkybox(a_pic, b_pic, c_pic, d_pic, e_pic, f_pic);

	     skybox = new Skybox(a_pic, b_pic, c_pic, d_pic, e_pic, f_pic);

	        skybox->OnCreate();

	return true;
}
void Camera::OnDestroy(){}

void Camera::HandleEvents(const SDL_Event& sdlEvent){
	trackball->HandleEvents(sdlEvent);
	rotation = trackball->getMatrix4();

	viewMatrix = rotation * translation;
}

void Camera::Render()const {

	glUseProgram(skybox->GetShader()->GetProgram());
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("viewMatrix"), 1, GL_FALSE, rotation);
	//glUniformMatrix4fv(skybox->GetShader()->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);


	skybox->Render();
}