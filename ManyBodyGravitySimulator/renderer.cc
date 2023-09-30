#include <math.h>
#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Body.h"
#include "TwoVector.h"
#include "RK4Method.h"
#include "NBodySimulation.h"

#include "RK4FOODEs.h"
#include "RK4Function.h"

#include <math.h>


void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * atan(1)*4;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount;i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

#include <fstream>
#include <sstream>

const char* vShaderCode;
std::string readShader(const char* vertexPath)
{
	std::string vertexCode;
	std::ifstream vShaderFile;
	// ensure ifstream objects can throw exceptions:
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		std::stringstream vShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return vertexCode;
}

int main(void)
{

	NBodySimulation testSimulation;
	testSimulation.setUpTestSimulation();
	std::vector<TwoVector> posHistory;
	for (unsigned int epoch = 0; epoch < 1; epoch++)
	{
		posHistory.push_back(testSimulation.simulatedBodies_[0].body().position());
		testSimulation.testSimulate();
	};

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glewInit();
	std::string shaderCode = readShader("C:\\Users\\Cal\\Documents\\Code\\ManyBodyGravitySimulator\\ManyBodyGravitySimulator\\vertex.shader");
	auto code = shaderCode.c_str();
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &code, NULL);
	glCompileShader(vertexShader);
	unsigned int ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glLinkProgram(ID);

	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	int positionUniform = glGetUniformLocation(vertexShader, "position");

	//glfwSwapInterval(2);
	/* Loop until the user closes the window */
	unsigned int currentPos = 0;
	while (!glfwWindowShouldClose(window))
	{
		if (currentPos == posHistory.size()) return 0;
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		drawFilledCircle(posHistory[currentPos].x1(), posHistory[currentPos].x2(), 0.01);
		glfwSwapBuffers(window);
		glEnd();
		/* Poll for and process events */
		glfwPollEvents();
		currentPos++;
	}

	glfwTerminate();
	return 0;
}