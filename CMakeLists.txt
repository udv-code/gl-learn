cmake_minimum_required(VERSION 3.16)
project(gl_learn)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glad REQUIRED)

add_executable(gl_learn
		main.cpp
		util/shader.hpp)

target_link_libraries(
		gl_learn
		PRIVATE
		OpenGL::GL
		glfw
		glad::glad
)