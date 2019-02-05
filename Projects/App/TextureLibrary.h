#pragma once
#include <SFML\Graphics.hpp>
#include <stb_image.hpp>
#include "Util.h"
#include <GL\glew.h>
#include <map>
#include <memory>
#include <iostream>

class TextureLibrary 
{
public:

	/// <summary>
	/// Loads the texture from the given path.
	/// </summary>
	/// <param name="path">The path to the texture.</param>
	/// <param name="smoothing">if set to <c>true</c> [smoothing].</param>
	/// <param name="flipped">if set to <c>true</c> [flipped].</param>
	/// <returns>A pointer to the loaded texture</returns>
	static sf::Texture* loadTexture(const std::string path, bool smoothing = false, bool flipped = false);

	/// <summary>
	/// Gets the texture given the ID.
	/// </summary>
	/// <param name="id">The texture identifier.</param>
	/// <returns>A pointer to the texture</returns>
	static sf::Texture* GetTexture(const std::string id);

	/// <summary>
	/// Loads the given HDR.
	/// </summary>
	/// <param name="path">The path to the hdr.</param>
	/// <returns>the GL id of the loaded HDR</returns>
	static unsigned int loadHDR(const std::string path);
	static std::map<std::string, sf::Texture*> m_Textures;
private:
	TextureLibrary() {};
};