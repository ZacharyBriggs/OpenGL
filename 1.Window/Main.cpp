#include <gl_core_4_4.h>
#include <glfw3.h>
#include <stdio.h>
#include <Gizmos.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>#include "Application.h"
int main()
{
	Application* App = new Application();
	while (true)
		App->run("game",720,720,false);
	delete App;
	return 0;
	//if (glfwInit() == false)
	//	return -1;
	//GLFWwindow* window = glfwCreateWindow(1280, 720,
	//	"Computer Graphics",
	//	nullptr, nullptr);
	//if (window == nullptr) {
	//	glfwTerminate();
	//	return -2;
	//}
	//glfwMakeContextCurrent(window);
	//// the rest of our code goes here!
	//if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
	//	glfwDestroyWindow(window);
	//	glfwTerminate();
	//	return -3;
	//}	//Gizmos::create();
	//glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	//glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f,
	//	16 / 9.f, 0.1f, 1000.f);	//auto major = ogl_GetMajorVersion();
	//auto minor = ogl_GetMinorVersion();
	//printf("GL: %i.%i\n", major, minor);	//glClearColor(0.25f, 0.25f, 0.25f, 1);	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) 
	//{
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	Gizmos::clear();
	//	Gizmos::addTransform(glm::mat4(1));
	//	glm::vec4 white(1);
	//	glm::vec4 black(0, 0, 0, 1);
	//	for (int i = 0; i < 21; ++i) {
	//		Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
	//			glm::vec3(-10 + i, 0, -10),
	//			i == 10 ? white : black);
	//		Gizmos::addLine(glm::vec3(10, 0, -10 + i),
	//			glm::vec3(-10, 0, -10 + i),
	//			i == 10 ? white : black);
	//	}
	//	Gizmos::draw(projection * view);
	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}	//Gizmos::destroy();
	//glfwDestroyWindow(window);
	//glfwTerminate();
	//return 0;
}