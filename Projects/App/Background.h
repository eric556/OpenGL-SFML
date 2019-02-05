#pragma once
#include "MaterialLibrary.h"
#include "TextureLibrary.h"
#include "Mesh.h"
#include <glm\gtc\matrix_transform.hpp>
#include <stb_image.hpp>
#include "Cube.h"
#include "Plane.h"
#include "Renderer.h"

/// <summary>
/// Return values for GenerateMaps
/// </summary>
struct IBLMaps
{
	unsigned int enviormentMap;
	unsigned int irradianceMap;
    unsigned int prefilterMap;
    unsigned int lut;
};

/// <summary>
/// Return values for GenerateEnv
/// </summary>
struct EnvReturn
{
    unsigned int envMap;
    unsigned int captrueFBO;
    unsigned int captureRBO;
};


class Background 
{
public:
	/// <summary>
	/// Generates the maps used in IBL.
	/// </summary>
	/// <param name="path">The path to the HDR map.</param>
	/// <returns>ID's to the generated maps</returns>
	static IBLMaps GenerateMaps(std::string path);
private:
	/// <summary>
	/// Generates the enviorment map from and HDR file.
	/// </summary>
	/// <param name="path">The path to an HDR file.</param>
	/// <returns>The GL id to the envMap and the GL id's to the FBO and the RBO</returns>
	static EnvReturn GenerateEnv(std::string path);


	/// <summary>
	/// Generates the irradiance map given a enviorment cube map.
	/// </summary>
	/// <param name="envCubemap">The env cubemap id.</param>
	/// <param name="captureFBO">The capture fbo id.</param>
	/// <param name="captureRBO">The capture rbo id.</param>
	/// <returns>The id of the generated irradiance map</returns>
	static unsigned int GenerateIrr(unsigned int envCubemap, unsigned int captureFBO, unsigned int captureRBO);

	/// <summary>
	/// Generates the pre filter from the enviorment cube map.
	/// </summary>
	/// <param name="envCubemap">The env cubemap id.</param>
	/// <param name="captureFBO">The capture fbo id.</param>
	/// <param name="captureRBO">The capture rbo id.</param>
	/// <returns>The id of the generated pre filter map</returns>
	static unsigned int GeneratePreFilter(unsigned int envCubemap, unsigned int captureFBO, unsigned int captureRBO);

	/// <summary>
	/// Generates the brdf 2d lut.
	/// </summary>
	/// <param name="captureFBO">The capture fbo id from the prefilter.</param>
	/// <param name="captureRBO">The capture rbo id from the prefilter.</param>
	/// <returns>The id of the generated brdf lut</returns>
	static unsigned int GenerateLut(unsigned int captureFBO, unsigned int captureRBO);
};