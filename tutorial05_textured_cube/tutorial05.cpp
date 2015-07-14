#include <stdio.h>
#include <stdlib.h>

#include <gl/glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.h>
#include <common/texture.h>


int main(int argc, char *argv[])
{
	if (!glfwInit())
	{
		fprintf(stderr, "");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	auto window = glfwCreateWindow(1024, 768, "Tutorial 05 - Textured Cube", NULL, NULL);
	if (window == nullptr)
	{
		fprintf(stderr, "");
		glfwTerminate();
		return -2;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "");
		glfwTerminate();
		return -3;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue, background color
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Turn on depth test and set depth function
	glEnable(GL_DEPTH);
	glDepthFunc(GL_LESS);

	// Load shaders
	GLuint unProgram = LoadShader("TransformVertexShader.glsl", "TextureFragmentShader.glsl");

	GLuint unMatMVP = glGetUniformLocation(unProgram, "MVP");

	// Calculate matrix
	glm::mat4 matModel = glm::mat4(1.0f);
	glm::mat4 matView = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 matProjection = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);

	glm::mat4 matMVP = matProjection * matView * matModel;

	// Setup VAO
	GLuint unVertexArray;
	glGenVertexArrays(1, &unVertexArray);
	glBindVertexArray(unVertexArray);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	const static GLfloat g_cube_vertex_buffer_data[] =
	{
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	const static GLfloat g_cube_uv_buffer_data[] =
	{
		0.000059f, 0.000004f, 
		0.000103f, 0.336048f, 
		0.335973f, 0.335903f, 
		1.000023f, 0.000013f, 
		0.667979f, 0.335851f, 
		0.999958f, 0.336064f, 
		0.667979f, 0.335851f, 
		0.336024f, 0.671877f, 
		0.667969f, 0.671889f, 
		1.000023f, 0.000013f, 
		0.668104f, 0.000013f, 
		0.667979f, 0.335851f, 
		0.000059f, 0.000004f, 
		0.335973f, 0.335903f, 
		0.336098f, 0.000071f, 
		0.667979f, 0.335851f, 
		0.335973f, 0.335903f, 
		0.336024f, 0.671877f, 
		1.000004f, 0.671847f, 
		0.999958f, 0.336064f, 
		0.667979f, 0.335851f, 
		0.668104f, 0.000013f, 
		0.335973f, 0.335903f, 
		0.667979f, 0.335851f, 
		0.335973f, 0.335903f, 
		0.668104f, 0.000013f, 
		0.336098f, 0.000071f, 
		0.000103f, 0.336048f, 
		0.000004f, 0.671870f, 
		0.336024f, 0.671877f, 
		0.000103f, 0.336048f, 
		0.336024f, 0.671877f, 
		0.335973f, 0.335903f, 
		0.667969f, 0.671889f, 
		1.000004f, 0.671847f, 
		0.667979f, 0.335851f
	};

	// Create VBO
	GLuint CubeBuffer[2];
	glGenBuffers(2, CubeBuffer);

	// Bind VBO and set data
	glBindBuffer(GL_ARRAY_BUFFER, CubeBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_vertex_buffer_data), g_cube_vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, CubeBuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_uv_buffer_data), g_cube_uv_buffer_data, GL_STATIC_DRAW);

	// Load texture
	GLuint texture = LoadDDSImage("uvtemplate.DDS");
	GLuint textureID = glGetUniformLocation(unProgram, "textureSampler");

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		// Draw a cube with texture
		glUseProgram(unProgram);

		glUniformMatrix4fv(unMatMVP, 1, GL_FALSE, &matMVP[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(textureID, 0);

		glBindBuffer(GL_ARRAY_BUFFER, CubeBuffer[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, CubeBuffer[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDeleteTextures(1, &texture);
	glDeleteBuffers(2, CubeBuffer);
	glDeleteVertexArrays(1, &unVertexArray);
	glDeleteProgram(unProgram);

	glfwTerminate();

	return 0;
}
