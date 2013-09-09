#include "texture.h"

#include <SOIL/SOIL.h>

Texture::Texture()
{

}

Texture::~Texture()
{

}

bool Texture::loadFrom(const std::string& filename)
{
	int channels;
	int width;
	int height;
	uint8_t *data = SOIL_load_image(filename.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
	if (!data)
		return false;

	m_hasAlphaChannel = (channels == 4);
	m_pixels = data;
	m_width = uint16_t(width);
	m_height = uint16_t(height);
	return true;
}

