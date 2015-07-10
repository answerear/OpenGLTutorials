
#include <stdio.h>
#include <stdlib.h>

#include <gl/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.h>

int main(int argc, char *argv[])
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	auto window = glfwCreateWindow(1024, 768, "Tutorial 04 - Colored cube", NULL, NULL);
	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "");
		glfwTerminate();
		return -3;
	}

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Shutdown GLFW
	glfwTerminate();

	return 0;
}
