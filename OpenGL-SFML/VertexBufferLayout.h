#pragma once
#include <GL\glew.h>
#include <vector>
#include "Util.h"

struct VertexBufferElement 
{
	unsigned int type;
	unsigned int count;
	unsigned int normailzed;

	static unsigned int GetSizeOfType(unsigned int type) 
	{
		switch (type) 
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_BYTE:	return 1;
			case GL_UNSIGNED_INT:	return 4;
		}
		return 0;
	}
};

class VertexBufferLayout 
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="VertexBufferLayout"/> class.
	/// </summary>
	VertexBufferLayout() : m_Stride(0) {};

	/// <summary>
	/// Pushes the specified count of T types to the layout.
	/// </summary>
	/// <param name="count">The count.</param>
	template<typename T>
	void Push(unsigned int count) 
	{
		static_assert(false);
	}

	/// <summary>
	/// Pushes the specified float count.
	/// </summary>
	/// <param name="count">The count.</param>
	template<>
	void Push<float>(unsigned int count) 
	{
		m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	/// <summary>
	/// Pushes the specified unsigned int count.
	/// </summary>
	/// <param name="count">The count.</param>
	template<>
	void Push<unsigned int>(unsigned int count) 
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	/// <summary>
	/// Pushes the specified unsigned char count.
	/// </summary>
	/// <param name="count">The count.</param>
	template<>
	void Push<unsigned char>(unsigned int count) 
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};