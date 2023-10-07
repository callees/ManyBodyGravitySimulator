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

#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

#include "VertexArrayBuffer.h"

float screenX = 1280;
float screenY = 720;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 view;
glm::mat4 trans;
glm::mat4 projection = glm::mat4(1);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float fov = 45;
float scaleFactor = 0.001;

void processInput(GLFWwindow* window)
{
	float cameraSpeed = 2.5f * deltaTime * (1/scaleFactor); // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraRight;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraRight;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	float increment = scaleFactor / 20;
	scaleFactor += increment * (float)yoffset;
	if (scaleFactor < 0)
	{
		scaleFactor = 0;
	}
}

void centerCameraOnBody(TwoVector center)
{
	cameraPos = glm::vec3(center.x1(), center.x2(), 3.0f);
}

void printMat4(glm::mat4 mat)
{
	for (unsigned int row = 0; row < mat.length(); row++) {
		for (unsigned int column = 0; column < mat[row].length(); column++)
		{
			std::cout << mat[row][column] << "\t";
		}
		std::cout << "\n";
	}
}

void printVec4(glm::vec4 vec)
{
	for (unsigned int element = 0; element < vec.length(); element++)
	{
		std::cout << vec[element] << "\t";
	}
	std::cout << "\n";
}

int main(void) {

	NBodySimulation testSimulation;
	testSimulation.setUpTestSimulation();
	testSimulation.trackBodyPositionHistory();
	for (unsigned int epoch = 0; epoch < 200000; epoch++)
	{
		testSimulation.simulateOneTimeStep();
	};

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(screenX, screenY, "Cal's Universe Simulator: Renderer WIP", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glewInit();


	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	std::vector<TwoVector> positions = testSimulation.getBodyPositionHistory()[0];

	const int sizeOfPositions = 2 * positions.size();
	float* positionsForOpenGl = new float[sizeOfPositions];
	std::string vertexCode = readShader("C:\\Users\\Cal\\Documents\\Code\\ManyBodyGravitySimulator\\ManyBodyGravitySimulator\\vertex.vert");
	auto vertex = vertexCode.c_str();
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex, NULL);
	glCompileShader(vertexShader);

	std::string fragmentCode = readShader("C:\\Users\\Cal\\Documents\\Code\\ManyBodyGravitySimulator\\ManyBodyGravitySimulator\\fragment.frag");
	auto fragment = fragmentCode.c_str();
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment, NULL);
	glCompileShader(fragmentShader);

	unsigned int ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	glUseProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);


		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "Shader program linked succesfully" << std::endl;
	}

	int positionUniform = glGetUniformLocation(ID, "uniformBodyPosition");
	int cameraUniform = glGetUniformLocation(ID, "camera");
	int projectionUniform = glGetUniformLocation(ID, "projection");
	int resolutionUniform = glGetUniformLocation(ID, "iResolution");
	int translationUniform = glGetUniformLocation(ID, "translation");
	int massUniform = glGetUniformLocation(ID, "normalisedMass");

	glEnable(0x8861);
	glUniform2f(resolutionUniform, screenX, screenY);
	glfwSwapInterval(0);
	/* Loop until th user closes the window */
	unsigned int currentHistory = 0;
	std::vector<std::vector<TwoVector>> history = testSimulation.getBodyPositionHistory();
	unsigned int endOfHistory = testSimulation.getBodyPositionHistory().size();
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (currentHistory == endOfHistory) return 0;
		view = glm::lookAt(cameraPos, glm::vec3(cameraPos.x, cameraPos.y, 0.0f), cameraUp);
		projection = glm::perspective(glm::radians(fov), screenX / screenY, 0.1f, 100.0f);
		trans = glm::scale(glm::mat4(1.0), glm::vec3(scaleFactor));

		glUniformMatrix4fv(translationUniform, 1, GL_FALSE, glm::value_ptr(trans));
		glUniformMatrix4fv(cameraUniform, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(projection));
		glClear(GL_COLOR_BUFFER_BIT);
		auto currentPositions = history[currentHistory];
		for (unsigned int currentBody = 0; currentBody < currentPositions.size(); currentBody++) {
			glUniform2f(positionUniform, currentPositions[currentBody].x1(), currentPositions[currentBody].x2());
			glUniform1f(massUniform, testSimulation.simulatedBodies_[currentBody].body().mass() / (2.5 + testSimulation.simulatedBodies_[currentBody].body().mass()));
			glDrawArrays(GL_POINTS, 0, 1);
		}
		glfwSwapBuffers(window);
		glfwSetScrollCallback(window, scroll_callback);
		/* Poll for and process events */
		glfwPollEvents();
		processInput(window);
		currentHistory++;
	}

	glfwTerminate();
	return 0;
}

//Loop over and set uniforms

//Instancing


//L