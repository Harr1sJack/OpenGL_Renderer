#include"ShaderClass.h"


std::string Get_File_Content(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile,const char* fragmentFile,std::string shaderName)
{
	name = shaderName;
	std::string vertexCode = Get_File_Content(vertexFile);
	std::string fragmentCode = Get_File_Content(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//creating vertex shader obj
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//linking the source vertex shader code to obj
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//compiling the obj
	glCompileShader(vertexShader);
	CompileError(vertexShader, "VERTEX");

	//creating fragment shader obj
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//linking the source fragment shader code to obj
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//compiling the obj
	glCompileShader(fragmentShader);
	CompileError(fragmentShader, "FRAGMENT");

	//creating shader program
	ID = glCreateProgram();
	//attaching the vertex and fragment to the shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//linking all the shaders to the shader program
	glLinkProgram(ID);
	CompileError(ID, "PROGRAM");

	//deleting the individual shader objs since we already linked it with program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete() 
{
	glDeleteShader(ID);
}

void Shader::CompileError(unsigned int shader, const char* type) 
{
	GLint hasCompiled;
	char charLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE) 
		{
			glGetShaderInfoLog(shader, 1024, NULL, charLog);
			std::cout << "Shader_Compilation_Error for " << name << type << "\n" << std::endl;
		}
	}
	else 
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, charLog);
			std::cout << "Shader_Linking_Error for " << type << "\n" << std::endl;
		}
	}
}