#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

constexpr int window_width = 800;
constexpr int window_height = 600;

void processInput(GLFWwindow *window);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main(int argc, char **argv) {
	if (glfwInit() != GLFW_TRUE) {
		std::cerr << "Failed to initialize GLFW!\n";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(window_width, window_height, "Learning Modern OpenGL", nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "Failed to create GLFW window!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cerr << "Failed to load GL!\n";
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, window_width, window_height);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
