#pragma once
#include<iostream>
#include<unordered_map>
#include<string>

struct ShaderProgramSource
{
	std::string vertex_source;
	std::string fragment_source;
};



class Shader
{
private:
	std::string file_path;
	unsigned int program_id;
	std::unordered_map < std::string, int > localtion_map;
public:
	Shader(const std::string path);
	~Shader();

	void Bind() const;
	void Unbind() const;

	unsigned get_uniform_location(const std::string name);
	void set_uniform_4f(const std::string name, float v1, float v2, float v3, float v4);
	void set_uniform_1i(const std::string name, int v1);

private:
	unsigned int create_shader(std::string& vertex_shader, std::string& fragment_shader);
	unsigned int compile_shader(unsigned int type, const std::string& source);
	ShaderProgramSource parse_file();
};
