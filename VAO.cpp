#include "VAO.h"

VAO::VAO() 
{
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttributes(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	//config the vertex attribute so opengl know how to read it properly
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	//enabling the vertex attribute so opengl know to use it
	glEnableVertexAttribArray(layout);
	VBO.UnBind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
} 

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
