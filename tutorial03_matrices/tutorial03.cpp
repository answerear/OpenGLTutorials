
#include <stdio.h>
#include <stdlib.h>

#include <gl/glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.h>


int main(int argc, char *argv[])
{
	// Initialize GLFW component
	if (!glfwInit())
	{
		fprintf(stderr, "");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	auto window = glfwCreateWindow(1024, 768, "Tutorial 03 - Matrices", NULL, NULL);
	if (window == nullptr)
	{
		fprintf(stderr, "");
		glfwTerminate();
		return -2;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "");
		glfwTerminate();
		return -3;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Create vertex array
	GLuint unVertexArrayID;
	glGenVertexArrays(1, &unVertexArrayID);
	glBindVertexArray(unVertexArrayID);

	// Load shaders
	GLuint unProgram = LoadShader("SimpleTransformVertex.glsl", "SingleColorFragment.glsl");

	// Get a handle for matMVP uniform
	GLuint unMatMVP = glGetUniformLocation(unProgram, "matMVP");

	// Projection matrix, 45 degree FOV, 4:3 ratio, display range : 0.1 -> 100.0
	glm::mat4 matProjection = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
// 	glm::mat4 matProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);

	// Camera matrix
	glm::mat4 matView = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	// Model matrix
	glm::mat4 matModel = mat4(1.0f);

	glm::mat4 matMVP = matProjection * matView * matModel;

	static const GLfloat g_vertex_buffer_data[] =
	{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	GLuint unVertexBuffer;
	glGenBuffers(1, &unVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, unVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
// 	glBindBuffer(GL_ARRAY_BUFFER, unVertexBuffer);

	glEnableVertexAttribArray(0);

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(unProgram);

		glUniformMatrix4fv(unMatMVP, 1, GL_FALSE, &matMVP[0][0]);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDisableVertexAttribArray(0);

	glDeleteBuffers(1, &unVertexBuffer);
	glDeleteVertexArrays(1, &unVertexArrayID);
	glDeleteProgram(unProgram);

	// Shutdown GLFW service
	glfwTerminate();

	return 0;
}

