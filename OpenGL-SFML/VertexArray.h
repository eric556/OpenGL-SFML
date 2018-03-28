#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Util.h"

class VertexArray 
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="VertexArray"/> class.
	/// </summary>
	VertexArray();

	/// <summary>
	/// VAO copy constructor
	/// </summary>
	/// <param name="other">The other.</param>
	VertexArray(const VertexArray& other);

	/// <summary>
	/// Finalizes an instance of the <see cref="VertexArray"/> class.
	/// </summary>
	~VertexArray();

	/// <summary>
	/// Operator=s the specified other.
	/// </summary>
	/// <param name="other">The other.</param>
	/// <returns></returns>
	VertexArray& operator=(const VertexArray& other);
	
	/// <summary>
	/// Binds this VAO.
	/// </summary>
	void Bind();

	/// <summary>
	/// Unbinds this VAO.
	/// </summary>
	void Unbind();

	/// <summary>
	/// Adds a VBO with the given layout to the VAO
	/// </summary>
	/// <param name="vb">The vbo.</param>
	/// <param name="layout">The vbo layout.</param>
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	inline unsigned int GetID() const { return m_ID; }
private:
	unsigned int m_ID;
	mutable bool m_copied;
};