#include "adlShader_program.h"

#include <fstream>

adlShader_program::adlShader_program()
{

}

adlShader_program::~adlShader_program()
{

}

void adlShader_program::init(const std::string& vertex_file_path, const std::string& fragment_file_path)
{
	adlLogger* adl_logger = &adlLogger::get();
	adl_logger->log_info("Compiling shader");
	vertex_shader_id_ = load_shader(vertex_file_path, GL_VERTEX_SHADER);
	fragment_shader_id_ = load_shader(fragment_file_path, GL_FRAGMENT_SHADER);

	program_id_ = glCreateProgram();
	glAttachShader(program_id_, vertex_shader_id_);
	glAttachShader(program_id_, fragment_shader_id_);

	bind_attributes();

	glLinkProgram(program_id_);
	check_shader_error(program_id_, GL_LINK_STATUS, true, "Program linking failed.\n");

	glValidateProgram(program_id_);
	check_shader_error(program_id_, GL_VALIDATE_STATUS, true, "Program invalid.\n");

	get_all_uniform_locations();
}

void adlShader_program::bind_attribute(int attribute, const std::string& variable_name)
{
	glBindAttribLocation(program_id_, attribute, variable_name.c_str());
}

int32 adlShader_program::get_uniform_location(const std::string& uniform_name)
{
	int32 location = glGetUniformLocation(program_id_, uniform_name.c_str());
	return location;
}

void adlShader_program::load_vector(int32 location, adlVec3 vector)
{
	glUniform3fv(location, 1, vector.vec);
}


void adlShader_program::start()
{
	glUseProgram(program_id_);
}

void adlShader_program::stop()
{
	glUseProgram(0);
}

void adlShader_program::clean_up()
{
	stop();
	glDetachShader(program_id_, vertex_shader_id_);
	glDetachShader(program_id_, fragment_shader_id_);
	glDeleteShader(vertex_shader_id_);
	glDeleteShader(fragment_shader_id_);
	glDeleteProgram(program_id_);
}

uint32 adlShader_program::load_shader(const std::string& shader_path, int32 shader_type)
{
	adlLogger* adl_logger = &adlLogger::get();
	std::ifstream file;
	file.open(shader_path);

	std::string file_text;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			file_text.append(line + "\n");
		}
	}
	else
	{
		adl_logger->log_error("Unable to open shader file at " + shader_path);
	}

	uint32 shader_id = glCreateShader(shader_type);
	if (shader_id == 0)
	{
		adl_logger->log_error("Could not create shader");
	}

	const char* shader_source_strings[1];
	shader_source_strings[0] = file_text.c_str();

	int32 source_string_lengths[1];
	source_string_lengths[0] = file_text.length();

	glShaderSource(shader_id, 1, shader_source_strings, source_string_lengths);
	glCompileShader(shader_id);
	check_shader_error(shader_id, GL_COMPILE_STATUS, false, "Could not compile shader.");

	return shader_id;
}

void adlShader_program::check_shader_error(uint32 shader, uint32 flag, bool is_program, const std::string& error_message)
{
	int32 success = 0;
	char error[1024] = { 0 };

	if (is_program)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (is_program)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		adlLogger* adl_logger = &adlLogger::get();
		adl_logger->log_error(error_message + std::string(error));
	}
}