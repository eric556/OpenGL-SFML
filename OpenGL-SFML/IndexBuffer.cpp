#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int * data, unsigned int count) : m_Count(count)
{
	GLCall(glGenBuffers(1, &m_ID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,  m_Count, data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(const IndexBuffer & other)
{
	m_ID = other.m_ID;
	m_Count = other.m_Count;
	other.m_copied = true;
}

IndexBuffer::~IndexBuffer()
{
	if (!m_copied) 
	{
		GLCall(glDeleteBuffers(1, &m_ID));
	}
}

IndexBuffer & IndexBuffer::operator=(const IndexBuffer & other)
{
	m_ID = other.m_ID;
	m_Count = other.m_Count;
	other.m_copied = true;
	return *this;
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::SetData(const unsigned int * data, unsigned int count)
{
	m_Count = count;
	Bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count, data, GL_STATIC_DRAW));
	Unbind();
}
