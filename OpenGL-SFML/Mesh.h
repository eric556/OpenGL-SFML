#pragma once
#include "Material.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Util.h"
#include <vector>

/// <summary>
/// Vertex struct
/// </summary>
struct Vertex
{
	glm::vec3 Position;
    glm::vec2 Texture;
	glm::vec3 Normal;
};

class Mesh 
{
public:
	VertexArray VAO;
	IndexBuffer IBO;
	VertexBuffer VBO;
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Mesh"/> class.
	/// </summary>
	/// <param name="verticies">The verticies of the mesh.</param>
	/// <param name="indicies">The indicies of the mesh.</param>
	Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indicies);

	/// <summary>
	/// Initializes a new empty instance of the <see cref="Mesh"/> class.
	/// </summary>
	Mesh() : VBO(nullptr, 0), IBO(nullptr, 0) {};
protected:
	std::vector<Vertex> m_Verticies;
	std::vector<unsigned int> m_Indicies;
	VertexBufferLayout m_layout;

};