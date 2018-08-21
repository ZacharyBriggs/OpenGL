#include "IntroApplication.h"

int main()
{
	auto App = new IntroApplication();
	App->run("title", 720, 720, false);
	
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
	//}
	//Gizmos::create();
	//auto major = ogl_GetMajorVersion();
	//auto minor = ogl_GetMinorVersion();
	//printf("GL: %i.%i\n", major, minor);
	//glm::mat4 model = glm::mat4(1);//model
	//glm::mat4 model2 = glm::translate(model, glm::vec3(25, 20, 0));
	//glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 25), glm::vec3(0), glm::vec3(0, 1, 0));//view
	//glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);//projection
	//glClearColor(0.25f, 0.25f, 0.25f, 1);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) 
	//{
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	Gizmos::clear();
	//	Gizmos::addSphere(glm::vec3(0, 0, 0), 5, 25, 25, glm::vec4(.5, .25, .25, 1), &model);
	//	Gizmos::draw(projection * view);
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
	//}
	//Gizmos::destroy();
	//glfwDestroyWindow(window);
	//glfwTerminate();
	//return 0;
}
