#pragma once
class VertexArrayBuffer
{
public:
	VertexArrayBuffer(const void* data, unsigned int size);
	~VertexArrayBuffer();
	void bind();
	void bufferData();
private:
	unsigned int vbo_;
};

