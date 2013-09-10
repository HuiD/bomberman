#include "textureditem.h"

TexturedItem::TexturedItem() :
	m_currentFrame(0)
{

}

TexturedItem::~TexturedItem()
{

}

void TexturedItem::addTexture(int frameIndex, const TexturePtr& texture)
{
	if (frameIndex > m_textures.size())
		m_textures.resize(frameIndex + 1);

	if (frameIndex < 0)
		m_textures.push_back(texture);
	else
		m_textures[frameIndex] = texture;
}

TexturePtr TexturedItem::getNextTexture() const
{
	if (m_currentFrame == -1)
		return nullptr;

	return m_textures[m_currentFrame];
}

void TexturedItem::update()
{
	if (++m_currentFrame > m_textures.size())
		m_currentFrame = -1;
}

void TexturedItem::reset()
{
	m_currentFrame = -1;
}

