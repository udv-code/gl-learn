#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "util/shader.hpp"

//region Constants
constexpr int window_width = 800;
constexpr int window_height = 600;
//endregion

//region Callbacks
void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//endregion

int main(int argc, char **argv) {
	//region init
	if (glfwInit() != GLFW_TRUE) {
		std::cerr << "Failed to initialize GLFW!\n";
		return -1;
	}
	//endregion

	//region Window and context
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
	//endregion

	//region Load GL
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cerr << "Failed to load GL!\n";
		glfwTerminate();
		return -1;
	}

	std::cout << "Using OpenGL v" << glGetString(GL_VERSION) << "\n";
	//endregion

	//region Set Callbacks
	glViewport(0, 0, window_width, window_height);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//endregion

	// region Data
	// region static
	const int vertices_count = 4;
	const int vertices_size = vertices_count * (3);
	float vertices[vertices_size] = {
			// Positions
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
	};
	unsigned int indices[6] = {
			0, 1, 3,
			1, 2, 3,
	};
	// endregion

	// Element buffer
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// Shader
	shader program = shader{"shaders/default.vs.glsl", "shaders/default.fs.glsl"};

	// Vertex array
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertex buffer
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_size * sizeof(float), vertices, GL_STATIC_DRAW);

	// Attributes
	//// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	program.use();
	// endregion

	//region Main loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);

		// region Rendering
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)nullptr);
		// endregion

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//endregion

	//region Finalization
	glfwTerminate();
	return 0;
	//endregion
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
