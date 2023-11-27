#include "EBO.h"

EBO::EBO(std::vector<GLuint>& indices)
{
	glGenBuffers(1, &ID);
	//binding the VBO by specfying it's a Array_Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);  
	//introducing the vertices into VBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
