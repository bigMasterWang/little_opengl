#include"Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include"Renderer.h"
#include<iostream>


Shader::Shader(const std::string path) : file_path(path)
{
	ShaderProgramSource spc = parse_file();
	program_id = create_shader(spc.vertex_source, spc.fragment_source);
}
Shader::~Shader()
{
	glUseProgram(0);
}

void Shader::Bind() const
{
	glUseProgram(program_id);
}
void Shader::Unbind() const
{
	glUseProgram(0);
}


unsigned int Shader::get_uniform_location(const std::string name)
{
	if (localtion_map.find(name) != localtion_map.end())
		return localtion_map[name];
	unsigned int localtion = glGetUniformLocation(program_id, name.c_str());
	localtion_map[name] = localtion;
	return localtion_map[name];
}
void Shader::set_uniform_4f(const std::string name, float v1, float v2, float v3, float v4)
{
	glUniform4f(get_uniform_location(name), v1, v2, v3, v4);
}

unsigned int Shader::create_shader(std::string& vertex_shader, std::string& fragment_shader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);


	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);


	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}
unsigned int Shader::compile_shader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}
ShaderProgramSource Shader::parse_file()
{
	std::ifstream stream(file_path);
	std::string line;
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;
	std::stringstream ss[2];
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}
