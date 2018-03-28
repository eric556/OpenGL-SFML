#include "Plane.h"

Plane::Plane(float width, float height) : Mesh()
{
	m_Verticies.push_back({ glm::vec3(-1.0 * width, 1.0 * height,0.0), glm::vec2(0.0,1.0), glm::vec3(0.0,0.0,0.0) });
	m_Verticies.push_back({ glm::vec3(-1.0 * width,-1.0 * height,0.0), glm::vec2(0.0,0.0), glm::vec3(0.0,0.0,0.0) });
	m_Verticies.push_back({ glm::vec3( 1.0 * width, 1.0 * height,0.0), glm::vec2(1.0,1.0), glm::vec3(0.0,0.0,0.0) });
	m_Verticies.push_back({ glm::vec3( 1.0 * width,-1.0 * height,0.0), glm::vec2(1.0,0.0), glm::vec3(0.0,0.0,0.0) });

	for (unsigned int i = 0; i < 4; i++) {
		m_Indicies.push_back(i);
	}

	VBO.Unbind();
	IBO.Unbind();

	VAO.Bind();
	VBO.Bind();
	VBO.SetData(m_Verticies.data(), m_Verticies.size() * sizeof(Vertex));
	m_layout.Push<float>(3);
	m_layout.Push<float>(2);
	m_layout.Push<float>(3);
	VAO.AddBuffer(VBO, m_layout);
	IBO.Bind();
	IBO.SetData(m_Indicies.data(), m_Indicies.size() * sizeof(unsigned int));
}
