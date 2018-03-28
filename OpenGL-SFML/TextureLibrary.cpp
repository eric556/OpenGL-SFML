#include "TextureLibrary.h"

std::map<std::string, sf::Texture*> TextureLibrary::m_Textures = {};

sf::Texture * TextureLibrary::loadTexture(const std::string path, bool smoothing, bool flipped)
{
	sf::Texture text;
	if (flipped) 
	{
		sf::Image img;
		if (!img.loadFromFile(path)) 
		{
			std::cout << "Error loading image: " << path << "\n";
		}
		img.flipVertically();
		
		if (!text.loadFromImage(img, sf::IntRect(0, 0, img.getSize().x, img.getSize().y)))
		{
			std::cout << "Error loading image: " << path << "\n";
		}
	}
	else 
	{
		if (!text.loadFromFile(path)) 
		{
			std::cout << "Error loading texture: " << path << "\n";
		}
	}
	text.generateMipmap();
	text.setRepeated(true);
	text.setSmooth(smoothing);
	m_Textures[path] = new sf::Texture(text);
	return m_Textures[path];
}

sf::Texture * TextureLibrary::GetTexture(const std::string id)
{
	return m_Textures[id];
}

unsigned int TextureLibrary::loadHDR(const std::string path)
{
    //stbi_set_flip_vertically_on_load(true);
	int width, height, nrComponents;
    float *data = stbi_loadf(path.c_str(), &width, &height, &nrComponents, 0);
    unsigned int hdrText;
    if (data) 
	{
        GLCall(glGenTextures(1, &hdrText));
        GLCall(glBindTexture(GL_TEXTURE_2D, hdrText));
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        stbi_image_free(data);
    }
    //stbi_set_flip_vertically_on_load(false);

    return hdrText;
}
