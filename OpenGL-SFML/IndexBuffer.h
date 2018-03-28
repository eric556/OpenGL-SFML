#pragma once
#include <GL\glew.h>
#include "Util.h"

class IndexBuffer 
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="IndexBuffer"/> class.
	/// </summary>
	/// <param name="data">The index data.</param>
	/// <param name="count">The index data count.</param>
	IndexBuffer(const unsigned int* data, unsigned int count);

	/// <summary>
	/// <see cref="IndexBuffer"/> Copy constructor.
	/// </summary>
	/// <param name="other">The other.</param>
	IndexBuffer(const IndexBuffer& other);

	/// <summary>
	/// Finalizes an instance of the <see cref="IndexBuffer"/> class.
	/// </summary>
	~IndexBuffer();

	/// <summary>
	/// Operator=s the specified other.
	/// </summary>
	/// <param name="other">The other.</param>
	/// <returns></returns>
	IndexBuffer& operator=(const IndexBuffer& other);

	/// <summary>
	/// Binds this IBO.
	/// </summary>
	void Bind() const;

	/// <summary>
	/// Unbinds this IBO.
	/// </summary>
	void Unbind() const;

	/// <summary>
	/// Sets the data of this IBO.
	/// </summary>
	/// <param name="data">The index data.</param>
	/// <param name="count">The index data count.</param>
	void SetData(const unsigned int* data, unsigned int count);

	/// <summary>
	/// Gets the GL identifier. 
	/// </summary>
	/// <returns>the GL identifier of the IBO</returns>
	inline unsigned int GetID() const { return m_ID; }

	/// <summary>
	/// Gets the data count.
	/// </summary>
	/// <returns>the data count</returns>
	inline unsigned int GetCount() const { return m_Count; }
private:
	unsigned int m_ID;
	unsigned int m_Count;
	mutable bool m_copied;
};