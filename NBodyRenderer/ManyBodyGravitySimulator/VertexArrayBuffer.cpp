#include "VertexArrayBuffer.h"
#include "GL/glew.h"

VertexArrayBuffer::VertexArrayBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexArrayBuffer::~VertexArrayBuffer()
{
	glDeleteBuffers(1, &vbo_);
}

void VertexArrayBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
}

void VertexArrayBuffer::bufferData()
{

}