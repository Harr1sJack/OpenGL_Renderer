#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cerrno>

std::string Get_File_Content(const char* flieName);

class Shader
{
	public:
		GLint ID;
		std::string name;

		Shader(const char* vertexFile, const char* fragmentFile, std::string shaderName);

		void Activate();
		void Delete();
	private:
		void CompileError(unsigned int shader,const char* type);
};

#endif
