#pragma once
#include <map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <fstream>
#include "Renderer.h"
#include "Mesh.h"
#include "TextureLibrary.h"
#include "MaterialLibrary.h"
#include "Libs/json.hpp"


class Model {
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Model"/> class given
	/// the directory containing the model and is material.json file and the
	/// name of the model
	/// </summary>
	/// <param name="dir">The directory of the model and material.json file.</param>
	/// <param name="name">The name of the model file.</param>
	Model(std::string dir, std::string name);

	/// <summary>
	/// Draws this instance.
	/// </summary>
	void Draw();


	/// <summary>
	/// Updates the model given the model mat4 the view mat4 and 
	/// the view pos.
	/// </summary>
	/// <param name="model">The model mat4.</param>
	/// <param name="view">The view.</param>
	/// <param name="viewpos">The viewpos.</param>
	void Update(glm::mat4 model, glm::mat4 view, glm::vec3 viewpos);

	/// <summary>
	/// Updates the lights effecting the model (current max is 4).
	/// </summary>
	/// <param name="positions">The positions of the lights.</param>
	/// <param name="size">The amount of lights.</param>
	/// <param name="colors">The colors of the lights.</param>
	void UpdateLights(glm::vec3 positions[], int size, glm::vec3 colors[]);

	/// <summary>
	/// Sets the projection.
	/// </summary>
	/// <param name="proj">The projection.</param>
	void SetProjection(glm::mat4 proj);
private:
	std::map<int, Mesh> m_Meshes;
	std::string m_name;
};