#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const VertexBuffer & other)
{
	m_ID = other.m_ID;
	other.m_copied = true;
}

VertexBuffer::~VertexBuffer()
{
	if (!m_copied)
	{
		GLCall(glDeleteBuffers(1, &m_ID));
	}
}

VertexBuffer & VertexBuffer::operator=(const VertexBuffer & other)
{
	m_ID = other.m_ID;
	other.m_copied = true;
	return *this;
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::SetData(const void * data, unsigned int size)
{
	Bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	Unbind();
}
