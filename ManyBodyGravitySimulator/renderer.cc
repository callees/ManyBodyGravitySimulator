#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "NBodySimulation.h"

#include "NBodyRenderer.h"

float screenX = 1280;
float screenY = 720;

//float scaleFactor = 0.027;
float scaleFactor = 2.19219998e-12;
//float scaleFactor = 3.13656900e-09;


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	float increment = scaleFactor / 20;
	scaleFactor += increment * (float)yoffset;
	if (scaleFactor < 0)
	{
		scaleFactor = 0;
	}
}

int main(void) {

	NBodySimulation testSimulation;
	testSimulation.setUpTestSimulation();
	testSimulation.trackBodyHistory();

	//4333*100
	for (unsigned int epoch = 0; epoch < 4333*10; epoch++)
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

	glfwMakeContextCurrent(window);
	glewInit();


	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(0x8861);
	glfwSwapInterval(0);

	NBodyRenderer nBodyRenderer(testSimulation.getBodyHistory(), window);

	while (!glfwWindowShouldClose(window))
	{
		nBodyRenderer.draw();
		glfwSwapBuffers(window);
		glfwSetScrollCallback(window, scroll_callback);
		nBodyRenderer.setScaleFactor(scaleFactor);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}