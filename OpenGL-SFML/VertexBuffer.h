#pragma once
#include <GL\glew.h>
#include "Util.h"

class VertexBuffer 
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="VertexBuffer"/> class.
	/// </summary>
	/// <param name="data">The vertex data.</param>
	/// <param name="size">The size of the vertex data (bytes).</param>
	VertexBuffer(const void* data, unsigned int size);

	/// <summary>
	/// VBO copy constructor
	/// </summary>
	/// <param name="other">The other.</param>
	VertexBuffer(const VertexBuffer& other);

	/// <summary>
	/// Finalizes an instance of the <see cref="VertexBuffer"/> class.
	/// </summary>
	~VertexBuffer();

	/// <summary>
	/// Operator=s the specified other.
	/// </summary>
	/// <param name="other">The other.</param>
	/// <returns></returns>
	VertexBuffer& operator=(const VertexBuffer& other);

	/// <summary>
	/// Binds this VBO.
	/// </summary>
	void Bind() const;

	/// <summary>
	/// Unbinds this VBO.
	/// </summary>
	void Unbind() const;

	/// <summary>
	/// Sets the VBO data.
	/// </summary>
	/// <param name="data">The vertex data.</param>
	/// <param name="size">The vertex data size (bytes).</param>
	void SetData(const void* data, unsigned int size);

	inline unsigned int GetID() const { return m_ID; }
private:
	unsigned int m_ID;
	mutable bool m_copied;
};