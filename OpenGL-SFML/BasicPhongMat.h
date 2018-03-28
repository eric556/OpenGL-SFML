#include "Material.h"

struct MaterialParameters {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

struct LightParameters {
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class BasicPhongMat : public Material {
public:
	BasicPhongMat();
	void Bind();
	void SetMaterialParameters(MaterialParameters params);
	void SetLightParameters(LightParameters params);
    void SetViewPos(glm::vec3 viewpos);
private:
	MaterialParameters m_MaterialParameters;
	LightParameters m_LightParameters;
    glm::vec3 m_ViewPos;
};