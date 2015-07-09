#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "shader.h"

using namespace std;

GLuint LoadShader(const char *vertex_file_path, const char *fragment_file_path)
{
	// Create vertex shader
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	// Read vertex shader code from file
	string strShader;
	fstream fs(vertex_file_path, ios::in);
	if (fs.is_open())
	{
		string strLine("");
		while (getline(fs, strLine))
			strShader += "\n" + strLine;
		fs.close();
		fs.flush();
	}
	else
	{
		fprintf(stderr, "Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	GLint nResult = 0;
	GLint nInfoLogLength;

	// Compile vertex shader
	printf("Compiling shader : %s\n", vertex_file_path);
	const char *pVertexShader = strShader.c_str();
	glShaderSource(vertexShaderID, 1, &pVertexShader, NULL);
	glCompileShader(vertexShaderID);

	// Check vertex shader
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &nResult);
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &nInfoLogLength);
	vector<char> logs(nInfoLogLength);
	glGetShaderInfoLog(vertexShaderID, nInfoLogLength, NULL, &logs[0]);
	fprintf(stdout, "%s\n", &logs[0]);

	// Create fragment shader
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	strShader.clear();
	fs.open(fragment_file_path, ios::in);
	if (fs.is_open())
	{
		string strLine("");
		while (getline(fs, strLine))
			strShader += "\n" + strLine;

		fs.close();
		fs.flush();
	}

	// Compile fragment shader
	printf("Compiling shader : %s\n", fragment_file_path);
	const char *pFragmentShader = strShader.c_str();
	glShaderSource(fragmentShaderID, 1, &pFragmentShader, NULL);
	glCompileShader(fragmentShaderID);

	// Check fragment shader
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &nResult);
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &nInfoLogLength);
	logs.resize(nInfoLogLength);
	glGetShaderInfoLog(fragmentShaderID, nInfoLogLength, NULL, &logs[0]);
	fprintf(stdout, "%s\n", &logs[0]);

	// Link the program
	fprintf(stdout, "Linking program");

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShaderID);
	glAttachShader(program, fragmentShaderID);
	glLinkProgram(program);

	// Check the program
	glGetProgramiv(program, GL_LINK_STATUS, &nResult);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &nInfoLogLength);
	logs.resize(nInfoLogLength);
	glGetProgramInfoLog(program, nInfoLogLength, NULL, &logs[0]);
	fprintf(stdout, "%s\n", &logs[0]);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return program;
}
