#include "Sphere.h"

Sphere::Sphere(float radius) : Mesh()
{
	for (unsigned int y = 0; y <= Y_SEGMENTS; y++) 
	{
		for (unsigned int x = 0; x <= X_SEGMENTS; x++) 
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			m_Verticies.push_back({
				glm::vec3(xPos, yPos, zPos) * radius,
				glm::vec2(xSegment, ySegment),
				glm::vec3(xPos, yPos, zPos)
			});
		}
	}

	bool oddRow = false;
	for (int y = 0; y < Y_SEGMENTS; y++) 
	{
		if (!oddRow) 
		{
			for (int x = 0; x <= X_SEGMENTS; x++) 
			{
				m_Indicies.push_back(y * (X_SEGMENTS + 1) + x);
				m_Indicies.push_back((y+1) * (X_SEGMENTS + 1) + x);
			}
		}
		else 
		{
			for (int x = X_SEGMENTS; x >= 0; x--) 
			{
				m_Indicies.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				m_Indicies.push_back(y * (X_SEGMENTS + 1) + x);
			}
		}
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
