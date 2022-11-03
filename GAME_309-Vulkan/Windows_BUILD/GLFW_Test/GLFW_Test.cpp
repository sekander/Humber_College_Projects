#define STB_IMAGE_IMPLEMENTATION
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include <stdexcept>
#include <vector>
#include <iostream>

#include "VulkanRenderer.h"


GLFWwindow* window;
VulkanRenderer vk_render;

void initWindow(std::string w_name = "Nahid Window", const int width = 900, const int height = 600)
{
	//Initialzie glfw
	glfwInit();

	//Set GLFW to NOT work with openGL
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, w_name.c_str(), nullptr, nullptr);
}

int main() {

	//Create Window
	initWindow();
	printf("GLFW Initalized\n");

	//Create Vulkan Renderere Instance
	if (vk_render.init(window) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}

	float angle = 0.0f;
	float deltaTime = 0.0f;
	float lastTime = 0.0f;

	vk_render.createMeshModel("Mario.obj", "mario_main.png");
	vk_render.createMeshModel("Mario.obj", "mario_mime.png");

	//Loop until closed
	printf("Creating Window\n");
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		float now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		angle += 10.0f * deltaTime;
		if (angle > 360.0f) { angle -= 360.0f; }

		glm::mat4 firstModel(1.0f);
		glm::mat4 secondModel(1.0f);

		firstModel = glm::translate(firstModel, glm::vec3(-1.0f, 0.0f, -2.5f));
		firstModel = glm::rotate(firstModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		firstModel = glm::rotate(firstModel, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));



		secondModel = glm::translate(secondModel, glm::vec3(1.0f, 0.0f, -3.0f));
		secondModel = glm::rotate(secondModel, glm::radians(-angle * 50), glm::vec3(0.0f, 1.0f, 0.0f));

		vk_render.updateModel(0, firstModel);
		vk_render.updateModel(1, secondModel);

		//vk_render.updateModel(glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)));


		vk_render.draw();
	}

	vk_render.cleanup();

	//Destroy GLFW window and stop GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
};
