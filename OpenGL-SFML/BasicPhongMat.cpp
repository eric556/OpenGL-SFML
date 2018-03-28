#include "BasicPhongMat.h"

BasicPhongMat::BasicPhongMat()
{
    ShaderSources sources = Material::parseShader("res/shaders/basic_phong.shader");
    if (!m_shader.loadFromMemory(sources.vertexSource, sources.fragmentSource)) {
        std::cout << "Error loading basic_phong.shader\n";
    }
}

void BasicPhongMat::Bind()
{
	sf::Shader::bind(&m_shader);
	m_shader.setUniform("material.ambient", sf::Glsl::Vec3(m_MaterialParameters.ambient.x, m_MaterialParameters.ambient.y, m_MaterialParameters.ambient.z));
	m_shader.setUniform("material.diffuse", sf::Glsl::Vec3(m_MaterialParameters.diffuse.x, m_MaterialParameters.diffuse.y, m_MaterialParameters.diffuse.z));
	m_shader.setUniform("material.specular", sf::Glsl::Vec3(m_MaterialParameters.specular.x, m_MaterialParameters.specular.y, m_MaterialParameters.specular.z));
    m_shader.setUniform("material.shininess", m_MaterialParameters.shininess);
    m_shader.setUniform("light.position", sf::Glsl::Vec3(m_LightParameters.position.x, m_LightParameters.position.y, m_LightParameters.position.z));
    m_shader.setUniform("light.ambient", sf::Glsl::Vec3(m_LightParameters.ambient.x, m_LightParameters.ambient.y, m_LightParameters.ambient.z));
    m_shader.setUniform("light.diffuse", sf::Glsl::Vec3(m_LightParameters.diffuse.x, m_LightParameters.diffuse.y, m_LightParameters.diffuse.z));
    m_shader.setUniform("light.specular", sf::Glsl::Vec3(m_LightParameters.specular.x, m_LightParameters.specular.y, m_LightParameters.specular.z));
    m_shader.setUniform("viewPos", sf::Glsl::Vec3(m_ViewPos.x, m_ViewPos.y, m_ViewPos.z));
    m_shader.setUniform("view", sf::Glsl::Mat4(&m_View[0][0]));
    m_shader.setUniform("model", sf::Glsl::Mat4(&m_Model[0][0]));
    m_shader.setUniform("projection", sf::Glsl::Mat4(&m_Projection[0][0]));
}

void BasicPhongMat::SetMaterialParameters(MaterialParameters params)
{
	m_MaterialParameters = params;
}

void BasicPhongMat::SetLightParameters(LightParameters params)
{
	m_LightParameters = params;
}

void BasicPhongMat::SetViewPos(glm::vec3 viewpos)
{
    this->m_ViewPos = viewpos;
}
