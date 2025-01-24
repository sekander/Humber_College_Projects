#include <glm/ext/matrix_clip_space.hpp>

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <vector>
#include <math.h>
 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


//#include "../include/nahid_math.h"
#include "../include/Physics.h"
//

using glm::mat4;
using glm::vec3;
using std::vector;
 

class Line {
    int shaderProgram;
    unsigned int VBO, VAO;
    vector<float> vertices;
    //vec3 startPoint;
    //vec3 endPoint;
    vec_3 origin_point;
    vec_3 direction_vector;
    mat4 MVP = mat4(1.0);

    

    vec3 lineColor;

    //vec_3 colour;

private:

public:
    //Line(vec3 start, vec3 end, int screen_width, int screen_height) {
    Line(vec_3 start, vec_3 end) {
 
        //startPoint = start;
        //endPoint = end;
        origin_point = start;
        direction_vector = end;
        lineColor = vec3(1,1,1);

	
 
        const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "uniform mat4 MVP;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        const char *fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "uniform vec3 color;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(color, 1.0f);\n"
            "}\n\0";
 
        // vertex shader
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        // check for shader compile errors
 
        // fragment shader
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        // check for shader compile errors
 
        // link shaders
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        // check for linking errors
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

	/*
	float x1 = start.x;
    	float y1 = start.y;
    	float x2 = end.x;
    	float y2 = end.y;
    	float w =  screen_width;
    	float h =  screen_height;

    	// convert 3d world space position 2d screen space position
    	x1 = 2*x1 / w - 1;
    	y1 = 2*y1 / h - 1;

	x2 = 2*x2 / w - 1;
	y2 = 2*y2 / h - 1;

    	start.x = x1;
    	start.y = y1;
	end.x = x2;
    	end.y = y2;
	*/



        vertices = {
             start.x, start.y, start.z,
             end.x, end.y, end.z,
 
        };
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
 
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
 
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 
 
    }
 
    int setMVP(mat4 mvp) {
        MVP = mvp;
        return 1;
    }
 
    int setColor(vec3 color) {
        lineColor = color;
        return 1;
    }

    int draw() {
        glUseProgram(shaderProgram);
 
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, &lineColor[0]);
 
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 2);
        return 1;
    }

    int draw(float xpos, float ypos, float rotate, float scale) {
        glUseProgram(shaderProgram);
 
	 glm::mat4 model = glm::mat4(1.0f);
    	 model = glm::translate(model, glm::vec3(xpos, ypos, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    	model = glm::translate(model, glm::vec3(0.5f * direction_vector.x, 0.5f * direction_vector.y, 0.0f)); // move origin of rotation to center of quad
    	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    	model = glm::translate(model, glm::vec3(-0.5f * direction_vector.x, -0.5f * direction_vector.y, 0.0f)); // move origin back

	model = glm::scale(model, glm::vec3(scale, scale, 0.0f));

    	//model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

        //i = animation;
	MVP = MVP * model;

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, &lineColor[0]);
 
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 2);
        return 1;
    }
 
    ~Line() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
    }
};

