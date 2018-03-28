#include "Background.h"

IBLMaps Background::GenerateMaps(std::string path)
{
    EnvReturn envMap = Background::GenerateEnv(path);
	unsigned int irr = Background::GenerateIrr(envMap.envMap, envMap.captrueFBO, envMap.captureRBO);
    unsigned int pre = Background::GeneratePreFilter(envMap.envMap, envMap.captrueFBO, envMap.captureRBO);
    unsigned int lut = Background::GenerateLut(envMap.captrueFBO, envMap.captureRBO);
	GLCall(glViewport(0, 0, 1920, 1080));
	return {envMap.envMap, irr, pre, lut};
}

EnvReturn Background::GenerateEnv(std::string path)
{

    unsigned int hdrText = TextureLibrary::loadHDR(path);

	unsigned int captureFBO;
	unsigned int captureRBO;
	GLCall(glGenFramebuffers(1, &captureFBO));
	GLCall(glGenRenderbuffers(1, &captureRBO));

	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, captureFBO));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, captureRBO));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO));


	Material* matEtoC = MaterialLibrary::GetMaterial("er_to_cube");
	if (!matEtoC) 
	{
		matEtoC = MaterialLibrary::CreateMaterial("er_to_cube", "res/shaders/eq_to_cube.shader");
	}

	unsigned int envCubemap;
	GLCall(glGenTextures(1, &envCubemap));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap));
	for (unsigned int i = 0; i < 6; i++) 
	{
		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, nullptr));
	}
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
	glm::mat4 captureViews[] =
	{
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
	};

	matEtoC->SetUniform("erMap", 0);
	matEtoC->SetUniform("projection", captureProjection);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, hdrText);

	GLCall(glViewport(0, 0, 512, 512));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, captureFBO));
	for (unsigned int i = 0; i < 6; i++) 
	{
		matEtoC->SetUniform("view", captureViews[i]);
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubemap, 0));
		Renderer::Clear();
		Cube cube(1.0f);
		Renderer::Draw(&cube, matEtoC);
	}
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    return{ envCubemap, captureFBO, captureRBO };
}

unsigned int Background::GenerateIrr(unsigned int envCubemap, unsigned int captureFBO, unsigned int captureRBO)
{

	Material* matIrrConvl = MaterialLibrary::GetMaterial("irr_convl");
	if (!matIrrConvl) 
	{
		matIrrConvl = MaterialLibrary::CreateMaterial("irr_convl", "res/shaders/irr_convl.shader");
	}

	unsigned int irradianceMap;
	GLCall(glGenTextures(1, &irradianceMap));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap));
	for (unsigned int i = 0; i < 6; i++) 
	{
		GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr));
	}
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
	glm::mat4 captureViews[] =
	{
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
	};


	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, captureFBO));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, captureRBO));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32));

	matIrrConvl->SetUniform("envMap", 0);
	matIrrConvl->SetUniform("projection", captureProjection);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap);

	glViewport(0, 0, 32, 32);
	glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
	for (unsigned int i = 0; i < 6; i++) 
	{
		matIrrConvl->SetUniform("view", captureViews[i]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
		Renderer::Clear();
		Cube cube(1.0f);
		Renderer::Draw(&cube, matIrrConvl);
	}
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	return irradianceMap;
}

unsigned int Background::GeneratePreFilter(unsigned int envCubemap, unsigned int captureFBO, unsigned int captureRBO)
{
    glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    glm::mat4 captureViews[] =
    {
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
    };

    unsigned int prefilterMap;
    GLCall(glGenTextures(1, &prefilterMap));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, prefilterMap));
    for (unsigned int i = 0; i < 6; i++) 
	{
        GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr));
    }
    
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));
    

    Material* matPrefilter = MaterialLibrary::GetMaterial("prefilter");
    if (!matPrefilter) 
	{
        matPrefilter = MaterialLibrary::CreateMaterial("prefilter", "res/shaders/prefilter.shader");
    }
    matPrefilter->SetUniform("enviormentMap", 0);
    matPrefilter->SetUniform("projection", captureProjection);
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, envCubemap));
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, captureFBO));
    unsigned int maxMipLevels = 5;
    for (unsigned int mip = 0; mip < maxMipLevels; mip++) 
	{
        unsigned int mipWidth = 128 * std::pow(0.5, mip);
        unsigned int mipHeight = 128 * std::pow(0.5, mip);
        GLCall(glBindRenderbuffer(GL_RENDERBUFFER, captureRBO));
        GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipHeight));
        GLCall(glViewport(0, 0, mipWidth, mipHeight));

        float roughness = (float)mip / (float)(maxMipLevels - 1);
        matPrefilter->SetUniform("roughness", roughness);
        for (unsigned int i = 0; i < 6; i++) 
		{
            matPrefilter->SetUniform("view", captureViews[i]);
            GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterMap, mip));

            Renderer::Clear();
            Cube cube(1.0);
            Renderer::Draw(&cube, matPrefilter);
        }
    }
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    return prefilterMap;
}

unsigned int Background::GenerateLut(unsigned int captureFBO, unsigned int captureRBO)
{
    unsigned int brdfLUTTexture;
    glGenTextures(1, &brdfLUTTexture);

    GLCall(glBindTexture(GL_TEXTURE_2D, brdfLUTTexture));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));


    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, captureFBO));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, captureRBO));
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512));
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUTTexture, 0));

    glViewport(0, 0, 512, 512);

    Material* matBrdf = MaterialLibrary::GetMaterial("brdf");
    if (!matBrdf) 
	{
        matBrdf = MaterialLibrary::CreateMaterial("brdf", "res/shaders/brdf.shader");
    }
    Renderer::Clear();
    Plane plane(1.0f, 1.0f);
    Renderer::Draw(&plane, matBrdf, GL_TRIANGLE_STRIP);
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

    return brdfLUTTexture;
}
