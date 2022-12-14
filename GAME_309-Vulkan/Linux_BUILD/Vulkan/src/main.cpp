#define STB_IMAGE_IMPLEMENTATION
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include <stdexcept>
#include <vector>
#include <iostream>

#include "../include/Render/VulkanRenderer.h"
//#include "../include/Camera/Perspective_camera.h"

//#include "../include/Camera/openGL_camera.h"
#include "../include/Camera/Camera.h"

// Rotation and Mouse
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));


GLFWwindow* window;
VulkanRenderer vk_render;
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

Camera camera;
//float x_cam = 0.0f;
//float y_cam = 0.0f;
//float z_cam = 0.0f;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//-----------------INPUTS------------------------------------------------
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


const unsigned int SCR_WIDTH  = 900;
const unsigned int SCR_HEIGHT = 600;

float x_cam, y_cam, z_cam, r_cam;
float x, y, z;
glm::vec2 z_scale;

//float lastX =  800.0f / 2.0;
//float lastX =  SCR_WIDTH / 2.0;
float lastX = 0.0f;
//float lastY =  600.0 / 2.0;
//float lastY =  SCR_HEIGHT / 2.0;
float lastY = 0.0f;
//float fov   =  45.0f;

bool firstMouse = true;

//timing 
float delta_time = 0.0f;	//time between current frame and last frame
float last_frame = 0.0f;



void initWindow(std::string w_name = "Nahid Window", const int width = 900, const int height = 600)
{
	//Initialzie glfw
	glfwInit();

	//Set GLFW to NOT work with openGL
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	window = glfwCreateWindow(width, height, w_name.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Mouse Calls
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetWindowPos(window, 0, 0);
    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		

}

int main(){

	//Create Window
	initWindow();
	printf("GLFW Initalized\n");

	//Create Vulkan Renderere Instance
	if(vk_render.init(window) == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}

	float angle = 0.0f;
	float deltaTime = 0.0f;
	float lastTime = 0.0f;

	x = 1.0f;
	y = 1.0f;
	z = 1.0f;
	x_cam = 0.0f;
	y_cam = -5.0f;
	z_cam = 3.0f;

	float wave0;
	float wave1;
	float wave2;

	vk_render.createMeshModel("Mario.obj", "mario_main.png");
	vk_render.createMeshModel("Dragon.3ds", "Dragon_ground_color.jpg");
	vk_render.createMeshModel("Skull.obj", "skull_texture.jpg");



	
	//Loop until closed
	printf("Creating Window\n");
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
        processInput(window);
		camera.UpdateViewMatrix();
		camera.SetRotation(z_cam);
			float now = glfwGetTime();
			deltaTime = now - lastTime;
			lastTime = now;


			// per-frame time logic
			//
			float current_frame = glfwGetTime();
			delta_time = current_frame - last_frame;
			last_frame = current_frame;


			angle += 10.0f * deltaTime;
			if(angle > 360.0f){angle -= 360.0f;}

			glm::mat4 firstModel(1.0f);
			glm::mat4 secondModel(1.0f);
			glm::mat4 thridModel(1.0f);

			firstModel = glm::translate(firstModel, glm::vec3(-1.0f, 0.0f, -2.5f));
			firstModel = glm::rotate(firstModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			firstModel = glm::rotate(firstModel, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

			
			secondModel = glm::translate(secondModel, glm::vec3(1.0f, 0.0f, -3.0f));
			secondModel = glm::rotate(secondModel, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			secondModel = glm::rotate(secondModel, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			secondModel = glm::rotate(secondModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			secondModel = glm::rotate(secondModel, glm::radians(270.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			secondModel = glm::scale(secondModel, glm::vec3(0.5f, 0.5f, 0.5f));
			secondModel = glm::scale(secondModel, glm::vec3(0.25f, 0.25f, 0.25f));
			secondModel = glm::scale(secondModel, glm::vec3(0.25f, 0.25f, 0.25f));
			secondModel = glm::rotate(secondModel, glm::radians(-angle * 1), glm::vec3(0.0f, 0.0f, 1.0f));
//
//
//
			thridModel = glm::translate(thridModel , glm::vec3(-1.0f, 4.0f, -2.5f));
			thridModel = glm::rotate(thridModel , glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			thridModel = glm::rotate(thridModel , glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));


			vk_render.updateModel(0, firstModel);
			vk_render.updateModel(1, secondModel);
			vk_render.updateModel(2, thridModel);


			
			wave0 = 1.0f * sin(2 * 3.14 * 0.001f * (int)(glfwGetTime() * 100)); 
			wave1 = 1.0f * cos(2 * 3.14 * 0.001f * (int)(glfwGetTime() * 100)); 
			wave2 = 1.0f * sin(2 * 3.14 * 0.0001f * (int)(glfwGetTime() * 100)); 


			//vk_render.pushData.push_constant_colour = vec4(1.0f, 1.0f, 0.0f, 0.0f);	
			//Move Red light with keyboard
			vk_render.lightData.position[0] = glm::vec3(x, y, z);
			

			//Red Light
			vk_render.lightData.colour[0] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);	
			//Blue Light
			vk_render.lightData.colour[1]   = glm::vec4(0.0f, 0.0f, abs(wave0), 0.0f);
			//Green Light
			vk_render.lightData.colour[2]   = glm::vec4(0.0f, abs(wave1), 0.0f, 0.0f);
		vk_render.draw();


		vk_render.uboViewProjection.projection = glm::perspective(glm::radians(1000.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		vk_render.uboViewProjection.projection[1][1] *= -1;
		vk_render.uboViewProjection.view = camera.GetViewMatrix();


    	// check and call events and swap the buffers
    	glfwPollEvents();
    	glfwSwapBuffers(window);
		//vk_render.uboViewProjection.projection[1][1] *= -1;

	}

	vk_render.cleanup();

	//Destroy GLFW window and stop GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

return 0;
};


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	    glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	    x += 0.1;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	    x -= 0.1;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	    y -= 0.1;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	    y += 0.1;


    //Camera Controls
    //const float camera_speed = 0.25f; //adjust camera speed
    float camera_speed = 2.5 * delta_time; //adjust camera speed

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	    //camera.ProcessKeyboard(FORWARD, delta_time);
		{
			y_cam += 0.005;	
			camera.SetPosition(glm::vec3(x_cam, y_cam, z_cam));
		}
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			y_cam -= 0.005;	
			camera.SetPosition(glm::vec3(x_cam, y_cam, z_cam));
		}
            //camera.ProcessKeyboard(BACKWARD, delta_time);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			x_cam -= 0.005;	
			camera.SetPosition(glm::vec3(x_cam, y_cam, z_cam));
		}
            //camera.ProcessKeyboard(LEFT, delta_time);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			x_cam += 0.005;	
			camera.SetPosition(glm::vec3(x_cam, y_cam, z_cam));
		}
            //camera.ProcessKeyboard(RIGHT, delta_time); 



    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
	    x_cam +=0.01f;
//	    o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
            std::cout << "X cam : " << x_cam  << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
	    x_cam -=0.01f;
//	    o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
            std::cout << "X cam : " << x_cam  << std::endl;
    	//ResourceManager::GetShader("sprite").SetMatrix4("projection", o_cam->return_matrix());
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
	    y_cam -=0.01f;
//	    o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
            std::cout << "Y cam : " << y_cam  << std::endl;
    	//ResourceManager::GetShader("sprite").SetMatrix4("projection", o_cam->return_matrix());
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
	    y_cam +=0.01f;
//	    o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
            std::cout << "Y cam : " << y_cam  << std::endl;
    	//ResourceManager::GetShader("sprite").SetMatrix4("projection", o_cam->return_matrix());
    }
    
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
	    z_cam +=0.0001;
		camera.SetRotation(z_cam);
//	    o_cam->SetRotation(r_cam);
            std::cout << "R cam : " << z_cam  << std::endl;
    	//ResourceManager::GetShader("sprite").SetMatrix4("projection", o_cam->return_matrix());
    }
    
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
	    z_cam -=0.0001;
		camera.SetRotation(z_cam);
//	    o_cam->SetRotation(r_cam);
            std::cout << "R cam : " << z_cam  << std::endl;
    	//ResourceManager::GetShader("sprite").SetMatrix4("projection", o_cam->return_matrix());
    }

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
	    z_scale.x += 0.01;
	    z_scale.y += 0.01;
	    z += 0.01;
//	    o_cam->SetScale(z_scale);
            std::cout << "Z-x cam : " << z_scale.x << std::endl;
            std::cout << "Z-y cam : " << z_scale.y << std::endl;
    	//ResourceManager::GetShader("sprite").SetMatrix4("projection", o_cam->return_matrix());
    }

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
	    z_scale.x -= 0.01;
	    z_scale.y -= 0.01;
	    z -= 0.01;
//	    o_cam->SetScale(z_scale);
            std::cout << "Z-x cam : " << z_scale.x << std::endl;
            std::cout << "Z-y cam : " << z_scale.y << std::endl;
    	//ResourceManager::GetShader("sprite").SetMatrix4("projection", o_cam->return_matrix());
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that widthand 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	//std::cout << "Xpos : " << lastX << "\nYpos : " << lastY  << std::endl;
	//camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//camera.ProcessMouseScroll(yoffset);
	//std::cout << "Yoffset : " << yoffset << std::endl;
}



