#ifndef __TEXTURE_H
#define __TEXTURE_H

#include "../../util/databuffer.h"

class Texture
{
public:
	Texture();
	~Texture();

	bool loadFrom(const std::string& filename);

	uint8_t *getPixels() { return &m_pixels[0]; }
	const uint8_t *getPixels() const { return &m_pixels[0]; }
	uint32_t getPixelCount() const { return m_width * m_height; }

	uint16_t getWidth() const { return m_width; }
	void setWidth(uint16_t width) { m_width = width; }

	uint16_t getHeight() const { return m_height; }
	void setHeight(uint16_t height) { m_height = height; }

	bool hasAlphaChannel() const { return m_hasAlphaChannel; }
	void setHasAlphaChannel(bool has) { m_hasAlphaChannel = has; }

private:
	uint16_t m_width;
	uint16_t m_height;
	bool m_hasAlphaChannel;

	DataBuffer<uint8_t> m_pixels;
};

typedef std::shared_ptr<Texture> TexturePtr;

#endif

