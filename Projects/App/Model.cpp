#include "Model.h"

Model::Model(std::string dir, std::string name)
{
	//Create materials here

	std::ifstream t(dir + "/material.json");
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

	auto matData = nlohmann::json::parse(str);
	std::string temp = matData["name"];
	m_name = temp;

	for (int i = 0; i < matData["materials"].size(); i++) {
		int id = matData["materials"][i]["id"];
		bool textures = matData["materials"][i]["textures"];
		std::string type = matData["materials"][i]["type"];
		if (textures) 
		{
			Material* mat = MaterialLibrary::CreateMaterial(m_name + " " + std::to_string(id), "res/shaders/pbr_" + type + ".shader");
			if (type == "RM" || type == "GM") 
			{
				mat->SetUniform("albedoMap", 0, TextureLibrary::loadTexture(matData["materials"][i]["albedo"]));
				mat->SetUniform("normalMap", 1, TextureLibrary::loadTexture(matData["materials"][i]["normal"]));
				mat->SetUniform("metallicMap", 2, TextureLibrary::loadTexture(matData["materials"][i]["metallic"]));
				mat->SetUniform("roughnessMap", 3, TextureLibrary::loadTexture(matData["materials"][i]["roughness"]));
				mat->SetUniform("aoMap", 4, TextureLibrary::loadTexture(matData["materials"][i]["ao"]));
				mat->SetUniform("irradianceMap", 5);
                mat->SetUniform("prefilterMap", 6);
                mat->SetUniform("brdfLUT", 7);

			}
			else if (type == "UE4") 
			{
				mat->SetUniform("basecolorMap", 0, TextureLibrary::loadTexture(matData["materials"][i]["base"]));
				mat->SetUniform("normalMap", 1, TextureLibrary::loadTexture(matData["materials"][i]["normal"]));
				mat->SetUniform("ORMMap", 2, TextureLibrary::loadTexture(matData["materials"][i]["ORM"]));
			}

		}
		else 
		{
			//Make a non texture version of the pbr shader and load it here
		}
	}

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(dir + "/" + name, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	std::vector<Vertex> verticies;
	std::vector<unsigned int> indicies;

	for (int i = 0; i < scene->mNumMeshes; i++) 
	{
		Vertex vert;
		aiMesh* mesh = scene->mMeshes[i];
		
		for (int j = 0; j < mesh->mNumVertices; j++) 
		{
			aiVector3D vector = mesh->mVertices[j];
			aiVector3D normal = mesh->mNormals[j];

			vert.Position = glm::vec3(vector.x, vector.y, vector.z);
			vert.Normal = glm::vec3(normal.x, normal.y, normal.z);

			aiVector3D* textCoord = mesh->mTextureCoords[0];
			if (textCoord) 
			{
				vert.Texture = glm::vec3(textCoord[j].x, textCoord[j].y, textCoord[j].z);
			}
			else
			{
				vert.Texture = glm::vec3(0.0);
			}
			verticies.push_back(vert);
		}

		for (int j = 0; j < mesh->mNumFaces; j++)
		{
			aiFace face = mesh->mFaces[j];
			for (int k = 0; k < face.mNumIndices; k++) 
			{
				indicies.push_back(face.mIndices[k]);
			}
		}
		m_Meshes[mesh->mMaterialIndex] = Mesh(verticies, indicies);
		verticies.clear();
		indicies.clear();
	}
}

void Model::Draw()
{
	for (auto& mesh : m_Meshes) 
	{
		Material* mat = MaterialLibrary::GetMaterial(m_name + " " + std::to_string(mesh.first));
		Renderer::Draw(&mesh.second, mat);
	}
}

void Model::Update(glm::mat4 model, glm::mat4 view, glm::vec3 viewpos)
{
	for (auto& mesh : m_Meshes) 
	{
		Material* mat = MaterialLibrary::GetMaterial(m_name + " " + std::to_string(mesh.first));
		mat->SetUniform("view", view);
		mat->SetUniform("viewPos", viewpos);
		mat->SetUniform("model", model);
	}
}

void Model::UpdateLights(glm::vec3 positions[], int size, glm::vec3 colors[])
{
	for (auto& mesh : m_Meshes) 
	{
		Material* mat = MaterialLibrary::GetMaterial(m_name + " " + std::to_string(mesh.first));
		mat->SetUniform("lightPositions", positions, size);
		mat->SetUniform("lightColors", colors, size);
	}
}

void Model::SetProjection(glm::mat4 proj)
{
	for(auto& mesh: m_Meshes)
	{
		Material* mat = MaterialLibrary::GetMaterial(m_name + " " + std::to_string(mesh.first));
		mat->SetUniform("projection", proj);
	}
}
