// Copyright (c) 2020 udv. All rights reserved.

#ifndef GL_LEARN_SHADER
#define GL_LEARN_SHADER

#include <xstring>
#include <fstream>
#include <iostream>

#include <glad.h>
#include <GLFW/glfw3.h>

class shader {
private:
	GLuint id;

	static void checkhandle_program_error(GLuint id, GLenum action) {
		int success;
		char info_log[512];
		glGetProgramiv(id, action, &success);
		if (!success) {
			glGetProgramInfoLog(id, 512, nullptr, info_log);
			std::cout << info_log;
		}
	}

	static void checkhandle_shader_error(GLuint id, GLenum action) {
		int success;
		char info_log[512];
		glGetShaderiv(id, action, &success);
		if (!success) {
			glGetShaderInfoLog(id, 512, nullptr, info_log);
			std::cout << info_log;
		}
	}

	static std::string *read_shader(std::string &&filename) {
		auto *buffer = new std::string;

		std::ifstream f(filename);
		f.seekg(0, std::ios::end);
		buffer->resize(f.tellg());
		f.seekg(0);
		f.read(buffer->data(), buffer->size());

		f.close();

		return buffer;
	}

public:
	shader(std::string &&vertex_filename, std::string &&fragment_filename) {
		//region Vertex shader
		const GLchar * const v_src_buffer = (*read_shader(std::move(vertex_filename))).c_str();

		GLuint vid;
		vid = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vid, 1, &v_src_buffer, nullptr);
		glCompileShader(vid);
		checkhandle_shader_error(vid, GL_COMPILE_STATUS);
		//endregion

		//region Fragment shader
		const GLchar *const f_src_buffer = (*read_shader(std::move(fragment_filename))).c_str();

		GLuint fid;
		fid = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fid, 1, &f_src_buffer, nullptr);
		glCompileShader(fid);
		checkhandle_shader_error(fid, GL_COMPILE_STATUS);
		//endregion

		// region Program
		id = glCreateProgram();
		glAttachShader(id, vid);
		glAttachShader(id, fid);
		glLinkProgram(id);

		checkhandle_program_error(id, GL_LINK_STATUS);
		// endregion

		glDeleteShader(vid);
		glDeleteShader(fid);
	}

	void use() const {
		glUseProgram(id);
	}

};

#endif //GL_LEARN_SHADER
