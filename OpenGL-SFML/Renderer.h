#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Material.h"
#include "Mesh.h"
#include "Util.h"

class Renderer 
{
public:
	/// <summary>
	/// Clears the screen.
	/// </summary>
	static void Clear();

	/// <summary>
	/// Draws the specified vao and ibo with the given material.
	/// </summary>
	/// <param name="VAO">The vao.</param>
	/// <param name="IBO">The ibo.</param>
	/// <param name="mat">The mat.</param>
	static void Draw(VertexArray* VAO, IndexBuffer* IBO, Material* mat);

	/// <summary>
	/// Draws the specified mesh with the given material.
	/// </summary>
	/// <param name="mesh">The mesh.</param>
	/// <param name="mat">The mat.</param>
	static void Draw(Mesh* mesh, Material* mat);

	/// <summary>
	/// Draws the specified mesh with the given material and GL draw method (ie GL_TRIANGLES).
	/// </summary>
	/// <param name="mesh">The mesh.</param>
	/// <param name="mat">The mat.</param>
	/// <param name="drawMethod">The draw method.</param>
	static void Draw(Mesh* mesh, Material* mat, GLenum drawMethod);

};