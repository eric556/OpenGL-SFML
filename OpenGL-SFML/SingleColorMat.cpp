#include "SingleColorMat.h"
#include <iostream>

SingleColorMat::SingleColorMat()
{
	ShaderSources sources = Material::parseShader("res/shaders/basic_color.shader");
	if (!m_shader.loadFromMemory(sources.vertexSource, sources.fragmentSource)) {
		std::cout << "Error loading basic_color.shader\n";
	}
}

void SingleColorMat::Bind()
{
	sf::Shader::bind(&m_shader);
	m_shader.setUniform("input_color", sf::Glsl::Vec3(m_Color.x, m_Color.y, m_Color.z));
	m_shader.setUniform("view", sf::Glsl::Mat4(&m_View[0][0]));
	m_shader.setUniform("model", sf::Glsl::Mat4(&m_Model[0][0]));
	m_shader.setUniform("projection", sf::Glsl::Mat4(&m_Projection[0][0]));
}

void SingleColorMat::SetColor(glm::vec3 color)
{
	m_Color = color;
}

glm::vec3 SingleColorMat::GetColor()
{
	return m_Color;
}
