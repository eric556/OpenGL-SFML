#include "Cube.h"

Cube::Cube(float size) : Mesh()
{
		// back face
		m_Verticies.push_back({glm::vec3(-1.0f, -1.0f, -1.0f) * size,  glm::vec2(0.0f,  0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)}); // bottom-left
		m_Verticies.push_back({glm::vec3( 1.0f,  1.0f, -1.0f) * size,  glm::vec2(0.0f,  0.0f), glm::vec3(-1.0f, 1.0f, 1.0f)}); // top-right
		m_Verticies.push_back({glm::vec3( 1.0f, -1.0f, -1.0f) * size,  glm::vec2(0.0f,  0.0f), glm::vec3(-1.0f, 1.0f, 0.0f)}); // bottom-right         
		m_Verticies.push_back({glm::vec3( 1.0f,  1.0f, -1.0f) * size,  glm::vec2(0.0f,  0.0f), glm::vec3(-1.0f, 1.0f, 1.0f)}); // top-right
		m_Verticies.push_back({glm::vec3(-1.0f, -1.0f, -1.0f) * size,  glm::vec2(0.0f,  0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)}); // bottom-left
		m_Verticies.push_back({glm::vec3(-1.0f,  1.0f, -1.0f) * size,  glm::vec2(0.0f,  0.0f), glm::vec3(-1.0f, 0.0f, 1.0f)}); // top-left
		// front face										  
		m_Verticies.push_back({glm::vec3(-1.0f, -1.0f,  1.0f) * size,  glm::vec2(0.0f,  0.0f), glm::vec3( 1.0f, 0.0f, 0.0f)}); // bottom-left
		m_Verticies.push_back({glm::vec3( 1.0f, -1.0f,  1.0f) * size,  glm::vec2(0.0f,  0.0f), glm::vec3( 1.0f, 1.0f, 0.0f)}); // bottom-right
		m_Verticies.push_back({glm::vec3( 1.0f,  1.0f,  1.0f) * size,  glm::vec2(0.0f,  0.0f), glm::vec3( 1.0f, 1.0f, 1.0f)}); // top-right
		m_Verticies.push_back({glm::vec3( 1.0f,  1.0f,  1.0f) * size,  glm::vec2(0.0f,  0.0f), glm::vec3( 1.0f, 1.0f, 1.0f)}); // top-right
		m_Verticies.push_back({glm::vec3(-1.0f,  1.0f,  1.0f) * size,  glm::vec2(0.0f,  0.0f), glm::vec3( 1.0f, 0.0f, 1.0f)}); // top-left
		m_Verticies.push_back({glm::vec3(-1.0f, -1.0f,  1.0f) * size,  glm::vec2(0.0f,  0.0f), glm::vec3( 1.0f, 0.0f, 0.0f)}); // bottom-left
		// left face										  
		m_Verticies.push_back({glm::vec3(-1.0f,  1.0f,  1.0f) * size, -glm::vec2(1.0f,  0.0f), glm::vec3( 0.0f, 1.0f, 0.0f)}); // top-right
		m_Verticies.push_back({glm::vec3(-1.0f,  1.0f, -1.0f) * size, -glm::vec2(1.0f,  0.0f), glm::vec3( 0.0f, 1.0f, 1.0f)}); // top-left
		m_Verticies.push_back({glm::vec3(-1.0f, -1.0f, -1.0f) * size, -glm::vec2(1.0f,  0.0f), glm::vec3( 0.0f, 0.0f, 1.0f)}); // bottom-left
		m_Verticies.push_back({glm::vec3(-1.0f, -1.0f, -1.0f) * size, -glm::vec2(1.0f,  0.0f), glm::vec3( 0.0f, 0.0f, 1.0f)}); // bottom-left
		m_Verticies.push_back({glm::vec3(-1.0f, -1.0f,  1.0f) * size, -glm::vec2(1.0f,  0.0f), glm::vec3( 0.0f, 0.0f, 0.0f)}); // bottom-right
		m_Verticies.push_back({glm::vec3(-1.0f,  1.0f,  1.0f) * size, -glm::vec2(1.0f,  0.0f), glm::vec3( 0.0f, 1.0f, 0.0f)}); // top-right
		// right face										  
		m_Verticies.push_back({glm::vec3( 1.0f,  1.0f,  1.0f) * size,  glm::vec2(1.0f,  0.0f), glm::vec3( 0.0f, 1.0f, 0.0f)}); // top-left
		m_Verticies.push_back({glm::vec3( 1.0f, -1.0f, -1.0f) * size,  glm::vec2(1.0f,  0.0f), glm::vec3( 0.0f, 0.0f, 1.0f)}); // bottom-right
		m_Verticies.push_back({glm::vec3( 1.0f,  1.0f, -1.0f) * size,  glm::vec2(1.0f,  0.0f), glm::vec3( 0.0f, 1.0f, 1.0f)}); // top-right         
		m_Verticies.push_back({glm::vec3( 1.0f, -1.0f, -1.0f) * size,  glm::vec2(1.0f,  0.0f), glm::vec3( 0.0f, 0.0f, 1.0f)}); // bottom-right
		m_Verticies.push_back({glm::vec3( 1.0f,  1.0f,  1.0f) * size,  glm::vec2(1.0f,  0.0f), glm::vec3( 0.0f, 1.0f, 0.0f)}); // top-left
		m_Verticies.push_back({glm::vec3( 1.0f, -1.0f,  1.0f) * size,  glm::vec2(1.0f,  0.0f), glm::vec3( 0.0f, 0.0f, 0.0f)}); // bottom-left     
		// bottom face										  
		m_Verticies.push_back({glm::vec3(-1.0f, -1.0f, -1.0f) * size,  glm::vec2(0.0f, -1.0f), glm::vec3( 0.0f, 0.0f, 1.0f)}); // top-right
		m_Verticies.push_back({glm::vec3( 1.0f, -1.0f, -1.0f) * size,  glm::vec2(0.0f, -1.0f), glm::vec3( 0.0f, 1.0f, 1.0f)}); // top-left
		m_Verticies.push_back({glm::vec3( 1.0f, -1.0f,  1.0f) * size,  glm::vec2(0.0f, -1.0f), glm::vec3( 0.0f, 1.0f, 0.0f)}); // bottom-left
		m_Verticies.push_back({glm::vec3( 1.0f, -1.0f,  1.0f) * size,  glm::vec2(0.0f, -1.0f), glm::vec3( 0.0f, 1.0f, 0.0f)}); // bottom-left
		m_Verticies.push_back({glm::vec3(-1.0f, -1.0f,  1.0f) * size,  glm::vec2(0.0f, -1.0f), glm::vec3( 0.0f, 0.0f, 0.0f)}); // bottom-right
		m_Verticies.push_back({glm::vec3(-1.0f, -1.0f, -1.0f) * size,  glm::vec2(0.0f, -1.0f), glm::vec3( 0.0f, 0.0f, 1.0f)}); // top-right
		// top face											  
		m_Verticies.push_back({glm::vec3(-1.0f,  1.0f, -1.0f) * size,  glm::vec2(0.0f,  1.0f), glm::vec3( 0.0f, 0.0f, 1.0f)}); // top-left
		m_Verticies.push_back({glm::vec3( 1.0f,  1.0f , 1.0f) * size,  glm::vec2(0.0f,  1.0f), glm::vec3( 0.0f, 1.0f, 0.0f)}); // bottom-right
		m_Verticies.push_back({glm::vec3( 1.0f,  1.0f, -1.0f) * size,  glm::vec2(0.0f,  1.0f), glm::vec3( 0.0f, 1.0f, 1.0f)}); // top-right     
		m_Verticies.push_back({glm::vec3( 1.0f,  1.0f,  1.0f) * size,  glm::vec2(0.0f,  1.0f), glm::vec3( 0.0f, 1.0f, 0.0f)}); // bottom-right
		m_Verticies.push_back({glm::vec3(-1.0f,  1.0f, -1.0f) * size,  glm::vec2(0.0f,  1.0f), glm::vec3( 0.0f, 0.0f, 1.0f)}); // top-left
		m_Verticies.push_back({glm::vec3(-1.0f,  1.0f,  1.0f) * size,  glm::vec2(0.0f,  1.0f), glm::vec3( 0.0f, 0.0f, 0.0f)}); // bottom-left 

		for (unsigned int i = 0; i < 36; i++) {
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
